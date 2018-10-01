#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
int main(int argc,char**argv)
{
	int sd=socket(AF_UNIX,SOCK_STREAM,0);
	struct sockaddr_in servr;
	servr.sin_family=AF_UNIX;
	servr.sin_addr.s_addr=INADDR_ANY;
	servr.sin_port=htons(atoi(argv[1]));
	int c=connect(sd,(void*)&servr,sizeof(servr));
	printf("connect=%d\n",c);
	char buf[80];

	while(1)
	{
		read(sd,buf,80);
		printf("%s\n",buf);
		scanf("%s",buf);
		write(sd,strcat(buf,"\n"),strlen(buf)+2);
	}
}