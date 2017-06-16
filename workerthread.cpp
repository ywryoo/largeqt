/// @author Ryangwook Ryoo, 2017
/// @email ywryoo@gmail.com
/// @license GNU LGPL
///
/// Distributed under the GNU LGPL License
/// (See accompanying file LICENSE or copy at
/// http://www.gnu.org/licenses/lgpl.html)

#include "workerthread.h"
#include "neighborthread.h"
#include "pixelsne/pixelsne.h"
#include <QtWidgets>
#include <stdlib.h>
#include <stdio.h>
#include <QApplication>
#define BILLION 1000000000L
struct timespec start_time, end_time;
WorkerThread::WorkerThread(QObject *parent): QThread(parent)
{
    inputLoc = QString::fromLocal8Bit("data.dat");
    isInitDone = false;
    rand_seed = 30;
    max_iter=1000;
    stop_lying_iter=250;
    mom_switch_iter=250;
    n_propagations = 3;
    labels=NULL;
    needExit = false;
    sleeping = false;
    fitting_threading = false;
    isCliOnly = false;
    bhsneOnly = false;
}

WorkerThread::~WorkerThread()
{
    
    if(pixelsne != NULL) free(pixelsne); pixelsne = NULL;
    if(data != NULL) free(data); data = NULL;
    if(nthread != NULL && nthread->isRunning())
    {
        nthread->quit();
        //nthread->wait();
        nthread=NULL;
    }
    if(labels != NULL) free(labels); labels=NULL;

}


void WorkerThread::runrun(QString input, QString label, int propagation_num, double th, double perp, unsigned int binbin, int pm, int rseed, int threads, bool isPipelined, bool isValidation, int n_rptrees, bool sleep, bool threading, bool bhsne, double learning, int maxIter, int early_iter, double sratee)
{
    inputLoc = input;
    labelLoc = label;
    n_propagations = propagation_num;
    theta = th;
    perplexity = perp;
    bins = binbin;
    p_method = pm;
    rand_seed = rseed;
    knn_validation = isValidation;
    n_threads = threads;
    pipelineEnabled = isPipelined;
    n_trees = n_rptrees;
    sleeping = sleep;
    fitting_threading = threading;
    bhsneOnly = bhsne;
    max_iter = maxIter;
    stop_lying_iter = early_iter;
    learning_rate = learning;
    srate = sratee;
   if (!isRunning()) {
        start(LowPriority);
    }/* else {
        restart = true;
        condition.wakeOne();
    }*/
}
void WorkerThread::runrun(QString input, QString label, QString out, int propagation_num, double th, double perp, unsigned int binbin, int pm, int rseed, int threads, bool isPipelined, bool isValidation, int n_rptrees,bool sleep, bool threading, bool bhsne, double learning, int maxIter, int early_iter, double sratee, bool cliOnly)
{
    inputLoc = input;
    labelLoc = label;
    outLoc = out;
    n_propagations = propagation_num;
    theta = th;
    perplexity = perp;
    bins = binbin;
    p_method = pm;
    rand_seed = rseed;
    knn_validation = isValidation;
    n_threads = threads;
    pipelineEnabled = isPipelined;
    n_trees = n_rptrees;
    sleeping = sleep;
    fitting_threading = threading;
    isCliOnly = cliOnly;
    bhsneOnly = bhsne;
    max_iter = maxIter;
    stop_lying_iter = early_iter;
    learning_rate = learning;
    srate = sratee;
    needExit = true;

   if (!isRunning()) {
        start(LowPriority);
    }/* else {
        restart = true;
        condition.wakeOne();
    }*/
}

void WorkerThread::stopWorkers()
{
    if(nthread != NULL && nthread->isRunning())
    {
        nthread->quit();
        //nthread->wait();
        nthread=NULL;
    }
}

