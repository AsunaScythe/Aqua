#ifndef PLOT_AGREGATE_CXX
#define PLOT_AGREGATE_CXX

#include <QScrollArea>
#include <QGridLayout>
#include "sliderWidget.h"
#include "plotWidget.h"
#include "zoomViewer.h"
#include "sinTable.h"
#include "connectionAggregate.h"

class plotAgregate : public QWidget{

Q_OBJECT

public:
    plotAgregate(QWidget *parent = nullptr);

private:

    PlotWidget *plot;
    sliderWidget *samplingRate;
    QGridLayout *layout;
    zoomViewer *viewer;
    sinTable *sine;
    connectionAggregate *agregate;
};



#endif