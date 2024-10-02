#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      {setCentralWidget(new plotAgregate());}

MainWindow::~MainWindow(){}