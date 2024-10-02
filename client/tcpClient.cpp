#include "tcpClient.h"

tcpClient::tcpClient(){}

tcpClient::~tcpClient(){}

int tcpClient::Connect(const std::string &remoteIp,uint16_t remotePort)
{

    sock = socket(AF_INET, SOCK_STREAM, NULL);
    SOCKADDR_IN addr;
	int addrLen = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr(remoteIp.c_str());

	addr.sin_port = htons(remotePort);
	addr.sin_family = AF_INET;

    return connect(sock, (SOCKADDR*)&addr, addrLen);
}

void tcpClient::disconnect(){closesocket(sock);}

int tcpClient::Send(char *buff,int size){
    int sended = 0;
    while(sended != size){
        int currSend = send(sock,buff + sended,size -sended,0);
        if(currSend == -1) return -1;
        sended += currSend;
    }
    return 0;
}
