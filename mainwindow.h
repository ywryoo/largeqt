/// @author Ryangwook Ryoo, 2017
/// @email ywryoo@gmail.com
/// @license GNU LGPL
///
/// Distributed under the GNU LGPL License
/// (See accompanying file LICENSE or copy at
/// http://www.gnu.org/licenses/lgpl.html)

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
    MainWindow(int argc, char **argv);
    ~MainWindow();

private slots:
    void setSamples(double*, int, int);
    void setLabels(int*,int);
    void startPixelSNE();
    void restartPixelSNE();
    void setConsoleText(const QString text);
    void on_quit();
private:
    QPushButton *startButton;
    QLabel *createLabel(const QString &text);
    QLabel *consoleLabel;
    QLineEdit* QinputLocation;
    QLineEdit* QlabelLocation;
    QDoubleSpinBox* Qtheta;
    QSpinBox* Qperplexity;
    QSpinBox* Qrand_seed;
    QSpinBox* Qn_rptrees;
    QSpinBox* Qn_propagations;
    QSpinBox* Qp_method;
    QSpinBox* Qn_threads;
    QCheckBox* QPipelining;
    QCheckBox* Qknn_validation;
    QCheckBox* Qsleeping;
    QCheckBox* Qgradient_threading;
    QCheckBox* Qbhsne_only;

    QSpinBox* Qbins;
    WorkerThread *thread = NULL;
    Plot *d_plot;
    int *data_labels = NULL;
    int sleep;
    int fitting_threading;
    int ArgPos(char *str, int argc, char **argv);
};
#endif
