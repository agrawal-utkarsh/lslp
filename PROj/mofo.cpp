#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<fcntl.h>
#include<string.h>
#include<bits/stdc++.h>
using namespace std;
typedef struct person
{
	int id,balance;
	char name1[50],name2[50],password[50],phone[50];	
}person;

void normaljoint(int t,int id)
{
	cout<<"enter the operation to perform\n";
	cout<<"1.deposit 2.withdraw 3.balance 4.password_change 5.view_detail 6.exit";
	int n;cin>>n;

	switch(t)
	{
		case 1://normal
		break;
		case 2://joint
		break;		
	}
}
void admin()
{
	while(1)
	{
		cout<<"enter the operation to perform\n";
		cout<<"1.add 2.delete 3.modify 4.search\n";
		int t,fd,fd1=-1;cin>>t;
		cout<<"enter account type\n";
		char s[50];cin>>s;
		if(strcmp(s,"normal")==0)
		{
			fd=open("normaldb",O_WRONLY);
		}
		else if(strcmp(s,"joint")==0)
		{
			fd=open("jointdb",O_WRONLY);
			fd1=open("jointdbbal",O_WRONLY);
		}
		person p;char name[50];bool flag=false;
		switch(t)
		{
			case 1://add
			lseek(fd,0,SEEK_END);
			cout<<"enter id,name1,name2,password,phone\n";
			cin>>p.id>>p.name1>>p.name2>>p.password>>p.phone;
			p.balance=0;
			write(fd,&p,sizeof(p));
			if(fd1!=-1)
			{
				lseek(fd1,0,SEEK_END);
				write(fd1,&p.balance,sizeof(int));
			}
			break;
			case 2://delete
			cout<<"enter username to delete\n";
			cin>>name;
			while(read(fd,&p,sizeof(p)))
			{
				if(strcmp(p.name1,name)==0||strcmp(p.name2,name)==0)
				{
					int id=p.id;
					p.id=0;
					strcpy(p.name1,"");
					strcpy(p.name2,"");
					p.balance=0;
					strcpy(p.password,"");
					strcpy(p.phone,"");
					lseek(fd,-1*sizeof(p),SEEK_CUR);
					write(fd,&p,sizeof(p));
					if(fd1!=-1)
					{
						int amt=0;
						lseek(fd1,(id-1)*sizeof(int),SEEK_SET);
						write(fd1,&amt,sizeof(int));
					}
					break;
				}
			}
			break;
			case 3://modify
				cout<<"enter username\n";
				cin>>name;
				while(read(fd,&p,sizeof(p)))
				{
					if(strcmp(p.name1,name)==0||strcmp(p.name2,name)==0)
					{
						cout<<"what do you want to modify\n";
						cout<<"1.name1 2.name2 3.password 4.phone\n";
						int x;cin>>x;cout<<"enter value\n";cin>>name;
						switch(x)
						{
							case 1:
							strcpy(p.name1,name);break;
							case 2:
							strcpy(p.name2,name);break;
							case 3:
							strcpy(p.password,name);break;
							case 4:
							strcpy(p.phone,name);break;
						}
						lseek(fd,-1*sizeof(p),SEEK_CUR);
						write(fd,&p,sizeof(p));
						break;
					}
				}

			break;
			case 4://search
				cout<<"enter username\n";
				cin>>name;
				while(read(fd,&p,sizeof(p)))
				{
					if(strcmp(p.name1,name)==0||strcmp(p.name2,name)==0)
					{
						cout<<"user found\n";
						flag=true;
						break;
					}
				}
				if(!flag)cout<<"user not found\n";
			break;
		}
	}
}
void nextstep(int t,int id)
{
	switch(t)
	{
		case 3://admin
		admin();
		break;
		default://normal or joint
		normaljoint(t,id);
		break;
	}
}
int welcome(int t,char username[],char password[])
{
	int fd,flag=0;person p;
	switch(t)
	{
		case 1://normal
			fd=open("normaldb",O_RDWR);
			break;
		case 2://joint
			fd=open("jointdb",O_RDWR);
			break;
		case 3://admin
			fd=open("admindb",O_RDWR);
			break;

			while(read(fd,&p,sizeof(p)))
			{
				if((strcmp(p.name1,username)==0||(strcmp(p.name2,username)==0))&&strcmp(p.password,password)==0)
				{
					nextstep(t,p.id);
					flag=1;		
				}
			}
	}
	return flag;
}
int main(void)
{
	while(1)
	{
		cout<<"enter login type : 1.normal 2.joint 3.admin\n";
		int t;cin>>t;
		cout<<"enter your username and password\n";
		char username[50],password[50];
		cin>>username>>password;
		welcome(t,username,password);
	}
}
