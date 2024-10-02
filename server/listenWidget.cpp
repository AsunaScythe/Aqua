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

    table = new connectionsTable(plot);

    connect(table,&connectionsTable::newValue,plot,&plotExternal::addValue);

    layout->addWidget(viewer,0,0);
    layout->addWidget(table,0,1);

}