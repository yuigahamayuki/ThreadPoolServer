#include "processSimple.h"
#include "sys/socket.h"

void ProcessSimple::process(int connfd)
{
	const char *sendBuf = "Welcome!";
	send(connfd, sendBuf, sizeof(sendBuf), 0);
	//close(connfd);
}
