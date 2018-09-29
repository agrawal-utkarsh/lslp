#include<fcntl.h>
#include<unistd.h>
#include<string.h>
typedef struct data
{
	char username[50],password[50];
}data;
int main(void)
{
	data a;
	int fd;
	fd=open("db",O_RDONLY);
	write(1,"exisiting users:\n\n",17);
	while(read(fd,&a,sizeof(a)))
	{
		write(1,a.username,strlen(a.username));
		//write(1," ",1);
		write(1,a.password,strlen(a.password));
		//write(1,"\n",2);
	}
	
	
}
