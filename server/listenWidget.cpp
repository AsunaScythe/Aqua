#include "listenWidget.h"

listenWidget::listenWidget(QWidget *parent)
    : QWidget(parent)
{
    layout = new QGridLayout(this);
    layout->setColumnMinimumWidth(0,1024);

    plot = new plotExternal();
    plot->resize(1024,500);
    viewer = new zoomViewer();
    viewer->setWidget(plot);

    agregate = new connectionAggregate(plot);

    connect(agregate,&connectionAggregate::newValue,plot,&plotExternal::addValue);

    layout->addWidget(viewer,0,0);
    layout->addWidget(agregate,0,1);

}