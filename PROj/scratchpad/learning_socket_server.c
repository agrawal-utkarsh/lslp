#include<unistd.h>
#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
int main(void)
{
	int sd;
	sd=socket(AF_UNIX,SOCK_STREAM,0);
	struct sockaddr_in server,client;
	server.sin_family=AF_UNIX;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(5555);
	bind(sd,(void*)(&server),sizeof(server));
	listen(sd,5);
	int sz=sizeof(client);
	int nsd=accept(sd,(void*)&client,&sz);
	char buf[80];
	read(nsd,buf,sizeof(buf));
	printf("message from client %s\n",buf);
	write(nsd,"ack from server\n",17);
}