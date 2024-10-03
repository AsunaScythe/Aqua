#include "connectionsTable.h"

using namespace std::chrono_literals;

connectionsTable::connectionsTable(QWidget * parent)
    : QWidget(parent)
{
    layout = new QGridLayout(this);

    portEdit = new QLineEdit();
    portLabel = new QLabel("port");

    connectButton = new QPushButton("connect");

    disconnectButton = new QPushButton("disconnect");
    disconnectButton->setVisible(false);

    connectTable = new QTableWidget();
    connectTable->setColumnCount(2);
    connectTable->verticalHeader()->hide();
    connectTable->horizontalHeader()->hide();

    layout->addWidget(portLabel,0,0);
    layout->addWidget(portEdit,0,1);
    layout->addWidget(connectButton,1,0,1,2);
    layout->addWidget(disconnectButton,1,0,1,2);
    layout->addWidget(connectTable,2,0,1,2);

    connect(connectButton,&QPushButton::clicked,this,&connectionsTable::startListen);
    connect(this,&connectionsTable::newConnection,this,&connectionsTable::createNewConnection);
    connect(disconnectButton,&QPushButton::clicked,this,&connectionsTable::stopListen);
}

connectionsTable::~connectionsTable(){
    breakFlag = false;
    if(listenThread.joinable()) listenThread.join();
}

void connectionsTable::startListen(){
    if(server.create(portEdit->text().toInt()) != 0){
        QMessageBox box;
        box.setText("Cannot create socket. Check port!!!");
        box.setWindowTitle("Error");
        box.exec();
    }else{
        connectButton->setVisible(false);
        disconnectButton->setVisible(true);
        portEdit->setDisabled(true);
        breakFlag = true;
        listenThread = std::thread([&]{this->connectionLoop();});
    }
}

void connectionsTable::stopListen(){

    breakFlag = false;
    listenThread.join();

    server.disconnect();

    connectTable->setRowCount(0);

    connectButton->setVisible(true);
    disconnectButton->setVisible(false);
    portEdit->setDisabled(false);
}

void connectionsTable::disconnectPressed(){
    std::lock_guard lock(mtx);
    for(int i = 0;i < connectTable->rowCount();i++)
        if(connectTable->cellWidget(i,1) == sender()){
            connectTable->removeRow(i);
            return;
        }
}

void connectionsTable::createNewConnection(int sock,int port,QString ip){

    tcpServerWidget* widget = new tcpServerWidget(sock,ip.toStdString(),port);

    QPushButton *deleteButton = new QPushButton("disconnect");

    connect(deleteButton,&QPushButton::clicked,this,&connectionsTable::disconnectPressed);
    connect(widget,&tcpServerWidget::disconected,this,&connectionsTable::disconnected);

    std::lock_guard<std::mutex> lock(mtx);
    connectTable->insertRow(0);
    connectTable->setCellWidget(0,0,widget);
    connectTable->setCellWidget(0,1,deleteButton);

    connectTable->setColumnWidth(0,connectTable->viewport()->width() - 150);
    connectTable->setColumnWidth(1,150);
    connectTable->setRowHeight(0,100);
}

void connectionsTable::connectionLoop(){
    while(breakFlag){
        int sock;
        sockaddr_in addr;
        if(sock = server.waitConnection((sockaddr*)&addr)){
            u_long mode = 1;
            ioctlsocket(sock, FIONBIO, &mode);
            emit newConnection(sock,ntohs(addr.sin_port),QString(inet_ntoa(addr.sin_addr)));
        }
    } 
}

float connectionsTable::getNextValue(){
    float sum = 0;
    float value;
    std::lock_guard lock(mtx);
    for(int i = 0;i < connectTable->rowCount();i++)
        if(qobject_cast<tcpServerWidget*>(connectTable->cellWidget(i,0))->Recv(&value,sizeof(value)) != -1){
            sum += value;
    }
    return sum;
}

void connectionsTable::disconnected(){
    std::lock_guard<std::mutex> lock(mtx);
    for(int i = 0;i < connectTable->rowCount();i++)
        if(connectTable->cellWidget(i,0) == sender()){
            connectTable->removeRow(i);
            return;
        }
}