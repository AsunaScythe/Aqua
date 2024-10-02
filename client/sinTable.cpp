#include "sinTable.h"
#include <QHeaderView>

sinTable::sinTable(QWidget *parent)
    : QWidget(parent)
{
    layout = new QGridLayout(this);
    table = new QTableWidget();
    
    table->setColumnCount(2);
    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();

    addButton =  new QPushButton("+");

    layout->addWidget(addButton,0,0);
    layout->addWidget(table,1,0);

    connect(addButton,&QPushButton::clicked,this,&sinTable::addSine);
}


void sinTable::addSine(){
    std::lock_guard<std::mutex> lock(mtx);
    table->insertRow(0);
    table->setRowHeight(0,200);

    table->setColumnWidth(0,table->viewport()->width() - 50);
    table->setColumnWidth(1,50);

    sinWidget *widget = new sinWidget();
    QPushButton *removeButton = new QPushButton("-");

    table->setCellWidget(0,0,widget);
    table->setCellWidget(0,1,removeButton);

    connect(removeButton,&QPushButton::clicked,this,&sinTable::deleteSine);
    connect(widget,&sinWidget::valueChanged,this,&sinTable::valueChanged);

    emit valueChanged();
}


float sinTable::getValueFromPhase(float phase){
    std::lock_guard<std::mutex> lock(mtx);
    float sum = 0;
    for(int i = 0;i < table->rowCount();i++)
        sum += qobject_cast<sinWidget*>(table->cellWidget(i,0))->getValueFromPhase(phase);
    return sum;
}

void sinTable::deleteSine(){
    std::lock_guard<std::mutex> lock(mtx);
    for(int i = 0;i < table->rowCount();i++){
        if(table->cellWidget(i,1) == sender())
            table->removeRow(i);
        
    }
    emit valueChanged();
}
