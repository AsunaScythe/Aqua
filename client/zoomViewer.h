#ifndef ZOOM_VIEWER_CXX
#define ZOOM_VIEWER_CXX

#include <QScrollArea>
#include <QWheelEvent>
#include <QScrollBar>

class zoomViewer : public QScrollArea{

Q_OBJECT

const float maxZoom = 100;

public:
    zoomViewer(QWidget *parent = nullptr);

    void wheelEvent(QWheelEvent * event) override;

private:

    float currZoom;

};


#endif