void WorkerThread::run()
{
    FILE* time_file;
    double calc_time = 0;
    double total_time = 0;

    pixelsne = new PixelSNE();
    if(!isCliOnly)
        sendLog("Loading Data..");

    if(inputLoc.contains(".dat",Qt::CaseInsensitive))
    {

        //temp vals for dump value
        int tempint;
        int tempint2;
        int tempint3;
        double tempdouble;
        double tempdouble2;
        unsigned int tempuint;

        // Read the parameters and the dataset
        pixelsne->load_data(inputLoc.toUtf8().constData(), &data, &origN, &D, &tempint, &tempdouble, &tempdouble2, &tempuint, &tempint2, &tempint3);
    }
    else if(inputLoc.contains(".log",Qt::CaseInsensitive))
    {
        FILE *h;
        size_t res = -1;
        int n, d;
        if((h = fopen(inputLoc.toUtf8().constData(), "r+b")) == NULL) {
            printf("LargeQT: Error: could not open data file.\n");
            return;
        }
        res = fread(&origN, sizeof(int), 1, h);                                            
        res = fread(&D, sizeof(int), 1, h);                                            

        data = (double*) malloc(D * origN * sizeof(double));
        if(data == NULL) { printf("LargeQT: Memory allocation failed!\n"); return; }
        res = fread(data, sizeof(double), origN * D, h);                               
        double C = 0;
        res = fread(&C, sizeof(double), 1, h);                                                       

        fclose(h);
        printf("LargeQT: Read the %i x %i data matrix successfully!\n", origN, D);
        printf("LargeQT: Error was %lf\n", C);

        if(!labelLoc.isEmpty()){
            loadLabels(origN);
        }

        if(!isCliOnly)
            emit updatePoints(data, origN, 2);
        if(!isCliOnly)
            sendLog("Log loaded");

        return;
    }
    else
    {
        // Load data from txt file like largevis
        pixelsne->load_data(inputLoc.toUtf8().constData(), &data, &origN, &D);

    }

    N = origN;
    if(!labelLoc.isEmpty()){
        loadLabels(N);
        if(!isCliOnly)
            sendLog(QString("Data(%1, %2D) with labels are Loaded! Initializing..").arg(QString::number(origN),QString::number(D)));       
    }
    else
    {
        if(!isCliOnly)
            sendLog(QString("Data(%1, %2D) are Loaded! Initializing..").arg(QString::number(origN),QString::number(D)));

    }
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    double* Y = (double*) malloc(N * 2 * sizeof(double));
    double* costs = (double*) calloc(N, sizeof(double));
    if(Y == NULL || costs == NULL) { printf("LargeQT: Memory allocation failed!\n"); exit(1); }


    //run RP Tree ONLY
    pixelsne->run(data, N, D, Y, 2, perplexity, theta, bins, p_method, rand_seed, n_threads, n_propagations, false, n_trees, bhsneOnly, knn_validation, pipelineEnabled ,srate, learning_rate, max_iter, stop_lying_iter, mom_switch_iter);

    isInitDone = true;
    //run background threads for neighbor exploring
    if(p_method == 0)
    {
        nthread = new NeighborThread;
        nthread->runrun(pixelsne);
        if(!pipelineEnabled)
        {
            nthread->wait(); //Neighbor exploring will be done before visualization
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    if(!isCliOnly)
        sendLog("Initialized.");

    total_time += (double)(end_time.tv_sec - start_time.tv_sec) + (double)(end_time.tv_nsec - start_time.tv_nsec)/BILLION;
    printf("LargeQT: Visualization started at %.2lfs\n", total_time);
    if(!outLoc.isEmpty())
    {
        printf("LargeQT: Logging on\n");
        time_file = fopen(QString(outLoc).append("_time_label.txt").toUtf8().constData(), "w+");
        calc_time = pixelsne->init_real_time + pixelsne->propagation_real_time;
        char temp_str[100] = "";
        sprintf(temp_str, "%.4lf %.4lf\n", calc_time, total_time);
        fwrite(temp_str, strlen(temp_str), 1, time_file);
        fclose(time_file);

    }
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    double temptime = 0;

    //TODO max_iter should come from pixelsne
    for(int iter = 0; iter < pixelsne->get_max_iter(); iter++) {

        //a gradient descent
        pixelsne->updatePoints(Y, N, 2, theta, bins, fitting_threading, sleeping, iter, stop_lying_iter, mom_switch_iter, max_iter);

        clock_gettime(CLOCK_MONOTONIC, &end_time);        
        temptime += (double)(end_time.tv_sec - start_time.tv_sec) + (double)(end_time.tv_nsec - start_time.tv_nsec)/BILLION;
        total_time += (double)(end_time.tv_sec - start_time.tv_sec) + (double)(end_time.tv_nsec - start_time.tv_nsec)/BILLION;
        if(!isCliOnly)
            sendLog(QString("Gradient Descent is running - %1/%2").arg(QString::number(iter+1),QString::number(max_iter)));
        
        //visualizing points
        if(!isCliOnly)
            emit updatePoints(Y, N, 2);
        if (iter > 0 && ((iter+1) % 50 == 0 || iter == pixelsne->get_max_iter() - 1)) {
            clock_gettime(CLOCK_MONOTONIC, &end_time);

            printf("LargeQT: Iteration %d: 50 iterations in %4.2lf real seconds\n", iter+1, temptime);
            if(!outLoc.isEmpty())
            {
                time_file = fopen(QString(outLoc).append("_time_label.txt").toUtf8().constData(), "a+");
                char temp_str[100] = "";
                sprintf(temp_str, "%.4lf %.4lf\n", calc_time+pixelsne->fitting_real_time, total_time);
                fwrite(temp_str, strlen(temp_str), 1, time_file);
                fclose(time_file);
                pixelsne->copy_y(Y, N, 2, iter+1);
                //save logs
//                pixelsne->save_data(QString(outLoc).toUtf8().constData(), Y, N, 2, theta, bins, iter);
            }
            
            temptime = 0;
        
        }
        clock_gettime(CLOCK_MONOTONIC, &start_time);
    }
    printf("LargeQT: Visualization ended at %.2lfs\n", total_time);

    if(!isCliOnly)
        sendLog("Done.");
    
    if(!outLoc.isEmpty())
    {
        pixelsne->save_y(QString(outLoc).toUtf8().constData(), N, 2, theta, bins);

        if(needExit && !isCliOnly)
        {
            quit_app();
        }
    }
}

void WorkerThread::loadLabels(int NN)
{

    int res = -1;

	FILE *fin = fopen(labelLoc.toUtf8().constData(), "rb");
	if (fin == NULL)
	{
        labels = NULL;
		printf("\nLargeQT: File not found!\n");
		return;
	}
    printf("LargeQT: Reading label file %s ......\n", labelLoc.toUtf8().constData());
    labels = (int *) malloc(NN * sizeof(int));
	for (long long i = 0; i < NN; ++i)
        res = fscanf(fin, "%d", &labels[i]);
	fclose(fin);
    if(!isCliOnly)
        emit updateLabels(labels, NN);
    printf("LargeQT: Label file is loaded.\n");
}



bool WorkerThread::initDone()
{
    return isInitDone;
}