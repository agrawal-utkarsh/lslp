#include<bits/stdc++.h>
#include<fcntl.h>
#include<unistd.h>
using namespace std;
typedef struct person
{
	int id,balance;
	char name1[50],name2[50],password[50],phone[50];	
}person;
int main()
{
	int fd=creat("normaldb",0744);
	close(fd);
	fd=open("normaldb",O_WRONLY|O_APPEND);
	person a;
	char name[4][50]={"utkarsh","satyam","abhay","pankaj"};
	char password[4][50]={"agrawal","khare","nanda","chowrasia"};
	//string phone[]={"","","","","",""};
	for(int i=0;i<4;i++)
	{
//		cout<<"enter id,balance,name1,name2,password,phone\n";
//		cin>>a.id>>a.balance>>a.name1>>a.name2>>a.password>>a.phone;
		a.id=i+1;
		a.balance=0;
		strcpy(a.name1,name[i]);
		strcpy(a.name2,"");
		strcpy(a.password,password[i]);
		strcpy(a.phone,"");
		write(fd,&a,sizeof(a));
	}
	close(fd);



	fd=creat("admindb",0744);
	close(fd);
	fd=open("admindb",O_WRONLY|O_APPEND);

		a.id=1;
		strcpy(a.name1,"utkarsh");
		strcpy(a.password,"agrawal");
		strcpy(a.phone,"");
		write(fd,&a,sizeof(a));
	close(fd);





	fd=creat("jointdb",0744);
	close(fd);
	fd=open("jointdb",O_WRONLY|O_APPEND);
	int fd1=creat("jointdbbal",0744);
	close(fd1);
	fd1=open("jointdbbal",O_WRONLY|O_APPEND);
	
		a.id=1;
		strcpy(a.name1,"anirudh");
		strcpy(a.name2,"prabhanjan");
		strcpy(a.password,"singh");
		strcpy(a.phone,"");
		a.balance=0;
		write(fd,&a,sizeof(a));
		write(fd1,&a.balance,sizeof(int));
	close(fd);









	return 0;
}