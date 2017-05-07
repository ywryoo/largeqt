/// @author Ryangwook Ryoo, 2017
/// @email ywryoo@gmail.com
/// @license GNU LGPL
///
/// Distributed under the GNU LGPL License
/// (See accompanying file LICENSE or copy at
/// http://www.gnu.org/licenses/lgpl.html)

#ifndef NEIGHBORTHREAD_H
#define NEIGHBORTHREAD_H

#include <QThread>
#include <QWaitCondition>
#include "pixelsne/pixelsne.h"

class NeighborThread : public QThread
{
    Q_OBJECT

public:
    NeighborThread(QObject *parent = 0);
    ~NeighborThread();
    void runrun(PixelSNE* model);

protected:
    void run() override;

private:
    PixelSNE* pixelsne;
    QWaitCondition condition;
    bool restart;
};
#endif