#ifndef UDP_SERVER_CXX
#define UDP_SERVER_CXX

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <inttypes.h>
#include <thread>

class udpServer {

public:

udpServer();

int start(uint16_t port);

void stop();

int recvFrom(void *buff,int len,sockaddr_in* from);

private:

int sock;

};

#endif
