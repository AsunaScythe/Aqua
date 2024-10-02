#include "sinWidget.h"

sinWidget::sinWidget(QWidget *parent)
    :QWidget(parent)
{
    layout = new QGridLayout(this);

    amplitude = new sliderWidget("A",0,Amplitude);
    phase = new sliderWidget("P",0,Phase);
    frequency = new sliderWidget("F",0,Frequency);

    layout->addWidget(amplitude,0,0);
    layout->addWidget(phase,0,1);
    layout->addWidget(frequency,0,2);

    connect(amplitude,&sliderWidget::valueChanged,this,&sinWidget::valueChanged);
    connect(phase,&sliderWidget::valueChanged,this,&sinWidget::valueChanged);
    connect(frequency,&sliderWidget::valueChanged,this,&sinWidget::valueChanged);

}

float sinWidget::getValueFromPhase(float p){
    return amplitude->getValue() * cos(p * frequency->getValue() +  2 * M_PI * phase->getValue()/Phase);
}
