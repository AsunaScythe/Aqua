#ifndef SIN_TABLE_CXX
#define SIN_TABLE_CXX

#include <QTableWidget>
#include <QPushButton>
#include <mutex>

#include "sinWidget.h"
#include "refByPhase.h"

class sinTable : public QWidget ,public refByPhase{

Q_OBJECT

public:

sinTable(QWidget *parent = nullptr);

float getValueFromPhase(float phase) override;

signals:

void valueChanged();

private:

void addSine();
void deleteSine();

QTableWidget *table;
QGridLayout *layout;
QPushButton *addButton;
std::mutex mtx;

};


#endif