#include "plotAgregate.h"


plotAgregate::plotAgregate(QWidget *parent)
    : QWidget(parent)
{
    layout = new QGridLayout(this);
    layout->setColumnMinimumWidth(0,1024);

    samplingRate = new sliderWidget("SamplingRate",0,2048);

    plot = new PlotWidget();
    plot->resize(1024,500);

    sine = new sinTable();
    plot->setSource(sine);

    viewer = new zoomViewer();
    viewer->setWidget(plot);
   
    connectW = new connectWidget();
    connectW->setSource(sine);

    layout->addWidget(viewer,0,0); 
    layout->addWidget(samplingRate,0,1);
    layout->addWidget(sine,0,2);
    layout->addWidget(connectW,0,3);

    connect(samplingRate,&sliderWidget::valueChanged,plot,&PlotWidget::setSamplingRate);
    connect(sine,&sinTable::valueChanged,plot,QOverload<>::of(&PlotWidget::update));

    samplingRate->setValue(1024);
}
