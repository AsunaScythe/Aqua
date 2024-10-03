#ifndef UDP_SENDER_WIDGET_CXX
#define UDP_SENDER_WIDGET_CXX

#include <QWidget>
#include <QPushButton>
#include <QlineEdit>
#include <QLabel>
#include <QGridLayout>
#include <thread>

#include "refByPhase.h"
#include "udpClient.h"

class udpSenderWidget : public QWidget{

static const uint16_t dataBlockSize = 256;

#pragma pack(push,1)

struct dataBlock{
    uint64_t blockid;
    float data[dataBlockSize];
};

#pragma pack(pop)

const uint16_t frequency = 1024;

Q_OBJECT

public:

udpSenderWidget(QWidget *parent = nullptr);

~udpSenderWidget();

void setSource(refByPhase *src);

signals:

void sendFailed();

private:

void sendLoop();

void startPressed();

void stopPressed();

QGridLayout *layout;
QPushButton *startButton;
QPushButton *stopButton;

QLabel *ipLabel;
QLabel *portLabel;
QLineEdit *ipEdit;
QLineEdit *portEdit;

refByPhase *source;

bool breakFlag;
std::thread sendThread;

udpClient client;

};


#endif