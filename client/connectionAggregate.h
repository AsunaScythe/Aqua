#ifndef CONNECTION_AGGREGATE_CXX
#define CONNECTION_AGGREGATE_CXX

#include <QWidget>
#include <QComboBox>
#include <QGridLayout>
#include "connectWidget.h"
#include "udpSenderWidget.h"

class connectionAggregate : public QWidget{

Q_OBJECT

public:

connectionAggregate(refByPhase *source,QWidget *parent = nullptr);

private:

void changeConnections(int);

QGridLayout *layout;
QComboBox *connectionsBox;
refByPhase *source;
QWidget *currWidget;

};

#endif