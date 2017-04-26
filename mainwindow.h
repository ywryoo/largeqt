#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QThread>
#include "workerthread.h"

class QLabel;
class QGroupBox;

class Plot;

class MainWindow: public QWidget
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private slots:
    void setSamples(double*, int, int);
    void startPixelSNE();
    void setConsoleText(const QString text);
private:
    QLabel *createLabel(const QString &text);
    QLabel *consoleLabel;
    WorkerThread *thread;
    Plot *d_plot;
};
#endif
