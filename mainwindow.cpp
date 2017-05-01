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
    QinputLocation->setText("data.dat");

    //theta
    Qtheta = new QDoubleSpinBox();
    Qtheta->setValue(0.5);

    //perplexity
    Qperplexity = new QSpinBox();
    Qperplexity->setValue(50);

    //no_dims
    Qno_dims = new QSpinBox();
    Qno_dims->setValue(2);

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
    layout->addRow(new QLabel(tr("theta")), Qtheta);
    layout->addRow(new QLabel(tr("perplexity")), Qperplexity);
    layout->addRow(new QLabel(tr("no_dims")), Qno_dims);
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
    if(thread != NULL && thread->isRunning()) thread->exit();
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
    //TODO read label
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

void MainWindow::startPixelSNE()
{
    if(thread != NULL && thread->isRunning()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Wait!");
        msgBox.setText("PixelSNE is Already running!");
        msgBox.exec();
    } else {
        thread = new WorkerThread;
        connect(thread, SIGNAL(updatePoints(double*,int,int)), this, SLOT(setSamples(double*,int,int)));
        connect(thread, SIGNAL(sendLog(QString)), this, SLOT(setConsoleText(QString)) );
        thread->runrun(QinputLocation->text(), Qno_dims->value(), Qtheta->value(), Qperplexity->value(), Qbins->value(), Qp_method->value(), 30, Qn_threads->value(), QPipelining->isChecked());
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
    connect(thread, SIGNAL(sendLog(QString)), this, SLOT(setConsoleText(QString)) );
    thread->runrun(QinputLocation->text(), Qno_dims->value(), Qtheta->value(), Qperplexity->value(), Qbins->value(), Qp_method->value(), 30, Qn_threads->value(), QPipelining->isChecked());
}