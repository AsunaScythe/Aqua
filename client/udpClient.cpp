#include "udpClient.h"

#include <cassert>

udpClient::udpClient()
    : sock(socket(AF_INET, SOCK_DGRAM, 0)){}

udpClient::~udpClient(){closesocket(sock);}

int udpClient::sendTo(const std::string &ip,uint16_t port,void *data,int len){
    sockaddr_in addr;
    addr.sin_family = AF_INET; 
    addr.sin_port = htons(port); 
    addr.sin_addr.s_addr = inet_addr(ip.c_str());

    int ret = sendto(sock,(char*)data,len,0,(sockaddr*)&addr,sizeof(sockaddr_in));
    if(ret != len) return -1;
    else return 0;
}