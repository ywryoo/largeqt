#include "mainwindow.h"
#include "plot.h"
#include "pixelsne/LargeVis.h"
#include "pixelsne/pixelsne.h"
//#include "ui_mainwindow.h"
#include "borderlayout.h"
#include <QTextBrowser>
#include <QLabel>
#include <QtWidgets>
#include <QPushButton>
#include <QThread>
#include "workerthread.h"

MainWindow::MainWindow(float *points, long long vertices, long long dims)
{
    vispoints = points;
    n_vertices = vertices;
    out_dims = dims;

    d_plot = new Plot( this );

    d_plot->setTitle( "Scatter Plot" );

    QTextBrowser *centralWidget = new QTextBrowser;
    centralWidget->setPlainText(tr("Central widget"));
    QPushButton *button = new QPushButton("&Run", this);
    QWidget *formGroupBox = new QWidget;
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Input Location")), new QLineEdit);
    layout->addRow(new QLabel(tr("Output Location")), new QLineEdit);
    layout->addRow(new QLabel(tr("theta")), new QSpinBox);
    layout->addRow(new QLabel(tr("perplexity")), new QSpinBox);
    layout->addRow(new QLabel(tr("no_dims")), new QSpinBox);
    layout->addRow(new QLabel(tr("p_method")), new QSpinBox);
    layout->addRow(new QLabel(tr("bin")), new QSpinBox);
    layout->addRow(button);
    formGroupBox->setLayout(layout);

    BorderLayout *mainLayout = new BorderLayout;
    mainLayout->addWidget(d_plot, BorderLayout::Center);
    //mainLayout->addWidget(createLabel("North"), BorderLayout::North);
    //mainLayout->addWidget(createLabel("West"), BorderLayout::West);
    mainLayout->addWidget(formGroupBox, BorderLayout::East);
    //mainLayout->addWidget(createLabel("East 2") , BorderLayout::East);
    //mainLayout->addWidget(createLabel("South"), BorderLayout::South);
    setLayout(mainLayout);

    setWindowTitle(tr("Border Layout"));

    //setCentralWidget( d_plot );

   WorkerThread *thread = new WorkerThread;
    connect(thread, SIGNAL(resultReady(double*,int,int)), this, SLOT(setSamples(double*,int,int)));
    thread->runrun();

}

MainWindow::~MainWindow()
{
}

QLabel *MainWindow::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setFrameStyle(QFrame::Box | QFrame::Raised);
    return label;
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
