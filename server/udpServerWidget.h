#ifndef UDP_SERVER_WIDGET_CXX
#define UDP_SERVER_WIDGET_CXX

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <string>
#include <QTimer>
#include <QSlider>

static const uint16_t dataBlockSize = 256;

static const uint16_t blockCount = 10;

#pragma pack(push,1)

struct dataBlock{
    uint64_t blockid;
    float data[dataBlockSize];
};

#pragma pack(pop)

class udpServerWidget : public QWidget{

static const uint16_t timeout = 120;

Q_OBJECT

public:

udpServerWidget(uint16_t port,const std::string &ip,QWidget *parent = nullptr);

float getNextValue();

void handleBlock(dataBlock *block);

signals:

void Disconnected();

private:

void TimerLoop();

QLabel *ipLabel;
QLabel *portLabel;
QGridLayout *layout;

QSlider *timeoutSlider;

uint16_t currIter;
float buff[blockCount*dataBlockSize];
QTimer *timer;

uint16_t currTimeout;

};


#endif