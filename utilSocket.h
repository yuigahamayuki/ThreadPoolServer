#ifndef _UTISOCKET_H_
#define _UTISOCKET_H_

#include <sys/socket.h>
#include <netinet/in.h>
int Socket(int family, int type, int protocal);
void Bind(int sockfd, struct sockaddr_in *myaddr, socklen_t addrlen);
void Listen(int sockfd, int backlog);
int Accept(int sockfd, struct sockaddr_in *cliaddr, socklen_t *addrlen);
void Connect(int sockfd, struct sockaddr_in *servaddr, socklen_t addrlen);

#endif //_UTISOCKET_H_
