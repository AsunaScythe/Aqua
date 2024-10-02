#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      {setCentralWidget(new listenWidget());}

MainWindow::~MainWindow(){}