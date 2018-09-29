#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
typedef struct data
{
	char username[50],password[50],status[50];
}data;
int main(void)
{
	data a;
	int fd;
	fd=open("db",O_RDONLY);
	printf("exisiting users:\n\n");
	while(read(fd,&a,sizeof(a)))
	{
		printf("%s %s %s\n",a.username,a.password,a.status);
	}


}
