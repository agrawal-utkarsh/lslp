#include<unistd.h>
#include<fcntl.h>
#include<string.h>
typedef struct data
{
	char username[50],password[50];
}data;
int main(void)
{
	int fd;
	fd=open("db",O_WRONLY|O_APPEND);
	data a;
	write(1,"enter your details\n",20);
	write(1,"enter your username\n",21);
	read(0,a.username,50);
	write(1,"enter your password\n",21);
	read(0,a.password,50);
	write(fd,&a,sizeof(a));
}
