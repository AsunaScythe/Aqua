#include "connectionAggregate.h"

connectionAggregate::connectionAggregate(refByPhase *src,QWidget *parent)
    : QWidget(parent),
      source(src)
{
    layout = new QGridLayout(this);
    connectionsBox = new QComboBox();
    connectionsBox->addItems(QStringList()<<"TCP"<<"UDP");
    layout->addWidget(connectionsBox,0,0);

    connectWidget *widget= new connectWidget();
    widget->setSource(source);

    currWidget = widget;

    layout->addWidget(widget,1,0);

    connect(connectionsBox,QOverload<int>::of(&QComboBox::currentIndexChanged),this,&connectionAggregate::changeConnections);

}

void connectionAggregate::changeConnections(int row){
    layout->removeWidget(currWidget);
    delete currWidget;
    switch(row){
        case 0:{
            connectWidget *widget= new connectWidget();
            widget->setSource(source);
            currWidget = widget;
        }break;
        case 1:{
            udpSenderWidget *widget = new udpSenderWidget();
            widget->setSource(source);
            currWidget = widget;
        }break;
    }
    layout->addWidget(currWidget,1,0);
}