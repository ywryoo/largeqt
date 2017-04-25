#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QWaitCondition>
#include "pixelsne/pixelsne.h"

class WorkerThread : public QThread
{
    Q_OBJECT

public:
    WorkerThread(QObject *parent = 0);
    ~WorkerThread();
    void runrun();

protected:
    void run() override;

signals:
    void resultReady(double* Y, int N, int no_dims);
private:
    int     origN;
    int     N;
    int     D;
    int     no_dims;
    double  perplexity;
    double  theta;
    double* data;
    unsigned int bins;
    int     p_method;
    int rand_seed;
    int max_iter;
    int stop_lying_iter;
    int mom_switch_iter;
    PixelSNE* pixelsne;
    bool restart;
    QWaitCondition condition;
};
#endif