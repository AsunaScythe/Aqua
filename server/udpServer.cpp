#include "udpServer.h"

udpServer::udpServer(){}

int udpServer::start(uint16_t port){
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    u_long mode = 1;
    ioctlsocket(sock, FIONBIO, &mode);

    sockaddr_in addr;
    
    addr.sin_family = AF_INET; 
    addr.sin_addr.s_addr = INADDR_ANY; 
    addr.sin_port = htons(port);

    return bind(sock,(sockaddr*)&addr,sizeof(sockaddr_in)); 
}

void udpServer::stop(){
    closesocket(sock);
}

int udpServer::recvFrom(void *buff,int len,sockaddr_in* from){
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 5000;
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(sock,&readfds);
    int size = sizeof(sockaddr_in);
    if(select(sock+1,&readfds,NULL,NULL,&tv) != 1) return 0;
    else return recvfrom(sock,(char*)buff, len, 0, (sockaddr*) from, &size); 
}