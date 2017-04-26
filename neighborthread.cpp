#include "neighborthread.h"
#include "pixelsne/pixelsne.h"
#include <QtWidgets>
#include <QThread>

NeighborThread::NeighborThread(QObject *parent): QThread(parent)
{
    pixelsne = NULL;
}
NeighborThread::~NeighborThread()
{
    pixelsne = NULL;    
}

void NeighborThread::runrun(PixelSNE* model)
{
    pixelsne = model;
    if (!isRunning()) {
        start(LowPriority);
    } else {
        restart = true;
        condition.wakeOne();
    }
}

void NeighborThread::run()
{
    if(pixelsne != NULL)
    {
        for(int i = 0; i < 3 ; i ++)
        {
            pixelsne->updateKNN(i);
        }

    }
}
    