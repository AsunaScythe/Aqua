#ifndef SLIDER_WIDGET_CXX
#define SLIDER_WIDGET_CXX

#include <QWidget>
#include <QSlider>
#include <QSpinBox>
#include <QLabel>
#include <QGridLayout>

class sliderWidget : public QWidget{
    Q_OBJECT

public:
    sliderWidget(const QString & name,int from,int to,QWidget *parent = nullptr);
    int getValue();

void setValue(int);

signals:

void valueChanged(int);

private:
    QSlider *slider;
    QGridLayout *layout;
    QLabel *label;
    QSpinBox *spin;

};


#endif