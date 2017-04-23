#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QDialog>

class QLabel;
class QGroupBox;

class Plot;

class MainWindow: public QWidget
{
    Q_OBJECT

public:
    MainWindow(float *points, long long vertices, long long dims);
    ~MainWindow();
private:
    QLabel *createLabel(const QString &text);
    float *vispoints;
    long long n_vertices;
    long long out_dims;
    void setSamples();
    void setSamples(double*, int, int);
    double fexp(double);
    Plot *d_plot;
};

#endif
