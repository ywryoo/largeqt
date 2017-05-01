#include "workerthread.h"
#include "neighborthread.h"
#include "pixelsne/pixelsne.h"
#include <QtWidgets>

WorkerThread::WorkerThread(QObject *parent): QThread(parent)
{
    inputLoc = QString::fromLocal8Bit("data.dat");
    restart = false;
    rand_seed = 30;
    max_iter=1000;
    stop_lying_iter=250;
    mom_switch_iter=250;

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

}


void WorkerThread::runrun(QString input, int dim, double th, double perp, unsigned int binbin, int pm, int rseed)
{
    inputLoc = input;
    no_dims = dim;
    theta = th;
    perplexity = perp;
    bins = binbin;
    p_method = pm;
    rand_seed = rseed;
    
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

    //temp vals for dump value
    int tempint;
    int tempint2;
    int tempint3;
    double tempdouble;
    double tempdouble2;
    unsigned int tempuint;

    // Read the parameters and the dataset
    pixelsne->load_data(inputLoc.toUtf8().constData(), &data, &origN, &D, &tempint, &tempdouble, &tempdouble2, &tempuint, &tempint2, &tempint3);

    sendLog(QString("Data(%1, %2 dimension) Loaded! Initializing..").arg(QString::number(origN),QString::number(D)));

    N = origN;

    // Make dummy landmarks
    int* landmarks = (int*) malloc(N * sizeof(int));
    if(landmarks == NULL) { printf("Memory allocation failed!\n"); exit(1); }
    for(int n = 0; n < N; n++) landmarks[n] = n;

    double* Y = (double*) malloc(N * no_dims * sizeof(double));
    double* costs = (double*) calloc(N, sizeof(double));
    if(Y == NULL || costs == NULL) { printf("Memory allocation failed!\n"); exit(1); }

    //run RP Tree ONLY
    pixelsne->run(data, N, D, Y, no_dims, perplexity, theta, bins, p_method, rand_seed, false, max_iter, stop_lying_iter, mom_switch_iter);
    sendLog("Initialized.");

    //run background threads for neighbor exploring
    nthread = new NeighborThread;
    nthread->runrun(pixelsne);
    //nthread->wait(); //Uncomment if neighbor exploring is done before visualization

    //TODO max_iter should come from pixelsne
    for(int iter = 0; iter < max_iter; iter++) {
        //a gradient descent
        pixelsne->updatePoints(Y, N, no_dims, theta, bins, iter, stop_lying_iter, mom_switch_iter, max_iter);
        
        sendLog(QString("Gradient Descent is running - %1/%2").arg(QString::number(iter+1),QString::number(max_iter)));
        
        //visualizing points
        emit updatePoints(Y, N, no_dims);
    }

    sendLog("Gradient Descent is done.");
}