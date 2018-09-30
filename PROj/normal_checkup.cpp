#include<bits/stdc++.h>
#include<unistd.h>
#include<fcntl.h>
using namespace std;
typedef struct person
{
	int id,balance;
	char name1[50],name2[50],password[50],phone[50];	
}person;
int main(void)
{
	person p;int amt;
	int fd=open("normaldb",O_RDONLY);
	while(read(fd,&p,sizeof(p)))
	{
		cout<<p.id<<" "<<p.balance<<" "<<p.name1<<" "<<p.name2<<" "<<p.password<<" "<<p.phone<<endl;
	}
	close(fd);
	

	fd=open("admindb",O_RDONLY);
	while(read(fd,&p,sizeof(p)))
	{
		cout<<p.id<<" "<<p.balance<<" "<<p.name1<<" "<<p.name2<<" "<<p.password<<" "<<p.phone<<endl;
	}
	close(fd);
	

	fd=open("jointdb",O_RDONLY);
	while(read(fd,&p,sizeof(p)))
	{
		cout<<p.id<<" "<<p.balance<<" "<<p.name1<<" "<<p.name2<<" "<<p.password<<" "<<p.phone<<endl;
	}
	close(fd);

	
	int fd1=open("jointdbbal",O_RDONLY);
	while(read(fd1,&amt,sizeof(int)))
	{
		cout<<amt<<endl;
	}
	close(fd1);
	
	return 0;
}