#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
int main(void)
{
	int sd=socket(AF_UNIX,SOCK_STREAM,0);
	struct sockaddr_in servr;
	servr.sin_family=AF_UNIX;
	servr.sin_addr.s_addr=INADDR_ANY;
	servr.sin_port=htons(5662);
	int c=connect(sd,(void*)(&servr),sizeof(servr));
	printf("connect=%d\n",c);

//welcome prompt
	char buf[80];
	read(sd,buf,80);
	printf("%s\n",buf);

//login type	
	int t;
	scanf("%d",&t);
	write(sd,&t,sizeof(int));

//username
	char username[50];
	read(sd,buf,80);
	printf("%s\n",buf);
	scanf("%s",username);
	write(sd,username,strlen(username));
//password
	read(sd,buf,80);
	printf("%s\n",buf);
	scanf("%s",username);
	write(sd,username,strlen(username));

//user found or not found result
	int z;
	read(sd,&z,sizeof(int));

//user found or not found prompt
	read(sd,buf,80);
	printf("%s\n",buf);

if(z!=1)
{
	
}
else
{

}
//admin
if(t==3)
{

	//welcome prompt 
		read(sd,buf,80);
		printf("%s\n",buf);

	//operation select prompt
		read(sd,buf,80);
		printf("%s\n",buf);
		
	//operation type

		scanf("%d",&t);
		write(sd,&t,sizeof(int));

		read(sd,buf,80);
		printf("%s\n",buf);
		scanf("%d",&t);
		write(sd,&t,sizeof(int));

		read(sd,buf,80);
		printf("%s\n",buf);

		read(sd,buf,80);
		printf("%s\n",buf);
		scanf("%s",username);
		write(sd,username,strlen(username));

		read(sd,buf,80);
		printf("%s\n",buf);
		scanf("%s",username);
		write(sd,username,strlen(username));

		read(sd,buf,80);
		printf("%s\n",buf);
		scanf("%s",username);
		write(sd,username,strlen(username));

		read(sd,buf,80);
		printf("%s\n",buf);
		scanf("%s",username);
		write(sd,username,strlen(username));
}
else
{

}



}