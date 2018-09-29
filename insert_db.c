#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
typedef struct data
{
	char username[50],password[50],status[50];
}data;
int main(void)
{
	int fd;
	fd=open("db",O_WRONLY|O_APPEND);
	data a;
	printf("welcome\n");
	printf("enter your username\n");
	scanf("%s",a.username);
	printf("enter your password\n");
	scanf("%s",a.password);
	printf("%s","normal account, joint account or admin ?");
	scanf("%s",a.status);
	write(fd,&a,sizeof(a));
}
