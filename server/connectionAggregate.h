#ifndef CONNECTION_AGGREGATE_CXX
#define CONNECTION_AGGREGATE_CXX

#include <QWidget>
#include <QGridLayout>
#include <thread>
#include "connectionsTable.h"
#include "udpConnectionsTable.h"

class connectionAggregate: public QWidget{

static const uint16_t frequency = 1024;

Q_OBJECT

public:

connectionAggregate(QWidget *parent = nullptr);
~connectionAggregate();

signals:

void newValue(float value);

private:

void loopFunction();

QGridLayout *layout;
connectionsTable *tcpConnection;
udpConnections   *udpConnection;

bool breakFlag;
std::thread loopThread;

};

#endif