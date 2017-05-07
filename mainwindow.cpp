/// @author Ryangwook Ryoo, 2017
/// @email ywryoo@gmail.com
/// @license GNU LGPL
///
/// Distributed under the GNU LGPL License
/// (See accompanying file LICENSE or copy at
/// http://www.gnu.org/licenses/lgpl.html)

#include "mainwindow.h"
#include "plot.h"
#include "borderlayout.h"
#include <QTextBrowser>
#include <QLabel>
#include <QtWidgets>
#include <QPushButton>
#include "workerthread.h"
#include <iostream>
#include <string>

MainWindow::MainWindow()
{
    //scatterplot
    d_plot = new Plot( this );

    //start button -> startPixelSNE
    startButton = new QPushButton("&Start", this);
    QObject::connect(startButton, SIGNAL(clicked()),this, SLOT(startPixelSNE()));

    //restart button -> restartPixelSNE
    QPushButton *restartButton = new QPushButton("&Restart", this);
    QObject::connect(restartButton, SIGNAL(clicked()),this, SLOT(restartPixelSNE()));

    //right panel
    QWidget *formGroupBox = new QWidget;
    QFormLayout *layout = new QFormLayout;

    //input
    QinputLocation = new QLineEdit("");
    QinputLocation->setText("data.txt");

    //label
    QlabelLocation = new QLineEdit("");
    QlabelLocation->setText("label.txt");

    //theta
    Qtheta = new QDoubleSpinBox();
    Qtheta->setValue(0.5);

    //perplexity
    Qperplexity = new QSpinBox();
    Qperplexity->setValue(50);

    //RP Tree numbers
    Qn_rptrees = new QSpinBox();
    Qn_rptrees->setMinimum(-1);
    Qn_rptrees->setValue(-1);

    //rand_seed
    Qrand_seed = new QSpinBox();
    Qrand_seed->setMinimum(-1);
    Qrand_seed->setValue(30);

    //rand_init
    Qknn_validation = new QCheckBox();
    Qknn_validation->setChecked(true);

    //n_propagations
    Qn_propagations = new QSpinBox();
    Qn_propagations->setValue(3);

    //p_method
    Qp_method = new QSpinBox();
    Qp_method->setValue(0);

    //n_threads
    Qn_threads = new QSpinBox();
    Qn_threads->setValue(4);

    //pipelining
    QPipelining = new QCheckBox();
    QPipelining->setChecked(true);

    //bins
    Qbins = new QSpinBox();
    Qbins->setMaximum(10000);
    Qbins->setMinimum(50);
    Qbins->setValue(512);

    //add boxes to panel
    layout->addRow(new QLabel(tr("Input Location")), QinputLocation);
    layout->addRow(new QLabel(tr("Label Location")), QlabelLocation);    
    layout->addRow(new QLabel(tr("theta")), Qtheta);
    layout->addRow(new QLabel(tr("perplexity")), Qperplexity);
    layout->addRow(new QLabel(tr("n_rptrees")), Qn_rptrees);
    layout->addRow(new QLabel(tr("rand_seed")), Qrand_seed);
    layout->addRow(new QLabel(tr("knn_validation")), Qknn_validation);
    layout->addRow(new QLabel(tr("n_propagations")), Qn_propagations);
    layout->addRow(new QLabel(tr("p_method")), Qp_method);
    layout->addRow(new QLabel(tr("n_threads")), Qn_threads);
    layout->addRow(new QLabel(tr("pipelining")), QPipelining);    
    layout->addRow(new QLabel(tr("bins")), Qbins);
    layout->addRow(startButton);
    layout->addRow(restartButton);
    formGroupBox->setLayout(layout);

    //console label
    consoleLabel = createLabel("Click Start button to start visualization.");

    //main layout
    BorderLayout *mainLayout = new BorderLayout;
    mainLayout->addWidget(d_plot, BorderLayout::Center);
    //mainLayout->addWidget(createLabel("North"), BorderLayout::North);
    //mainLayout->addWidget(createLabel("West"), BorderLayout::West);
    mainLayout->addWidget(formGroupBox, BorderLayout::East);
    //mainLayout->addWidget(createLabel("East 2") , BorderLayout::East);
    mainLayout->addWidget(consoleLabel, BorderLayout::South);
    setLayout(mainLayout);

    //title
    setWindowTitle(tr("Largeqt"));
}

MainWindow::~MainWindow()
{
    if(d_plot != NULL) free(d_plot); d_plot=NULL;
    if(thread != NULL && thread->isRunning()) thread->terminate(); thread->wait();
}

QLabel *MainWindow::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setFrameStyle(QFrame::Box | QFrame::Raised);
    return label;
}

void MainWindow::setConsoleText(const QString text)
{
    consoleLabel->setText(text);
}

void MainWindow::setSamples(double* Y, int N, int no_dims)
{
    if(data_labels != NULL)
    {
        d_plot->setSamplesWithLabels(Y, data_labels, N, no_dims);
        d_plot->replot();
    }
    else
    {
        QPolygonF samples;
        if(no_dims == 2) {
            for ( long long i = 0; i < N; i++ )
            {
                samples += QPointF(Y[i*no_dims],Y[i*no_dims+1] );
            }

        }

        d_plot->setSamples( samples );
        d_plot->replot();
    }

}

void MainWindow::setLabels(int* labels, int N)
{
    data_labels = labels;
    int max = 0;
    for(int i = 0; i< N; i++)
        if(max < data_labels[i])
            max = data_labels[i];
    d_plot->setLabels(max+1);
}

void MainWindow::startPixelSNE()
{
    if(thread != NULL && thread->isRunning()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Wait!");
        msgBox.setText("PixelSNE is Already running!");
        msgBox.exec();
    } else {
        thread = new WorkerThread;
        connect(thread, SIGNAL(updateLabels(int*,int)), this, SLOT(setLabels(int*,int)));
        connect(thread, SIGNAL(updatePoints(double*,int,int)), this, SLOT(setSamples(double*,int,int)));
        connect(thread, SIGNAL(sendLog(QString)), this, SLOT(setConsoleText(QString)) );
        thread->runrun(QinputLocation->text(), QlabelLocation->text(), Qn_propagations->value(), Qtheta->value(), Qperplexity->value(), Qbins->value(), Qp_method->value(), Qrand_seed->value(), Qn_threads->value(), QPipelining->isChecked(),Qknn_validation->isChecked(), Qn_rptrees->value());
    }
}

void MainWindow::restartPixelSNE()
{
    if(thread != NULL && thread->isRunning()) {
        if(thread->initDone())
        {
            thread->stopWorkers();
            thread->terminate();
            thread->wait();
            thread = NULL;
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Wait!");
            msgBox.setText("Try after initialization");
            msgBox.exec();
            return;
        }
    }
    thread = new WorkerThread;
    connect(thread, SIGNAL(updatePoints(double*,int,int)), this, SLOT(setSamples(double*,int,int)));
    connect(thread, SIGNAL(updateLabels(int*,int)), this, SLOT(setLabels(int*,int)));
    connect(thread, SIGNAL(sendLog(QString)), this, SLOT(setConsoleText(QString)) );
    thread->runrun(QinputLocation->text(), QlabelLocation->text(), Qn_propagations->value(), Qtheta->value(), Qperplexity->value(), Qbins->value(), Qp_method->value(), Qrand_seed->value(), Qn_threads->value(), QPipelining->isChecked(),Qknn_validation->isChecked(), Qn_rptrees->value());
}