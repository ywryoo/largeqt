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

    d_plot = new Plot( this );

    QTextBrowser *centralWidget = new QTextBrowser;
    centralWidget->setPlainText(tr("Central widget"));
    QPushButton *button = new QPushButton("&Run", this);
    QObject::connect(button, SIGNAL(clicked()),this, SLOT(startPixelSNE()));
    QWidget *formGroupBox = new QWidget;
    QFormLayout *layout = new QFormLayout;
    QinputLocation = new QLineEdit("");
    QinputLocation->setText("data.dat");
    QoutputLocation = new QLineEdit("");
    QoutputLocation->setText("out");
    Qtheta = new QDoubleSpinBox();
    Qtheta->setValue(0.5);
    Qperplexity = new QSpinBox();
    Qperplexity->setValue(50);
    Qno_dims = new QSpinBox();
    Qno_dims->setValue(2);
    Qp_method = new QSpinBox();
    Qp_method->setValue(0);
    Qbin = new QSpinBox();
    Qbin->setMaximum(4096);
    Qbin->setValue(512);
    layout->addRow(new QLabel(tr("Input Location")), QinputLocation);
    layout->addRow(new QLabel(tr("Output Location")), QoutputLocation);
    layout->addRow(new QLabel(tr("theta")), Qtheta);
    layout->addRow(new QLabel(tr("perplexity")), Qperplexity);
    layout->addRow(new QLabel(tr("no_dims")), Qno_dims);
    layout->addRow(new QLabel(tr("p_method")), Qp_method);
    layout->addRow(new QLabel(tr("bin")), Qbin);
    layout->addRow(button);
    formGroupBox->setLayout(layout);

    consoleLabel = createLabel("click Run to start visualization.");

    BorderLayout *mainLayout = new BorderLayout;
    mainLayout->addWidget(d_plot, BorderLayout::Center);
    //mainLayout->addWidget(createLabel("North"), BorderLayout::North);
    //mainLayout->addWidget(createLabel("West"), BorderLayout::West);
    mainLayout->addWidget(formGroupBox, BorderLayout::East);
    //mainLayout->addWidget(createLabel("East 2") , BorderLayout::East);
    mainLayout->addWidget(consoleLabel, BorderLayout::South);
    setLayout(mainLayout);

    setWindowTitle(tr("Largeqt"));

    //setCentralWidget( d_plot );

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
        thread->runrun(QinputLocation->text(), Qno_dims->value(), Qtheta->value(), Qperplexity->value(), Qbin->value(), Qp_method->value(), 30);
    }
}
