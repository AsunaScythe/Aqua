#ifndef CONNECT_WIDGET_CXX
#define CONNECT_WIDGET_CXX

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTimer>
#include <thread>

#include "refByPhase.h"
#include "tcpClient.h"

class connectWidget : public QWidget{

const uint16_t frequency = 1024;

Q_OBJECT

public:

connectWidget(QWidget *parent = nullptr);

~connectWidget();

void setSource(refByPhase * source);

signals:

void serverDissconect();

private:

void sendLoop();

void ConnectPressed();

void DisconnectPressed();

QPushButton *connectButton;
QPushButton *disconnectButton;
QGridLayout *layout;
QLineEdit   *ipEdit;
QLineEdit   *portEdit;
QLabel      *ipLabel;
QLabel      *portLabel;

bool breakFlag;
std::thread loopThread;

tcpClient client;

refByPhase *source;

};

#endif