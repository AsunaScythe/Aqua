

#include <QApplication>
#include "MainWindow.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment (lib, "Ws2_32.lib")


int main(int argc,char *argv[]){

    WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) 
		exit(1);

    QApplication app(argc,argv);

    MainWindow window;

    window.setFixedWidth(1600);
    window.setFixedHeight(500);
    window.show();
    
    return app.exec();;
}