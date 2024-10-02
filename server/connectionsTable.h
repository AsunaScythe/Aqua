#ifndef CONNECTIONS_TABLE_CXX
#define CONNECTIONS_TABLE_CXX

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QHeaderView>
#include <QTableWidget>
#include <thread>
#include <mutex>
#include <chrono>
#include "tcpServerWidget.h"
#include "tcpServer.h"
#include "PlotExternal.h"

class connectionsTable : public QWidget{

const uint16_t frequency = 1024;

Q_OBJECT

public: 

connectionsTable(QWidget *parent = nullptr);
~connectionsTable();

signals:

void newConnection(int sock,int port,QString ip);

void newValue(float value);

private:

void startListen();

void stopListen();

void connectionLoop();

void UpdateLoop();

void disconnectPressed();

void disconnected();

void createNewConnection(int sock,int port,QString ip);

QGridLayout *layout;
QLineEdit *portEdit;
QLabel    *portLabel;
QPushButton *connectButton;
QPushButton *disconnectButton;


QTableWidget *connectTable;
bool breakFlag;
std::mutex mtx;
std::thread listenThread;
std::thread updateThread;

tcpServer server;


};

#endif