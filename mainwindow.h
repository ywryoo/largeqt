#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QThread>
#include "pixelsne/LargeVis.h"
#include "pixelsne/pixelsne.h"

class QLabel;
class QGroupBox;

class Plot;

class MainWindow: public QWidget
{
    Q_OBJECT

public:
    MainWindow(float *points, long long vertices, long long dims);
    ~MainWindow();

private slots:
    void setSamples(double*, int, int);


private:
    void *pixelsne_caller(void*);
    void run_pixelsne(int);
    QLabel *createLabel(const QString &text);
    float *vispoints;
    long long n_vertices;
    long long out_dims;
    double fexp(double);
    Plot *d_plot;
};
#endif
