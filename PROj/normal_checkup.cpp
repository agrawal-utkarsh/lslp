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
		cout<<p.id<<"\t"<<p.balance<<"\t"<<p.name1<<"\t"<<p.name2<<"\t"<<p.password<<"\t"<<p.phone<<endl;
	}
	close(fd);
	cout<<endl<<endl;

	fd=open("admindb",O_RDONLY);
	while(read(fd,&p,sizeof(p)))
	{
		cout<<p.id<<"\t"<<p.balance<<"\t"<<p.name1<<"\t"<<p.name2<<"\t"<<p.password<<"\t"<<p.phone<<endl;
	}
	close(fd);
	cout<<endl<<endl;

	fd=open("jointdb",O_RDONLY);
	while(read(fd,&p,sizeof(p)))
	{
		cout<<p.id<<"\t"<<p.balance<<"\t"<<p.name1<<"\t"<<p.name2<<"\t"<<p.password<<"\t"<<p.phone<<endl;
	}
	close(fd);
	cout<<endl<<endl;
	
	int fd1=open("jointdbbal",O_RDONLY);
	while(read(fd1,&amt,sizeof(int)))
	{
		cout<<amt<<endl;
	}
	close(fd1);
	
	return 0;
}