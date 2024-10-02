#ifndef MAIN_WINDOW_CXX
#define MAIN_WINDOW_CXX

#include <QMainWindow>
#include "listenWidget.h"

class MainWindow : public QMainWindow{
    Q_OBJECT

public:

MainWindow(QWidget *parent = nullptr);
~MainWindow();

};

#endif