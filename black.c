#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
	int fd;
	fd=open("black",O_CREAT|O_WRONLY,S_IRWXU);
	char u[50],p[50];
	scanf("%s",u);
	scanf("%s",p);
	write(fd,u,50);
	write(fd,p,50);
	close(fd);
	fd=open("black",O_RDONLY);
	char buf;
	while(read(fd,&buf,1)>0)
	{
		printf("%c",buf);
		//write(1,buf,50);
	}
}
