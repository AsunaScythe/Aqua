#ifndef LISTEN_VIDGET_CXX
#define LISTEN_VIDGET_CXX

#include <QWidget>
#include <QGridLayout>
#include "zoomViewer.h"
#include "connectionsTable.h"
#include "PlotExternal.h"

class listenWidget : public QWidget{

const uint16_t frequency = 1024;

Q_OBJECT

public:

listenWidget(QWidget *parent = nullptr);

private:

QGridLayout *layout;
connectionsTable *table;
plotExternal *plot;
zoomViewer *viewer;

};

#endif