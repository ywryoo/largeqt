#include "mainwindow.h"
#include "plot.h"
#include <qmath.h>
#include "pixelsne/LargeVis.h"
#include "ui_mainwindow.h"

static double randomValue()
{
    // a number between [ 0.0, 1.0 ]
    return ( qrand() % 100000 ) / 100000.0;
}

MainWindow::MainWindow(float *points, long long vertices, long long dims)
{
    ui = new Ui::MainWindow;
    ui->setupUi(this);

    vispoints = points;
    n_vertices = vertices;
    out_dims = dims;
    d_plot = new Plot( ui->scatterplot );
    d_plot->setTitle( "Scatter Plot" );

    //setCentralWidget( d_plot );

    // a million points
    setSamples();
}

MainWindow::~MainWindow()
{
    delete ui;
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
