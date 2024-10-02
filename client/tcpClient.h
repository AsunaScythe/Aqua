#ifndef TCP_CLIENT_CXX
#define TCP_CLIENT_CXX

#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

class tcpClient {

public:

    tcpClient();

    ~tcpClient();

    int Connect(const std::string &remoteIp,uint16_t remotePort);

    void disconnect();

    int Send(char *buff,int size);
    
private:
    SOCKET sock;
};

#endif