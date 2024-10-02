#ifndef PLOT_EXTERNAL_CXX
#define PLOT_EXTERNAL_CXX

#include <QWidget>

class plotExternal : public QWidget{

Q_OBJECT

const uint16_t frequency = 1024;

public:

plotExternal(QWidget *parent = nullptr);

void addValue(float value);

private:

void paintEvent(QPaintEvent *event) override;

float buff[1024];
int currIter;

};


#endif