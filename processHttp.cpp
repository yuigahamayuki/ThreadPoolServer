#include "processHttp.h"
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <string.h>
#include <fstream>
#include <stdio.h>

void ProcessHttp::process(int connfd)
{
    char recvBuf[1024];
	std::cout << "processing connfd: " << connfd << std::endl;
    int res = recv(connfd, recvBuf, 1024, 0);
	std::cout << "receive succeeded! connfd: " << connfd << std::endl;
	if (res == 0) // res = 0: client sent fin
		return;
	//succeed:do ...; failed: do ...;
    std::string str(recvBuf);
    std::cout << str;
	std::cout<<std::endl;
	//parse URI
	char *pUri_start = recvBuf;
	while(*pUri_start != '/')
	{
		pUri_start++;
	}
	char *pUri_end = pUri_start;
	while(*pUri_end != ' ')
	{
		pUri_end++;
	}
	*pUri_end = '\0';
	char *uri = new char[pUri_end - pUri_start + 1];
	strcpy(uri, pUri_start);
	//process special charcter in uri, such as %20(= space)
	/*std::string str = uri;
	std::cout << str << std::endl;*/
	char *contentBuf;
	int content_length = 0;
	if (strcmp(uri, "/") == 0)
	{
		std::ifstream in;
		in.open("index.html");
		in.seekg(0, in.end);
		content_length = in.tellg();
		in.seekg(0, in.beg);
		contentBuf = new char[content_length];
		in.read(contentBuf, content_length);
		in.close();

		char sendBuf[1024];	
		sprintf(sendBuf, "HTTP/1.1 200 OK\r\n\
Content-Type: text/html\r\n\
Content-Length: %d\r\n\r\n", content_length);
		strcat(sendBuf, contentBuf);
		send(connfd, sendBuf, 1024, 0);
	}

	
	//close(connfd);
	
}
