#ifndef SIN_WIDGET_CXX
#define SIN_WIDGET_CXX

#include <QWidget>
#include <QGridLayout>

#define _USE_MATH_DEFINES
#include <math.h>

#include "sliderWidget.h"
#include "refByPhase.h"

class sinWidget : public QWidget , public refByPhase{
    Q_OBJECT

const uint16_t Frequency = 1024;
const uint16_t Phase = 200;
const uint16_t Amplitude = 100;

public:

sinWidget(QWidget * parent = nullptr);
~sinWidget(){}

float getValueFromPhase(float p) override;

signals:

void valueChanged();

private:

QGridLayout *layout;
sliderWidget *amplitude;
sliderWidget *phase;
sliderWidget *frequency;

};

#endif