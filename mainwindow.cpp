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

    // Define some variables
    int     origN;
    int     N;
    int     D;
    int     no_dims;
    double  perplexity;
    double  theta;
    double* data;
    unsigned int bins;
    int     p_method;
    int rand_seed = 30;
    PixelSNE* pixelsne = new PixelSNE();

    // #ifdef USE_BITWISE_OP
    //     printf("pixelsne.cpp USE_BITWISE_OP\n");
    // #else
    //     printf("pixelsne.cpp not USE_BITWISE_OP\n");
    // #endif

    // Read the parameters and the dataset
    if(pixelsne->load_data(&data, &origN, &D, &no_dims, &theta, &perplexity, &bins, &p_method, &rand_seed)) {
        // Make dummy landmarks
        N = origN;

        int* landmarks = (int*) malloc(N * sizeof(int));
        if(landmarks == NULL) { printf("Memory allocation failed!\n"); exit(1); }
        for(int n = 0; n < N; n++) landmarks[n] = n;

        double* Y = (double*) malloc(N * no_dims * sizeof(double));
        double* costs = (double*) calloc(N, sizeof(double));
        if(Y == NULL || costs == NULL) { printf("Memory allocation failed!\n"); exit(1); }

        pixelsne->run(data, N, D, Y, no_dims, perplexity, theta, bins, p_method, rand_seed, false);
        setSamples(Y, N, no_dims);

    }



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

void MainWindow::setSamples( )
{
    QPolygonF samples;

    if(out_dims == 2) {
        for ( long long i = 0; i < n_vertices; i++ )
        {

            samples += QPointF( vispoints[i*out_dims], vispoints[i*out_dims+1] );
        }

    }

    d_plot->setSamples( samples );
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
}
