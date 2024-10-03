#include "connectWidget.h"
#include <QMessageBox>

#define _USE_MATH_DEFINES
#include <math.h>
#include <chrono>

using namespace std::chrono_literals;

connectWidget::connectWidget(QWidget *parent)
    : QWidget(parent)
{
    layout = new QGridLayout(this);
    layout->setAlignment(Qt::Alignment::enum_type::AlignTop);

    connectButton = new QPushButton("connect");
    disconnectButton = new QPushButton("disconnect");
    disconnectButton->setVisible(false);

    ipLabel = new QLabel("ip");
    portLabel = new QLabel("port");

    ipEdit = new QLineEdit();
    portEdit = new QLineEdit();

    layout->addWidget(ipLabel,0,0);
    layout->addWidget(ipEdit,0,1);

    layout->addWidget(portLabel,1,0);
    layout->addWidget(portEdit,1,1);

    layout->addWidget(connectButton,2,0,1,2);
    layout->addWidget(disconnectButton,2,0,1,2);

    connect(connectButton,&QPushButton::clicked,this,&connectWidget::ConnectPressed);
    connect(disconnectButton,&QPushButton::clicked,this,&connectWidget::DisconnectPressed);
    connect(this,&connectWidget::serverDissconect,this,&connectWidget::DisconnectPressed);
}

connectWidget::~connectWidget(){
    breakFlag = false;
    if(loopThread.joinable()) loopThread.join();
}


void connectWidget::ConnectPressed(){
    int ret = client.Connect(ipEdit->text().toStdString(),portEdit->text().toInt());
    if(ret != 0){
        QMessageBox box;
        box.setText("Cannot connect. Check ip and port");
        box.setWindowTitle("Error");
        box.exec();
    }else{
        connectButton->setVisible(false);
        disconnectButton->setVisible(true);
        ipEdit->setEnabled(false);
        portEdit->setEnabled(false);

        breakFlag = true;
        loopThread = std::thread([&]{this->sendLoop();});
    }
}

void connectWidget::DisconnectPressed(){

    breakFlag = false;
    loopThread.join();
    client.disconnect();
    disconnectButton->setVisible(false);
    connectButton->setVisible(true);
    ipEdit->setEnabled(true);
    portEdit->setEnabled(true);
}

void connectWidget::sendLoop(){
    float value = 0;
    auto step = 1000000000ns/frequency;
    auto time = std::chrono::steady_clock::now();
    int i = 0;
    while(breakFlag){
        value = source->getValueFromPhase(2 * M_PI * i / frequency);
        if(client.Send(reinterpret_cast<char*>(&value),sizeof(value)) == -1){
            emit serverDissconect();
            return;
        }
        i = (i+1)%frequency;
        std::this_thread::sleep_until(time += step);
    }
}

void connectWidget::setSource(refByPhase * src){source = src;}