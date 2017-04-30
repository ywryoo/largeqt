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
    void runrun(QString input, int dim, double th, double perp, unsigned int binbin, int pm, int rseed);

protected:
    void run() override;

signals:
    void updatePoints(double* Y, int N, int no_dims);
    void sendLog(QString text);
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
    QString inputLoc;
};
#endif