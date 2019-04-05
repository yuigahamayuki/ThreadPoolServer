#include "utilSocket.h"
#include <iostream>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int Socket(int family, int type, int protocal)
{
    int sockfd = socket(family, type, protocal);
    if (sockfd >= 0)
        return sockfd;
    else
    {
        std::cout << "socket creation failed:" << strerror(errno) << std::endl;
        exit(-1);
    }
}

void Bind(int sockfd, struct sockaddr_in *myaddr, socklen_t addrlen)
{
    if (bind(sockfd, (sockaddr*)myaddr, addrlen) == -1)
    {
        std::cout << "bind failed: " << strerror(errno) << std::endl;
        exit(-1);
    }
}

void Listen(int sockfd, int backlog)
{
    if (listen(sockfd, backlog) == -1)
    {
        std::cout << "listen failed: " << strerror(errno) << std::endl;
        exit(-1);
    }
}

int Accept(int sockfd, struct sockaddr_in *cliaddr, socklen_t *addrlen)
{
    int connfd = accept(sockfd, (sockaddr*)cliaddr, addrlen);
    if (connfd == -1)
    {
        std::cout << "accept failed: " << strerror(errno) << std::endl;
        exit(-1);
    }

    return connfd;
}

void Connect(int sockfd, struct sockaddr_in *servaddr, socklen_t addrlen)
{
	if (connect(sockfd, (sockaddr*)servaddr, addrlen) == -1)
	{
		std::cout << "connect failed: " << strerror(errno) << std::endl;
		exit(-1);
	}
}
