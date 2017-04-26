#include "workerthread.h"
#include "neighborthread.h"
#include "pixelsne/pixelsne.h"
#include <QtWidgets>

WorkerThread::WorkerThread(QObject *parent): QThread(parent)
{
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

}


void WorkerThread::runrun()
{
   if (!isRunning()) {
        start(LowPriority);
    } else {
        restart = true;
        condition.wakeOne();
    }
}

void WorkerThread::run()
{
        
    // Define some variables
    pixelsne = new PixelSNE();

    // #ifdef USE_BITWISE_OP
    //     printf("pixelsne.cpp USE_BITWISE_OP\n");
    // #else
    //     printf("pixelsne.cpp not USE_BITWISE_OP\n");
    // #endif

    // Read the parameters and the dataset
    if(pixelsne->load_data(&data, &origN, &D, &no_dims, &theta, &perplexity, &bins, &p_method, &rand_seed)) {
        sendLog(QString("Data(%1, %2 dimension) Loaded! Initializing..").arg(QString::number(origN),QString::number(D)));
        // Make dummy landmarks
        N = origN;

        int* landmarks = (int*) malloc(N * sizeof(int));
        if(landmarks == NULL) { printf("Memory allocation failed!\n"); exit(1); }
        for(int n = 0; n < N; n++) landmarks[n] = n;

        double* Y = (double*) malloc(N * no_dims * sizeof(double));
        double* costs = (double*) calloc(N, sizeof(double));
        if(Y == NULL || costs == NULL) { printf("Memory allocation failed!\n"); exit(1); }

        pixelsne->run(data, N, D, Y, no_dims, perplexity, theta, bins, p_method, rand_seed, false, max_iter, stop_lying_iter, mom_switch_iter);
        sendLog("Initialized.");
        NeighborThread* nthread = new NeighborThread;
        nthread->runrun(pixelsne);
        for(int iter = 0; iter < max_iter; iter++) {
            pixelsne->updatePoints(Y, N, no_dims, theta, bins, iter, stop_lying_iter, mom_switch_iter, max_iter);
        //    if(iter % 50 == 0) {
                sendLog(QString("Gradient Descent is running - %1/%2").arg(QString::number(iter+1),QString::number(max_iter)));

                emit updatePoints(Y, N, no_dims);
         //   }
        }
        sendLog("Gradient Descent is done.");
      //  emit resultReady(Y, N, no_dims);

    }
}