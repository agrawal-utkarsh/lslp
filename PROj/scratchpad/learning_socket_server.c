#include<unistd.h>
#include<stdio.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/socket.h>
int main(int argc,char**argv)
{
	int sd;
	sd=socket(AF_UNIX,SOCK_STREAM,0);
	struct sockaddr_in server,client;
	server.sin_family=AF_UNIX;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(atoi(argv[1]));
	int b=bind(sd,(void*)(&server),sizeof(server));
	printf("bind=%d\n",b);
	int l=listen(sd,5);
	printf("listen=%d\n",l);
	int sz=sizeof(client);
	int nsd=accept(sd,(void*)&client,&sz);
	printf("accept=%d\n",nsd);
	char buf[80];
		
	
	{
		strcpy(buf,"statement 1 from server\n");
		write(nsd,buf,strlen(buf)-3);
		
		strcpy(buf,"statement 2 from server\n");
		write(nsd,buf,strlen(buf)-3);
		read(nsd,buf,80);
		printf("%d\n", atoi(buf)+4);

		strcpy(buf,"statement 3 from server\n");
		write(nsd,buf,strlen(buf)-3);
		read(nsd,buf,80);
		printf("%d\n", atoi(buf)+4);

		strcpy(buf,"statement 4 from server\n");
		write(nsd,buf,strlen(buf)-3);
		read(nsd,buf,80);
		printf("%d\n", atoi(buf)+4);

		strcpy(buf,"statement 5 from server\n");
		write(nsd,buf,strlen(buf)-3);
		read(nsd,buf,80);
		printf("%d\n", atoi(buf)+4);
	}
//	read(nsd,buf,sizeof(buf));
//	printf("message from client %s\n",buf);
//	write(nsd,"ack from server\n",17);
}