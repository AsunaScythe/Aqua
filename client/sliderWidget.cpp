#include "sliderWidget.h"

sliderWidget::sliderWidget(const QString & name,int from,int to,QWidget *parent)
    : QWidget(parent)
{
    layout = new QGridLayout(this);

    label = new QLabel(name);
    layout->addWidget(label,0,0);

    slider = new QSlider(Qt::Orientation::Vertical);
    slider->setMaximum(to);
    slider->setMinimum(from);

    layout->addWidget(slider,1,0);

    spin = new QSpinBox();
    spin->setMaximum(to);
    spin->setMinimum(from);

    layout->addWidget(spin,2,0);

    connect(spin,QOverload<int>::of(&QSpinBox::valueChanged),this,&sliderWidget::setValue);
    connect(slider,&QSlider::valueChanged,this,&sliderWidget::setValue);
}

int sliderWidget::getValue(){return slider->value();}


void sliderWidget::setValue(int value){
    spin->setValue(value);
    slider->setValue(value);
    emit valueChanged(value);
}