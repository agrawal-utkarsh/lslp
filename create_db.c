#include<unistd.h>
#include<fcntl.h>
int main(void)
{
	int fd;
	fd=creat("db",0744);
}
