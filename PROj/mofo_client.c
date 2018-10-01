#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<stdbool.h>
#include<sys/socket.h>
#include<stdlib.h>
typedef struct person
{
	int id,balance;
	char name1[50],name2[50],password[50],phone[50];	
}person;
int main(int argc,char**argv)
{
	int sd=socket(AF_UNIX,SOCK_STREAM,0);
	struct sockaddr_in servr;
	servr.sin_family=AF_UNIX;
	servr.sin_addr.s_addr=INADDR_ANY;
	servr.sin_port=htons(atoi(argv[1]));
	int c=connect(sd,(void*)(&servr),sizeof(servr));
	printf("connect=%d\n",c);


	if(c==0)
	{
		while(1)
		{
			char buf[50];
			printf("enter login type : 1.normal 2.joint 3.admin\n");
			int t;
			scanf("%d",&t);
			write(sd,&t,sizeof(int));

			printf("enter your username\n");
			strcpy(buf,"");
			scanf("%s",buf);
			write(sd,buf,strlen(buf)+1);

			printf("enter your password\n");
			strcpy(buf,"");
			scanf("%s",buf);
			write(sd,buf,strlen(buf)+1);

			//user found or not found result
			
			read(sd,buf,sizeof(buf));
			printf("%s\n",buf);
			if(strcmp(buf,"login not success\n")==0)
				return 0; 
			if(t==3)
			{
				while(1)
				{
					printf("enter the operation to perform\n");
					printf("1.add 2.delete 3.modify 4.search 5.exit\n");

										
					int tt;				
					scanf("%d",&tt);
					write(sd,&tt,sizeof(int));

					if(tt==5)exit(0);
					else
					{

						printf("enter account type : 1.normal 2.joint\n");
						int x;
						scanf("%d",&x);
						write(sd,&x,sizeof(int));
						if(x==1)
						{
							printf("inside normaldb\n");				
						}
						else if(x==2)
						{
							printf("inside jointdb\n");
						}

						if(tt==1)
						{
							char name[50];strcpy(name,"");
							printf("enter name1\n");
							scanf("%s",name);
							write(sd,name,strlen(name)+1);
							strcpy(name,"");
							printf("enter name2\n");
							scanf("%s",name);
							write(sd,name,strlen(name)+1);
							strcpy(name,"");
							printf("enter password\n");
							scanf("%s",name);
							write(sd,name,strlen(name)+1);
							strcpy(name,"");
							printf("enter phone\n");
							scanf("%s",name);
							write(sd,name,strlen(name)+1);
						}
						else if(tt==2)
						{
							printf("enter username\n");
							char name[50];strcpy(name,"");
							scanf("%s",name);
							write(sd,name,strlen(name)+1);
						}
						else if(tt==3)
						{
							printf("enter username\n");
							char name[50];strcpy(name,"");
							scanf("%s",name);
							write(sd,name,strlen(name)+1);
							int r;
							read(sd,&r,sizeof(r));
							if(r==1)
							{
								printf("what do you want to modify\n");
								printf("1.name1 2.name2 3.password 4.phone\n");
								scanf("%d",&x);
								write(sd,&x,sizeof(int));
								printf("enter value\n");strcpy(name,"");
								scanf("%s",name);
								write(sd,name,strlen(name)+1);
								
							}
						}
						else if(tt==4)
						{
							printf("enter username\n");
							char name[50];strcpy(name,"");
							scanf("%s",name);
							write(sd,name,strlen(name)+1);
							int r;
							read(sd,&r,sizeof(int));
							if(r==1)
								printf("user found\n");
							else
								printf("user not found\n");
						}
						/*else if(tt==5)
						{
							person p;
							read(sd,&p,sizeof(p));

							printf("%d %d %s %s %s %s\n",p.id,p.balance,p.name1,p.name2,p.password,p.phone);
						}*/
					}
				}
			}
			else
			{
				while(1)
				{
					printf("enter the operation to perform\n");
					printf("1.deposit 2.withdraw 3.balance 4.password_change 5.view_detail 6.exit\n");
					int x;scanf("%d",&x);

					write(sd,&x,sizeof(int));
					if(x==6){exit(0);}
					else
					{
						if(t==1)
						{

							//normal
							if(x==1)
							{
								printf("enter amt to deposit\n");
								int amt;
								scanf("%d",&amt);
								write(sd,&amt,sizeof(int));
							}
							else if(x==2)
							{
								printf("enter amt to withdraw\n");
								int amt,laplap;
								scanf("%d",&amt);
								write(sd,&amt,sizeof(int));
								read(sd,&laplap,sizeof(laplap));
								if(laplap==1)
									printf("funds not sufficient\n");
							}
							else if(x==3)
							{
								int ba;
								read(sd,&ba,sizeof(int));
								printf("balance=%d\n", ba);
							}
							else if(x==4)
							{
								printf("enter new password\n");
								char pas[50];strcpy(pas,"");
								scanf("%s",pas);
								write(sd,pas,strlen(pas)+1);
							}
							else if(x==5)
							{
								person p;
								read(sd,&p,sizeof(person));
								printf("%d %s %s %s %s\n",p.balance,p.name1,p.name2,p.password,p.phone);
							}
							

						}
						else if(t==2) 
						{
							//joint

							if(x==1)
							{
								printf("enter amt to deposit\n");
								int amt;
								scanf("%d",&amt);
								write(sd,&amt,sizeof(int));
							}
							else if(x==2)
							{
								printf("enter amt to withdraw\n");
								int amt,laplap;
								scanf("%d",&amt);
								write(sd,&amt,sizeof(int));
								read(sd,&laplap,sizeof(laplap));
								if(laplap==1)
									printf("funds not sufficient\n");
							}
							else if(x==3)
							{
								int ba;
								read(sd,&ba,sizeof(int));
								printf("balance=%d\n", ba);
							}
							else if(x==4)
							{
								printf("enter new password\n");
								char pas[50];strcpy(pas,"");
								scanf("%s",pas);
								write(sd,pas,strlen(pas)+1);
							}
							else if(x==5)
							{
								person p;
								read(sd,&p,sizeof(person));
								printf("%d %s %s %s %s\n",p.balance,p.name1,p.name2,p.password,p.phone);
							}

						}
					}
				}
			}
		

		}
	}

}