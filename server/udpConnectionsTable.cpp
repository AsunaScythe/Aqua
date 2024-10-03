#include "udpConnectionsTable.h"

#include <QMessageBox>
#include <QHeaderView>

udpConnections::udpConnections(QWidget *parent)
    : QWidget(parent)
{
    layout = new QGridLayout(this);
    portLabel = new QLabel("port");
    portEdit = new QLineEdit();
    startButton = new QPushButton("start");
    stopButton = new QPushButton("stop");
    stopButton->setVisible(false);

    connectionsWidget = new QTableWidget();
    connectionsWidget->setColumnCount(1);
    connectionsWidget->verticalHeader()->hide();
    connectionsWidget->horizontalHeader()->hide();
    
    layout->addWidget(portLabel,0,0);
    layout->addWidget(portEdit,0,1);
    layout->addWidget(startButton,1,0,1,2);
    layout->addWidget(stopButton,1,0,1,2);
    layout->addWidget(connectionsWidget,2,0,1,2);

    connect(startButton,&QPushButton::clicked,this,&udpConnections::start);
    connect(stopButton,&QPushButton::clicked,this,&udpConnections::stop);
    connect(this,&udpConnections::newConnections,this,&udpConnections::addConnections);
}
udpConnections::~udpConnections(){
    breakFlag = false;
    if(recvThread.joinable()) recvThread.join();
}

void udpConnections::start(){
    if(server.start(portEdit->text().toShort()) != 0){
        QMessageBox box;
        box.setText("Cannot create socket. Check port!!!");
        box.setWindowTitle("Error");
        box.exec();
    }
    else{
        portEdit->setDisabled(true);
        stopButton->setVisible(true);
        startButton->setVisible(false);

        breakFlag = true;
        recvThread = std::thread([&]{this->recvLoop();});
    }
}

float udpConnections::getNextValue(){
    std::lock_guard lock(mtx);
    float value = 0;
    for(auto i = connectionMap.begin();i != connectionMap.end();i++){
        value += i->second->getNextValue();
    }
    return value;
}

void udpConnections::stop(){
    breakFlag = false;
    recvThread.join();
    server.stop();
    portEdit->setDisabled(false);
    stopButton->setVisible(false);
    startButton->setVisible(true);
}

void udpConnections::recvLoop(){
    dataBlock block;
    sockaddr_in addr;
    while(breakFlag){
        if(server.recvFrom((void*)&block,sizeof(dataBlock),&addr) != 0){
            std::lock_guard lock(mtx);
            if(connectionMap.find(ntohs(addr.sin_port)) == connectionMap.end())
                emit newConnections(ntohs(addr.sin_port),QString(inet_ntoa(addr.sin_addr)));
            else
                connectionMap[ntohs(addr.sin_port)]->handleBlock(&block);
        }
    }
}

void udpConnections::addConnections(int port,QString ip){
    udpServerWidget *widget = new udpServerWidget(port,ip.toStdString());

    connect(widget,&udpServerWidget::Disconnected,this,&udpConnections::removeConnection);

    std::lock_guard lock(mtx);
    connectionMap.insert(std::make_pair(port,widget));

    connectionsWidget->insertRow(0);
    connectionsWidget->setRowHeight(0,200);
    connectionsWidget->setColumnWidth(0, connectionsWidget->viewport()->width());

    connectionsWidget->setCellWidget(0,0,widget);
}

void udpConnections::removeConnection(){
    std::lock_guard lock(mtx);
    for(int i = 0;i < connectionsWidget->rowCount();i++)
        if(connectionsWidget->cellWidget(i,0) == sender())
           connectionsWidget->removeRow(i);
    
    for(auto i = connectionMap.begin();i != connectionMap.end();i++)
        if(i->second == sender()){
            connectionMap.erase(i);
            return;
        }
}