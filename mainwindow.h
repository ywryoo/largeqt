#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Plot;

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(float *points, long long vertices, long long dims);
    ~MainWindow();
private:
    float *vispoints;
    long long n_vertices;
    long long out_dims;
    void setSamples();

private:
    Plot *d_plot;
    Ui::MainWindow *ui;
};

#endif
