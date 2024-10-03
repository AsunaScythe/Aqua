#include "udpSenderWidget.h"
#include <chrono>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std::chrono_literals;

udpSenderWidget::udpSenderWidget(QWidget *parent)
    : QWidget(parent)
{
    layout = new QGridLayout(this);
    layout->setAlignment(Qt::Alignment::enum_type::AlignTop);

    startButton = new QPushButton("start");
    stopButton = new QPushButton("stop");
    stopButton->setVisible(false);

    ipLabel = new QLabel("ip");
    portLabel = new QLabel("port");

    ipEdit = new QLineEdit();
    portEdit = new QLineEdit();

    layout->addWidget(ipLabel,0,0);
    layout->addWidget(ipEdit,0,1);
    layout->addWidget(portLabel,1,0);
    layout->addWidget(portEdit,1,1);
    layout->addWidget(startButton,2,0,1,2);
    layout->addWidget(stopButton,2,0,1,2);

    connect(startButton,&QPushButton::clicked,this,&udpSenderWidget::startPressed);
    connect(stopButton,&QPushButton::clicked,this,&udpSenderWidget::stopPressed);
    connect(this,&udpSenderWidget::sendFailed,this,&udpSenderWidget::stopPressed);
}

udpSenderWidget::~udpSenderWidget(){
    breakFlag = false;
    if(sendThread.joinable())sendThread.join();
}

void udpSenderWidget::setSource(refByPhase *src){source = src;}

void udpSenderWidget::startPressed(){
    ipEdit->setDisabled(true);
    portEdit->setDisabled(true);
    startButton->setVisible(false);
    stopButton->setVisible(true);

    breakFlag = true;
    sendThread = std::thread([&]{this->sendLoop();});

}

void udpSenderWidget::stopPressed(){

    breakFlag = false;
    sendThread.join();

    ipEdit->setDisabled(false);
    portEdit->setDisabled(false);
    stopButton->setVisible(false);
    startButton->setVisible(true);
}


void udpSenderWidget::sendLoop(){
    auto time = std::chrono::steady_clock::now();
    auto timeStep = 1000000000ns * dataBlockSize / frequency;
    dataBlock data;
    data.blockid = 0;

    std::string ip = ipEdit->text().toStdString();
    uint16_t port = portEdit->text().toShort();

    uint16_t currPhase = 0;
    while(breakFlag){
        for(int i = 0;i < dataBlockSize;i++){
            data.data[i] = source->getValueFromPhase(2 * M_PI * currPhase / frequency);
            currPhase = (currPhase + 1)%frequency;
        }

        std::this_thread::sleep_until(time += timeStep);

        if(client.sendTo(ip,port,&data,sizeof(data)) != 0)
            emit sendFailed();

        data.blockid++;

    }
}