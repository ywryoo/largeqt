/// source code from qwt examples
/// Modified by Ryangwook Ryoo, 2017

#include "plot.h"
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_curve.h>
#include <qwt_color_map.h>
#include <qwt_legend.h>
#include "huecolormap.h"

class DistancePicker: public QwtPlotPicker
{
public:
    DistancePicker( QWidget *canvas ):
        QwtPlotPicker( canvas )
    {
        setTrackerMode( QwtPicker::ActiveOnly );
        setStateMachine( new QwtPickerDragLineMachine() );
        setRubberBand( QwtPlotPicker::PolygonRubberBand );
    }

    virtual QwtText trackerTextF( const QPointF &pos ) const
    {
        QwtText text;

        const QPolygon points = selection();
        if ( !points.isEmpty() )
        {
            QString num;
            num.setNum( QLineF( pos, invTransform( points[0] ) ).length() );

            QColor bg( Qt::white );
            bg.setAlpha( 200 );

            text.setBackgroundBrush( QBrush( bg ) );
            text.setText( num );
        }
        return text;
    }
};

Plot::Plot( QWidget *parent ):
    QwtPlot( parent ),
    default_curve( NULL )
{
    canvas()->setStyleSheet(
        "border: 2px solid Black;"
        "border-radius: 15px;"
        "background-color: qlineargradient( x1: 0, y1: 0, x2: 0, y2: 1,"
            "stop: 0 LemonChiffon, stop: 1 PaleGoldenrod );"
    );
    QwtLegend *legend = new QwtLegend;
    legend->setDefaultItemMode( QwtLegendData::Checkable );
    insertLegend( legend, QwtPlot::RightLegend );

    // attach curve
    default_curve = new QwtPlotCurve( "Scattered Points" );
    default_curve->setPen( QColor( "Purple" ) );

    // when using QwtPlotCurve::ImageBuffer simple dots can be
    // rendered in parallel on multicore systems.
    default_curve->setRenderThreadCount( 0 ); // 0: use QThread::idealThreadCount()


    setSymbol( NULL );

    // panning with the left mouse button
    (void )new QwtPlotPanner( canvas() );

    // zoom in/out with the wheel
    QwtPlotMagnifier *magnifier = new QwtPlotMagnifier( canvas() );
    magnifier->setMouseButton( Qt::NoButton );

    // distanve measurement with the right mouse button
    //DistancePicker *picker = new DistancePicker( canvas() );
    //picker->setMousePattern( QwtPlotPicker::MouseSelect1, Qt::RightButton );
    //picker->setRubberBandPen( QPen( Qt::blue ) );
}

void Plot::setSymbol( QwtSymbol *symbol )
{
    default_curve->setSymbol( symbol );

    if ( symbol == NULL )
    {
        default_curve->setStyle( QwtPlotCurve::Dots );
    }
}

void Plot::setSamples( const QVector<QPointF> &samples )
{
    for(int i = 0; i < label_num; i++)
    {
        d_curves[i]->detach();
        delete d_curves[i];
    }
    label_num = 0;
    
    default_curve->attach( this );

    default_curve->setPaintAttribute( 
        QwtPlotCurve::ImageBuffer, samples.size() > 1000 );

    default_curve->setSamples( samples );
}

void Plot::setLabels(int max)
{
    default_curve->detach();

    for(int i = 0; i < label_num; i++)
    {
        d_curves[i]->detach();
        delete d_curves[i];
    }
    label_num = max;
    d_curves = new QwtPlotCurve*[label_num];
	QwtInterval a = QwtInterval(0,label_num);
    HueColorMap *aa = new HueColorMap;
    for(int i = 0; i < label_num; i++)
    {
        d_curves[i] = new QwtPlotCurve(QString("%1").arg(QString::number(i)));
        QColor bb = aa->color(a, i);
        d_curves[i]->setPen( bb );
        d_curves[i]->setStyle( QwtPlotCurve::Dots );
        d_curves[i]->setPaintAttribute( 
            QwtPlotCurve::ImageBuffer, true );
        // when using QwtPlotCurve::ImageBuffer simple dots can be
        // rendered in parallel on multicore systems.
        d_curves[i]->setRenderThreadCount( 0 ); // 0: use QThread::idealThreadCount()

        d_curves[i]->attach( this );
    }
}

void Plot::setSamplesWithLabels(double* Y, int* data_labels, int N, int no_dims)
{
        QPolygonF samples[label_num];
        for(int i = 0; i < label_num; i++) samples[i] = QPolygonF();
        if(no_dims == 2) {
            for ( long long i = 0; i < N; i++ )
            {
                samples[data_labels[i]] += QPointF(Y[i*no_dims],Y[i*no_dims+1] );
            }

        }
        for(int i = 0; i < label_num; i++) d_curves[i]->setSamples(samples[i]);
}
