#include "connectionAggregate.h"
#include <chrono>

using namespace std::chrono_literals;

connectionAggregate::connectionAggregate(QWidget *parent)
    : QWidget(parent)
{
    layout = new QGridLayout(this);
    tcpConnection = new connectionsTable();
    udpConnection = new udpConnections();

    layout->addWidget(tcpConnection,0,0);
    layout->addWidget(udpConnection,0,1);

    breakFlag = true;
    loopThread = std::thread([&]{this->loopFunction();});
}
connectionAggregate::~connectionAggregate(){
    breakFlag = false;
    loopThread.join();
}

void connectionAggregate::loopFunction(){
    auto step = 1000000000ns/frequency;
    auto time = std::chrono::steady_clock::now();
    while(breakFlag){
        float sum = 0;
        float value;
        std::this_thread::sleep_until(time += step);
        sum += udpConnection->getNextValue();
        sum += tcpConnection->getNextValue();
        emit newValue(sum);
    }
    
}