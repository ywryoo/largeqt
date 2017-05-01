#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QtWidgets>
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
    void restartPixelSNE();
    void setConsoleText(const QString text);
private:
    QPushButton *startButton;
    QLabel *createLabel(const QString &text);
    QLabel *consoleLabel;
    QLineEdit* QinputLocation;
    QLineEdit* QoutputLocation;
    QDoubleSpinBox* Qtheta;
    QSpinBox* Qperplexity;
    QSpinBox* Qno_dims;
    QSpinBox* Qp_method;
    QSpinBox* Qn_threads;
    QCheckBox* QPipelining;
    QSpinBox* Qbins;
    WorkerThread *thread;
    Plot *d_plot;
};
#endif
