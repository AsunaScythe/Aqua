#include "tcpServerWidget.h"

tcpServerWidget::tcpServerWidget(int sock,const std::string &ip,uint16_t port,QWidget *parent)
    : QWidget(parent),
      sock(sock)
{   
    layout = new QGridLayout(this);

    ipLabel = new QLabel(("ip = " + ip).c_str());
    portLabel = new QLabel(("port = " + std::to_string(port)).c_str());

    layout->addWidget(ipLabel,0,0);
    layout->addWidget(portLabel,1,0);
}

int tcpServerWidget::Recv(void* data,int len){
    int received = 0;
    while(received != len){
        int ret = recv(sock,(char*)data + received,len - received,0);
        if(ret == 0){
            emit disconected();
            return -1;
        }
        if(ret == -1) return -1;
        received += ret;
    }
    return 0;
}

tcpServerWidget::~tcpServerWidget(){
    shutdown(sock,SD_BOTH);
    closesocket(sock);}