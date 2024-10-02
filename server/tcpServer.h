#ifndef TCP_SERVER_CXX
#define TCP_SERVER_CXX

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <inttypes.h>

class tcpServer{

public:

tcpServer();

~tcpServer();

int create(uint16_t localPort);

int waitConnection(sockaddr *client_addr);

void disconnect();

private:

SOCKET sock;

};

#endif