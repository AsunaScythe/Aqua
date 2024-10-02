#include "PlotWidget.h"

#include <QPainter>

using namespace std::chrono_literals;

PlotWidget::PlotWidget(QWidget *parent)
    : QWidget(parent){}

PlotWidget::~PlotWidget(){}

void PlotWidget::paintEvent(QPaintEvent *event){

    QPainter painter(this);
    int width = painter.window().width();
    int height = painter.window().height()/2;

    float X = 0;
    float prevY = source->getValueFromPhase(0);
    float stepX = width/static_cast<float>(samplingRate);
    
    for(int i =1;i <= samplingRate;i++){
        float nextY = source->getValueFromPhase(2 * M_PI * i/samplingRate) + 0.5;

        painter.setPen(QColor(0,0,0,255));
        painter.drawLine(X,height - prevY,X + stepX,height - nextY);

        painter.setPen(QColor(55,55,55,55));
        painter.drawLine(X,0,X,height*2-1);

        X += stepX;
        prevY = nextY;
    }

    painter.drawLine(0,height,width-1,height);
    
}

void PlotWidget::setSamplingRate(int SR){
    samplingRate = SR;
    update();
}

void PlotWidget::setSource(refByPhase * src){
    source = src;
    update();
}