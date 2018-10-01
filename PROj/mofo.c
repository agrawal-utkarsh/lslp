
//file locking for multiple admins, for user and admin
//for admin modification : take enter as input for non joint second username

//socket multithreaded_server


#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
typedef struct person
{
	int id,balance;
	char name1[50],name2[50],password[50],phone[50];	
}person;

int nsd;char buf[80];
		
void normaljoint(int t,int id)
{
	while(1)
	{
		int x;
		read(nsd,&x,sizeof(int));
		printf("%d\n",x );
		if(x==6)return;

		printf("%d\n",x );
		struct flock lock;
		int jd;
		int fd,fd1=-1,amt=0,bowl=0,laplap=0;person p;char pass[50];
		switch(t)
		{
			case 1://normal
				fd=open("normaldb",O_RDWR);
				switch(x)
				{
					case 1://deposit
						read(nsd,&amt,sizeof(int));
						printf("%d\n",amt );
						lseek(fd,(id-1)*sizeof(p),SEEK_SET);
						read(fd,&p,sizeof(p));
						p.balance+=amt;
						lseek(fd,(-1)*sizeof(p),SEEK_CUR);
						write(fd,&p,sizeof(p));
					break;
					case 2://withdraw
						read(nsd,&amt,sizeof(int));
						printf("%d\n",amt );
						lseek(fd,(id-1)*sizeof(p),SEEK_SET);
						read(fd,&p,sizeof(p));
						if(p.balance-amt<0)
						{
							laplap=1;
						}
						else
						p.balance-=amt;
						write(nsd,&laplap,sizeof(int));
						lseek(fd,(-1)*sizeof(p),SEEK_CUR);
						write(fd,&p,sizeof(p));
					break;
					case 3://balance
						lseek(fd,(id-1)*sizeof(p),SEEK_SET);
						read(fd,&p,sizeof(p));
						write(nsd,&p.balance,sizeof(int));
					break;
					case 4://password_change
						lseek(fd,(id-1)*sizeof(p),SEEK_SET);
						read(fd,&p,sizeof(p));
						read(nsd,pass,50);
						printf("%s\n",pass );
						strcpy(p.password,pass);
						lseek(fd,(-1)*sizeof(p),SEEK_CUR);
						write(fd,&p,sizeof(p));
					break;
					case 5://view_detail
						lseek(fd,(id-1)*sizeof(p),SEEK_SET);
						read(fd,&p,sizeof(p));
						write(nsd,&p,sizeof(p));
					break;
				}
			break;
				




			case 2://joint
				fd=open("jointdb",O_RDWR);
				fd1=open("jointdbbal",O_RDWR);
				switch(x)
				{
					case 1://deposit
						lseek(fd,(id-1)*sizeof(p),SEEK_SET);
						lock.l_type=F_WRLCK;
						lock.l_whence=SEEK_CUR;
						lock.l_pid=getpid();
						lock.l_start=0;
						lock.l_len=sizeof(p);
						fcntl(fd,F_SETLKW,&lock);
						
						read(nsd,&amt,sizeof(int));
						printf("%d\n",amt );
						read(fd,&p,sizeof(p));
						p.balance+=amt;
						lseek(fd,(-1)*sizeof(p),SEEK_CUR);
						write(fd,&p,sizeof(p));
						if(fd1!=-1)
						{
							lseek(fd1,(id-1)*sizeof(int),SEEK_SET);
							write(fd1,&p.balance,sizeof(int));
						}

						lseek(fd,(-1)*sizeof(p),SEEK_CUR);
						lock.l_type=F_UNLCK;
						fcntl(fd,F_SETLKW,&lock);

					break;
					case 2://withdraw
						lseek(fd,(id-1)*sizeof(p),SEEK_SET);
						lock.l_type=F_WRLCK;
						lock.l_whence=SEEK_CUR;
						lock.l_pid=getpid();
						lock.l_start=0;
						lock.l_len=sizeof(p);
						fcntl(fd,F_SETLKW,&lock);
						
						read(nsd,&amt,sizeof(int));
						read(fd,&p,sizeof(p));
						if(p.balance-amt<0)
							laplap=1;
						else
						p.balance-=amt;
						write(nsd,&laplap,sizeof(int));
						lseek(fd,(-1)*sizeof(p),SEEK_CUR);
						write(fd,&p,sizeof(p));
						if(fd1!=-1)
						{
							lseek(fd1,(id-1)*sizeof(int),SEEK_SET);
							write(fd1,&p.balance,sizeof(int));
						}

						lseek(fd,(-1)*sizeof(p),SEEK_CUR);
						lock.l_type=F_UNLCK;
						fcntl(fd,F_SETLKW,&lock);

					break;
					case 3://balance
						lseek(fd,(id-1)*sizeof(p),SEEK_SET);
						lock.l_type=F_RDLCK;
						lock.l_whence=SEEK_CUR;
						lock.l_pid=getpid();
						lock.l_start=0;
						lock.l_len=sizeof(p);
						fcntl(fd,F_SETLKW,&lock);
						
						read(fd,&p,sizeof(p));
						write(nsd,&p.balance,sizeof(int));
						//cin>>jd;//dummy input for pause

						lseek(fd,(-1)*sizeof(p),SEEK_CUR);
						lock.l_type=F_UNLCK;
						fcntl(fd,F_SETLKW,&lock);
					break;
					case 4://password_change
						lseek(fd,(id-1)*sizeof(p),SEEK_SET);
						read(fd,&p,sizeof(p));
						read(nsd,pass,50);
						strcpy(p.password,pass);
						lseek(fd,(-1)*sizeof(p),SEEK_CUR);
						write(fd,&p,sizeof(p));
					break;
					case 5://view_detail
						lseek(fd,(id-1)*sizeof(p),SEEK_SET);
						lock.l_type=F_RDLCK;
						lock.l_whence=SEEK_CUR;
						lock.l_pid=getpid();
						lock.l_start=0;
						lock.l_len=sizeof(p);
						fcntl(fd,F_SETLKW,&lock);

						read(fd,&p,sizeof(p));
						write(nsd,&p,sizeof(p));
						//cin>>jd;//dummy

						lseek(fd,(-1)*sizeof(p),SEEK_CUR);
						lock.l_type=F_UNLCK;
						fcntl(fd,F_SETLKW,&lock);
					break;
				}
			break;		
		}
	}

}
void admin()
{
	while(1)
	{
			int t,fd,fd1=-1,cnt=0,r=0;
			read(nsd,&t,sizeof(int));
			printf("%d\n",t);

			if(t==5)return;

			int x;
			read(nsd,&x,sizeof(int));
			printf("%d\n",x);
			
			switch(x)
			{
				case 1:
					fd=open("normaldb",O_RDWR);
				break;
				case 2:
					fd=open("jointdb",O_RDWR);
					fd1=open("jointdbbal",O_RDWR);
				break; 
			}
			person p;char name[50];bool flag=false;
			switch(t)
			{
				case 1://add
					while(read(fd,&p,sizeof(p)))
						cnt++;
					read(nsd,p.name1,50);
					printf("%s\n",p.name1 );
					read(nsd,p.name2,50);
					printf("%s\n",p.name2 );
					read(nsd,p.password,50);
					printf("%s\n",p.password );
					read(nsd,p.phone,50);
					printf("%s\n",p.phone );
					p.id=++cnt;
					p.balance=0;
					write(fd,&p,sizeof(p));
					if(fd1!=-1)
					{
						lseek(fd1,0,SEEK_END);
						write(fd1,&p.balance,sizeof(int));
					}
				break;
				case 2://delete
					read(nsd,name,50);
					printf("%s\n", name);
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
					read(nsd,name,50);
					printf("%s\n",name );
					while(read(fd,&p,sizeof(p)))
					{
						if(strcmp(p.name1,name)==0||strcmp(p.name2,name)==0)
						{
							r=1;
							write(nsd,&r,sizeof(int));
							
							read(nsd,&x,sizeof(int));
							printf("%d\n", x);
							read(nsd,name,50);
							printf("%s\n",name );
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
					read(nsd,name,50);
					printf("%s\n",name);
					while(read(fd,&p,sizeof(p)))
					{
						if(strcmp(p.name1,name)==0||strcmp(p.name2,name)==0)
						{
							r=1;
							break;
						}
					}
					write(nsd,&r,sizeof(int));
				break;
				/*case 5:
					while(read(fd,&p,sizeof(p)))
					{
						write(nsd,&p,sizeof(p));
 						//cout<<p.id<<" "<<p.balance<<" "<<p.name1<<" "<<p.name2<<" "<<p.password<<" "<<p.phone<<endl;
					}
				break;*/
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
	printf("end of nextstep\n");
}
void welcome(int t,char username[],char password[])
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

	}

	while(read(fd,&p,sizeof(p)))
	{
		if((strcmp(p.name1,username)==0||(strcmp(p.name2,username)==0))&&strcmp(p.password,password)==0)
		{
			flag=1;
			write(nsd,"login success\n",15);
			nextstep(t,p.id);
			break;		
		}
	}
	
	if(flag==0)
			write(nsd,"login not success\n",19);


		printf("end of welcome\n");
		
}
int main(int argc,char**argv)
{
	int sd=socket(AF_UNIX,SOCK_STREAM,0);
	struct sockaddr_in servr,client;
	servr.sin_family=AF_UNIX;
	servr.sin_addr.s_addr=INADDR_ANY;
	servr.sin_port=htons(atoi(argv[1]));
	int b=bind(sd,(void*)(&servr),sizeof(servr));
	printf("bind=%d\n",b);
	b=listen(sd,5);
	printf("listen=%d\n",b);
	int sz=sizeof(client);	
	while(1)
	{
	nsd=accept(sd,(void*)(&servr),&sz);
	printf("accept=%d\n",nsd);

		int t;
		read(nsd,&t,sizeof(int));
		printf("%d\n",t);

		char username[50],password[50];
		strcpy(username,"");
		strcpy(password,"");
		//printf("%s %s\n",username,password);

		read(nsd,username,50);
		read(nsd,password,50);
		printf("%s %s\n",username,password);

		welcome(t,username,password);
		printf("end of main\n");
	}
}
