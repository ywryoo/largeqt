#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_ 1

#include <qmainwindow.h>

class Plot;

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(float *points, long long vertices, long long dims);

private:
    float *vispoints;
    long long n_vertices;
    long long out_dims;
    void setSamples();

private:
    Plot *d_plot;
};

#endif
