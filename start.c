#include<unistd.h>
#include<string.h>
#include<fcntl.h>
typedef struct db
{
	char username[50],password[50];
}db;
int main(void)
{
	
	write(1,"welcome\n",9);
	char username[50], password[50];
	write(1,"enter your username\n",21);
	read(0,username,50);
	write(1,"enter your password\n",21);
	read(0,password,50);

	db a;
	int fd;
	fd=open("db",O_RDONLY);
	while(read(fd,&a,sizeof(a)))
	{
		if(!(strcmp(a.username,username)&&strcmp(a.password,password)))
		{
			write(1,"login successful\n",18);
			break;
		}
	}
}
