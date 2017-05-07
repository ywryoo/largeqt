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
}

WorkerThread::~WorkerThread()
{
    
    if(pixelsne != NULL) free(pixelsne); pixelsne = NULL;
    if(data != NULL) free(data); data = NULL;
    if(nthread != NULL && nthread->isRunning())
    {
        nthread->terminate();
        nthread->wait();
        nthread=NULL;
    }
    if(labels != NULL) free(labels); labels=NULL;

}


void WorkerThread::runrun(QString input, QString label, int propagation_num, double th, double perp, unsigned int binbin, int pm, int rseed, int threads, bool isPipelined, bool isValidation, int n_rptrees)
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
        nthread->terminate();
        nthread->wait();
        nthread=NULL;
    }
}

void WorkerThread::run()
{
    pixelsne = new PixelSNE();
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
    else
    {
        // Load data from txt file like largevis
        pixelsne->load_data(inputLoc.toUtf8().constData(), &data, &origN, &D);

    }

    N = origN;
    if(!labelLoc.isEmpty()){
        loadLabels(N);
        sendLog(QString("Data(%1, %2D) with labels are Loaded! Initializing..").arg(QString::number(origN),QString::number(D)));       
    }
    else
    {
        sendLog(QString("Data(%1, %2D) are Loaded! Initializing..").arg(QString::number(origN),QString::number(D)));

    }

    // Make dummy landmarks
    int* landmarks = (int*) malloc(N * sizeof(int));
    if(landmarks == NULL) { printf("LargeQT: Memory allocation failed!\n"); exit(1); }
    for(int n = 0; n < N; n++) landmarks[n] = n;

    double* Y = (double*) malloc(N * 2 * sizeof(double));
    double* costs = (double*) calloc(N, sizeof(double));
    if(Y == NULL || costs == NULL) { printf("LargeQT: Memory allocation failed!\n"); exit(1); }

    //run RP Tree ONLY
    pixelsne->run(data, N, D, Y, 2, perplexity, theta, bins, p_method, rand_seed, n_threads, n_propagations, false, n_trees, knn_validation, max_iter, stop_lying_iter, mom_switch_iter);
    sendLog("Initialized.");

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

    //TODO max_iter should come from pixelsne
    for(int iter = 0; iter < pixelsne->get_max_iter(); iter++) {
        //a gradient descent
        pixelsne->updatePoints(Y, N, 2, theta, bins, iter, stop_lying_iter, mom_switch_iter, max_iter);
        
        sendLog(QString("Gradient Descent is running - %1/%2").arg(QString::number(iter+1),QString::number(max_iter)));
        
        //visualizing points
        emit updatePoints(Y, N, 2);
    }

    sendLog("Done.");
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
    emit updateLabels(labels, NN);
    printf("LargeQT: Label file is loaded.\n");
}



bool WorkerThread::initDone()
{
    return isInitDone;
}