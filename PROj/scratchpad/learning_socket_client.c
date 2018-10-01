#include<unistd.h>
#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
int main(void)
{
	int sd=socket(AF_UNIX,SOCK_STREAM,0);
	struct sockaddr_in servr;
	servr.sin_family=AF_UNIX;
	servr.sin_addr.s_addr=INADDR_ANY;
	servr.sin_port=htons(5555);
	connect(sd,(void*)&servr,sizeof(servr));
	char buf[80];
	write(sd,"initiation from client\n",20);
	read(sd,buf,80);
	printf("message from server %s\n",buf);

}