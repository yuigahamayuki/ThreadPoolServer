#include "utilSocket.h"
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
    if (argc != 5)
    {
        std::cout << "Wrong usage! Usage: client <ip> <port> <number of children> <number of loops>" << std::endl;
        return -1;
    }

    int nchildren = atoi(argv[3]);
    int nloops = atoi(argv[4]);
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    unsigned short port = atoi(argv[2]);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    
    pid_t pid;
    for (int i = 0; i < nchildren; ++i)
    {
        if (pid = fork() == 0) //child process
        {
            for (int j = 0; j < nloops; ++j)
            {
                int sockfd = Socket(AF_INET, SOCK_STREAM, 0);
                Connect(sockfd, &servaddr, sizeof(servaddr));

                char recvBuf[1024] = "";
                while(recv(sockfd, recvBuf, 1024, 0) > 0)
				{
					printf("child: %d, loop: %d, message: %s\n", i, j, recvBuf);
				}				

            }
            std::cout << "child " << i << " done." << std::endl;
            exit(0);
        }
        // parent loops around to fork() again
    }

    while(wait(NULL) > 0) // success, return pid; error, return -1
        ;                 // error == ECHILD, means no waited child

	std::cout << std::endl;
	std::cout << "All done!" << std::endl;
    return 0;
}
