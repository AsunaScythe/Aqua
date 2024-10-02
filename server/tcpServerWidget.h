#ifndef TCP_SERVER_WIDGET_CXX
#define TCP_SERVER_WIDGET_CXX

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

class tcpServerWidget : public QWidget{

Q_OBJECT

public:

tcpServerWidget(int sock,const std::string &ip,uint16_t port,QWidget *paren = nullptr);
~tcpServerWidget();

int Recv(void* data,int len);

signals:

void disconected();

private:

QLabel *ipLabel;
QLabel *portLabel;
QGridLayout *layout;

int sock;

};



#endif