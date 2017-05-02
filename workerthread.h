#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QWaitCondition>
#include "pixelsne/pixelsne.h"
#include "neighborthread.h"

class WorkerThread : public QThread
{
    Q_OBJECT

public:
    WorkerThread(QObject *parent = 0);
    ~WorkerThread();
    void runrun(QString input, QString label, int dim, double th, double perp, unsigned int binbin, int pm, int rseed, int threads,bool isPipelined,bool isRandInit);
    void stopWorkers();
    bool initDone();
protected:
    void run() override;

signals:
    void updateLabels(int* labels, int N);
    void updatePoints(double* Y, int N, int no_dims);
    void sendLog(QString text);
private:
    int     origN;
    int     N;
    int     D;
    int     n_threads;
    int     no_dims;
    bool pipelineEnabled;
    bool isInitDone;
    bool rand_init;
    double  perplexity;
    double  theta;
    double* data;
    int* labels;
    unsigned int bins;
    int     p_method;
    int rand_seed;
    int max_iter;
    int stop_lying_iter;
    int mom_switch_iter;
    PixelSNE* pixelsne;
    QWaitCondition condition;
    QString inputLoc;
    QString labelLoc;
    NeighborThread* nthread;
    void loadLabels(int NN);
};
#endif