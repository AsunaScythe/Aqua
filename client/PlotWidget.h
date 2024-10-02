#ifndef PLOT_WIDGET_CXX
#define PLOT_WIDGET_CXX

#include "sinWidget.h"
#include <QWidget>

class PlotWidget : public QWidget{
    Q_OBJECT

public:

    PlotWidget(QWidget *parent = nullptr);
    ~PlotWidget();

    void setSource(refByPhase * source);
    void setSamplingRate(int);

private:

    void paintEvent(QPaintEvent *event) override;

    refByPhase *source;
    int samplingRate;
    float currZoom = 1;
    sinWidget *sine;
};



#endif