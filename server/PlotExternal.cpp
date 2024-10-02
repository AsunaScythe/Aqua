#include "PlotExternal.h"

#include <QPainter>

plotExternal::plotExternal(QWidget *parent)
    : QWidget(parent),
      currIter(0)
      {for(int i = 0;i < frequency;i++) buff[i] = 0;}

void plotExternal::paintEvent(QPaintEvent *event){

    QPainter painter(this);
    int width = painter.window().width();
    int height = painter.window().height()/2;

    float X = 0;
    float prevY = buff[currIter];
    float stepX = width/static_cast<float>(frequency);
    
    for(int i = 1;i < frequency;i++){
        
        float nextY = buff[(currIter + i)%frequency];
        painter.setPen(QColor(0,0,0,255));
        painter.drawLine(X,height - prevY,X + stepX,height - nextY);

        painter.setPen(QColor(55,55,55,55));
        painter.drawLine(X,0,X,height*2-1);

        X += stepX;
        prevY = nextY;
    }

    painter.drawLine(0,height,width-1,height);
}

void plotExternal::addValue(float value){
    buff[currIter++] = value;
    if(currIter == frequency) currIter = 0;
    update();
}