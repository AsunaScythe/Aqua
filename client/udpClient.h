#ifndef UDP_CLIENT_CXX
#define UDP_CLIETN_CXX

#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

class udpClient{

public:

udpClient();

~udpClient();

int sendTo(const std::string &ip,uint16_t port,void *data,int len);

private:

int sock;

};

#endif