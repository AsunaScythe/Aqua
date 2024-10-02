
#include "tcpServer.h"

tcpServer::tcpServer(){}

tcpServer::~tcpServer(){disconnect();}

int tcpServer::create(uint16_t localPort){

    sock = socket(AF_INET, SOCK_STREAM, 0);

    u_long mode = 1;
    ioctlsocket(sock, FIONBIO, &mode);

    SOCKADDR_IN addr;
 
    addr.sin_family = AF_INET; 
    addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    addr.sin_port = htons(localPort); 
    
    return bind(sock, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN)); 
}

int tcpServer::waitConnection(sockaddr *client_addr){

    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 5000;
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(sock,&readfds);
    listen(sock,1);
    int len = sizeof(sockaddr_in);

    if(select(sock+1,&readfds,NULL,NULL,&tv) != 1) return 0;
    else return accept(sock, client_addr,&len);
    
    return 0;
} 

void tcpServer::disconnect(){closesocket(sock);}