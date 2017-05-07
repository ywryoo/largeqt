/// @author Ryangwook Ryoo, 2017
/// @email ywryoo@gmail.com
/// @license GNU LGPL
///
/// Distributed under the GNU LGPL License
/// (See accompanying file LICENSE or copy at
/// http://www.gnu.org/licenses/lgpl.html)

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
        printf("LargeQT: total propagation: %d\n",pixelsne->get_propagation_num());
        for(int i = 0; i < pixelsne->get_propagation_num() ; i ++)
        {
            pixelsne->updateKNN(i);
        }

    }
}
    