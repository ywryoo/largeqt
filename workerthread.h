/// @author Ryangwook Ryoo, 2017
/// @email ywryoo@gmail.com
/// @license GNU LGPL
///
/// Distributed under the GNU LGPL License
/// (See accompanying file LICENSE or copy at
/// http://www.gnu.org/licenses/lgpl.html)

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
    void runrun(QString input, QString label, int propagation_num, double th, double perp, unsigned int binbin, int pm, int rseed, int threads,bool isPipelined,bool isRandInit, int n_rptrees);
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
    int     n_propagations;
    bool pipelineEnabled;
    bool isInitDone;
    bool knn_validation;
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
    int n_trees;
    PixelSNE* pixelsne;
    QWaitCondition condition;
    QString inputLoc;
    QString labelLoc;
    NeighborThread* nthread;
    void loadLabels(int NN);
};
#endif