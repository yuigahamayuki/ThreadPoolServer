#include "utilSocket.h"
#include "tcpThread.h"
#include "processHttp.h"
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "processSimple.h"
int main(int argc, char* argv[])
{
    int listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(8888);
	const int on = 1;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    Bind(listenfd, &servaddr, sizeof(servaddr));

    Listen(listenfd, 64);

	ThreadPool threadPool(4);

    int connfd;
    struct sockaddr_in cliaddr;
    socklen_t clilen;
	//ProcessRequest *processRequest = new ProcessHttp;//change depend on process method
	ProcessRequest *processRequest = new ProcessSimple;
	int taskNum = 0; //debug
    while(1)
    {
        clilen = sizeof(cliaddr);
        connfd = Accept(listenfd, &cliaddr, &clilen);

        Task* task = new Task(connfd);
		task->setProcessMethod(processRequest);
		taskNum++;
		std::cout << "task No." << taskNum << ", accepted connfd: " << connfd << std::endl; 
        threadPool.addTask(task);
    }

    close(listenfd);
    return 0;
}
