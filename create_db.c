#include<unistd.h>
#include<fcntl.h>
int main(void)
{
	int fd,fd1;
	fd=creat("db",0744);
	fd1=creat("transaction_db",0744);
}
