#include "zoomViewer.h"

zoomViewer::zoomViewer(QWidget *parent)
    : QScrollArea(parent),
      currZoom(1){}

void zoomViewer::wheelEvent(QWheelEvent * event){
    int degrees = event->delta();

    float prevZoom = currZoom;
    if(degrees > 0) currZoom *= 1.1;
    else            currZoom /= 1.1;

    if(currZoom > maxZoom) currZoom = maxZoom;
    if(currZoom < 1) currZoom = 1;

    widget()->resize(viewport()->size().width()*currZoom,viewport()->size().height());

    int halfPageStep = horizontalScrollBar()->pageStep()/2;

    int newValue = (horizontalScrollBar()->value() + halfPageStep)*currZoom/prevZoom;
    
    int shift = (halfPageStep*currZoom/prevZoom - halfPageStep) * (event->pos().x() - halfPageStep) / halfPageStep;
    
    newValue += shift;

    horizontalScrollBar()->setValue(newValue - halfPageStep);
};