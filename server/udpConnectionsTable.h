#ifndef UDP_CONNECTIONS_TABLE_CXX
#define UDP_CONNECTIONS_TABLE_CXX

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QLabel>
#include <QTableWidget>
#include <QGridLayout>
#include <QPushButton>
#include <thread>
#include <map>
#include <mutex>

#include "udpServerWidget.h"
#include "udpServer.h"

class udpConnections : public QWidget{

Q_OBJECT

public:

udpConnections(QWidget *parent = nullptr);
~udpConnections();

float getNextValue();

signals:

void newConnections(int port,QString ip);

private:

void addConnections(int port,QString ip);

void removeConnection();

void recvLoop();

void start();

void stop();

QGridLayout *layout;
QLabel *portLabel;
QLineEdit *portEdit;

QPushButton *startButton;
QPushButton *stopButton;

QTableWidget *connectionsWidget;

bool breakFlag;
std::thread recvThread;

std::map<int,udpServerWidget*> connectionMap;

std::mutex mtx;

udpServer server;

};

#endif