#include "udpServerWidget.h"
#include <cstring>

udpServerWidget::udpServerWidget(uint16_t port,const std::string &ip,QWidget *parent)
    : QWidget(parent),
      currIter(0)
{      
    layout = new QGridLayout(this);

    ipLabel = new QLabel(("ip = " + ip).c_str());
    portLabel = new QLabel(("port = " + std::to_string(port)).c_str());

    timeoutSlider = new QSlider(Qt::Orientation::Vertical);
    timeoutSlider->setMaximum(timeout);
    timeoutSlider->setDisabled(true);

    layout->addWidget(ipLabel,0,0);
    layout->addWidget(portLabel,1,0);
    layout->addWidget(timeoutSlider,0,1,2,1);

    timer = new QTimer(this);

    for(int i = 0;i < blockCount*dataBlockSize;i++)
        buff[i] = 0;

    connect(timer,&QTimer::timeout,this,&udpServerWidget::TimerLoop);
    timer->start(25);
}

void udpServerWidget::handleBlock(dataBlock *block){
    currTimeout = 0;
    int buffId = (block->blockid+5)%blockCount;
    memcpy((char*)(buff + buffId*dataBlockSize),block->data,sizeof(float)*dataBlockSize);
}

float udpServerWidget::getNextValue(){
    float value = buff[currIter];
    buff[currIter] = 0;
    currIter = (currIter + 1)%(blockCount*dataBlockSize);
    return value;
}

void udpServerWidget::TimerLoop(){
    if(++currTimeout == timeout) emit Disconnected();
    timeoutSlider->setValue(currTimeout);
}