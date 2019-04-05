#include "processSimple.h"
#include "sys/socket.h"

void ProcessSimple::process(int connfd)
{
	const char *sendBuf = "Welcome!";
	for (int i = 0; i < 50000; ++i)
	{
	}
	send(connfd, sendBuf, sizeof(sendBuf), 0);
	//close(connfd);
}
