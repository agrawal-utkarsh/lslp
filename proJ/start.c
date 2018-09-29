//enter edge conditions for deposit and withdrawal
//file locking for multiple admins, for user and admin
//assign unique identifier to users


//locking socket multithreaded server


#include<stdio.h>//standard i/o
#include<unistd.h>//system calls
#include<stdbool.h>//bool
#include<string.h>//string library
#include<stdlib.h>//exit
#include<fcntl.h>//O_RDONLY, ......
typedef struct data
{
	char username[50],password[50],status[50],username2[50];
}data;
typedef struct transaction_data
{
	char username[50],username2[50];
	int deposit,withdrawal;
}tdata;
int main(void)
{

	printf("welcome\n");
	char username[50], password[50];
	while(1)
	{
		printf("enter your username\n");
		scanf("%s",username);
		printf("enter your password\n");
		scanf("%s",password);

		data a;
		int fd;
		fd=open("db",O_RDONLY);
		bool flag=false;
		while(read(fd,&a,sizeof(a)))
		{
			if((strcmp(a.username,username)==0 || strcmp(a.username2,username)==0) && strcmp(a.password,password)==0)
			{
				write(1,"login successful\n",18);
				flag=true;
				if(strcmp(a.status,"normal")==0)
				{
					//deposit withdraw balance password_change view_details exit
					while(1)
					{
						printf("\nenter the operation to perform\n");
						printf("1.deposit\n2.withdrawal\n3.view_balance\n4.password_change\n5.view_details\n6.exit\n");
						int t,fd1,amt;
						data a1,a2,a3;
						tdata ta1,ta2,ta3;
						scanf("%d",&t);
						switch (t)
						{
							case 1://deposit
								fd1=open("transaction_db",O_WRONLY|O_APPEND);
								printf("enter amount to deposit\n");
								scanf("%d",&amt);
								strcpy(ta1.username,username);
								ta1.deposit=amt;
								ta1.withdrawal=0;
								write(fd1,&ta1,sizeof(ta1));
								close(fd1);
								break;
							case 2://withdrawal
								fd1=open("transaction_db",O_WRONLY|O_APPEND);
								printf("enter amount to withdraw\n");
								scanf("%d",&amt);
								strcpy(ta1.username,username);
								ta1.deposit=0;
								ta1.withdrawal=amt;
								write(fd1,&ta1,sizeof(ta1));
								close(fd1);
								break;
							case 3://view_balance
								fd1=open("transaction_db",O_RDONLY);
								amt=0;
								while(read(fd1,&ta1,sizeof(ta1)))
								{
									if(strcmp(ta1.username,username)==0)
									amt=amt+ta1.deposit-ta1.withdrawal;
								}
								printf("%d",amt);
								close(fd1);
								break;
							case 4://password_change
								fd1=open("db",O_RDWR);
								char p[50];
								printf("enter new password\n");
								scanf("%s",a2.password);
								while(read(fd1,&a1,sizeof(a1)))
								{
									if(strcmp(a1.username,username)==0 && strcmp(a1.password,password)==0)
									{
										printf("user found\n");
										lseek(fd1,-1*sizeof(data),SEEK_CUR);
										strcpy(a1.password,a2.password);
										write(fd1,&a1,sizeof(a1));
										printf("modification successful\n");
										break;
									}
								}
								close(fd1);
								break;
							case 5://view_details
								fd1=open("transaction_db",O_RDONLY);
								printf("deposit\twithdrawal\n");
								while(read(fd1,&ta1,sizeof(ta1)))
								{
									if(strcmp(ta1.username,username)==0)
									{
										printf("%d\t%d\n",ta1.deposit,ta1.withdrawal);
									}
								}
								close(fd1);
								break;
							case 6://exit
								exit(0);
							default:
								printf("enter again\n");
						}
					}
				}

















				else if(strcmp(a.status,"joint")==0)
				{
					//view account details -> read lock
					//deposit withdrawal ->write lock

					while(1)
					{
						printf("\nenter the operation to perform\n");
						printf("1.deposit\n2.withdrawal\n3.view_balance\n4.password_change\n5.view_details\n6.exit\n");
						int t,fd1,amt;
						data a1,a2,a3;
						tdata ta1,ta2,ta3;
						scanf("%d",&t);
						switch (t)
						{
							case 1://deposit
								fd1=open("transaction_db",O_WRONLY|O_APPEND);
								printf("enter amount to deposit\n");
								scanf("%d",&amt);
								strcpy(ta1.username,username);
								ta1.deposit=amt;
								ta1.withdrawal=0;
								write(fd1,&ta1,sizeof(ta1));
								close(fd1);
								break;
							case 2://withdrawal
								fd1=open("transaction_db",O_WRONLY|O_APPEND);
								printf("enter amount to withdraw\n");
								scanf("%d",&amt);
								strcpy(ta1.username,username);
								ta1.deposit=0;
								ta1.withdrawal=amt;
								write(fd1,&ta1,sizeof(ta1));
								close(fd1);
								break;
							case 3://view_balance
								fd1=open("transaction_db",O_RDONLY);
								amt=0;
								while(read(fd1,&ta1,sizeof(ta1)))
								{
									if(strcmp(ta1.username,username)==0)
									amt=amt+ta1.deposit-ta1.withdrawal;
								}
								printf("%d",amt);
								close(fd1);
								break;
							case 4://password_change
								fd1=open("db",O_RDWR);
								char p[50];
								printf("enter new password\n");
								scanf("%s",a2.password);
								while(read(fd1,&a1,sizeof(a1)))
								{
									if(strcmp(a1.username,username)==0 && strcmp(a1.password,password)==0)
									{
										printf("user found\n");
										lseek(fd1,-1*sizeof(data),SEEK_CUR);
										strcpy(a1.password,a2.password);
										write(fd1,&a1,sizeof(a1));
										printf("modification successful\n");
										break;
									}
								}
								close(fd1);
								break;
							case 5://view_details
								fd1=open("transaction_db",O_RDONLY);
								printf("deposit\twithdrawal\n");
								while(read(fd1,&ta1,sizeof(ta1)))
								{
									if(strcmp(ta1.username,username)==0)
									{
										printf("%d\t%d\n",ta1.deposit,ta1.withdrawal);
									}
								}
								close(fd1);
								break;
							case 6://exit
								exit(0);
							default:
								printf("enter again\n");
						}
					}

				}






















				else if(strcmp(a.status,"admin")==0)
				{
						//add delete modify search
						while(1)
						{
								printf("select the operation you want to perform\n");
								printf("1.add\n2.delete\n3.modify\n4.search\n5.view_all\n6.exit\n");
								int t,fd1;
								data a1,a2,a3;
								scanf("%d",&t);
								switch(t)
								{
									case 1://add

										fd1=open("db",O_WRONLY|O_APPEND);

										printf("welcome\n");
										printf("enter your username\n");
										scanf("%s",a1.username);
										printf("enter your password\n");
										scanf("%s",a1.password);
										printf("%s","normal account, joint account or admin ?");
										scanf("%s",a1.status);
										if(strcmp(a.status,"joint")==0)
										{
											printf("enter 2nd username\n");
											scanf("%s",a.username2);
										}
										write(fd1,&a1,sizeof(a1));
										close(fd1);
										break;
									case 2://delete

										fd1=open("db",O_RDWR);

										printf("welcome\n");
										printf("enter your username\n");
										scanf("%s",a1.username);
										printf("enter your password\n");
										scanf("%s",a1.password);
										while(read(fd1,&a2,sizeof(a2)))
										{
											if((strcmp(a1.username,a2.username)==0 || strcmp(a1.username,a2.username2)==0)&& strcmp(a1.password,a2.password)==0)
											{
												printf("user found\n");
												lseek(fd1,-1*sizeof(data),SEEK_CUR);
												break;
											}
										}
									  strcpy(a2.username,"");
										strcpy(a2.password,"");
										strcpy(a2.status,"");
										strcpy(a2.username2,"");
										write(fd1,&a2,sizeof(a2));
										printf("deletion successful\n");
										close(fd1);
										break;
									case 3://modify

										fd1=open("db",O_RDWR);

										printf("welcome\n");
										printf("enter old username1\n");
										scanf("%s",a1.username);
										printf("enter old password\n");
										scanf("%s",a1.password);
										printf("enter old username2\n");
										scanf("%s",a1.username2);

										char u[50],p[50];
										printf("enter new username1\n");
										scanf("%s",a2.username);
										printf("enter new password\n");
										scanf("%s",a2.password);
										printf("enter new username2\n");
										scanf("%s",a2.username2);

										while(read(fd1,&a3,sizeof(a3)))
										{
											if((strcmp(a1.username,a3.username)==0 || strcmp(a1.username,a3.username2)==0) && strcmp(a1.password,a3.password)==0)
											{
												printf("user found\n");
												lseek(fd1,-1*sizeof(data),SEEK_CUR);
												strcpy(a1.username,a2.username);
												strcpy(a1.password,a2.password);
												strcpy(a1.status,a3.status);
												strcpy(a1.username2,a2.username2);

												write(fd1,&a1,sizeof(a1));
												printf("modification successful\n");
												break;
											}
										}
										close(fd1);
										break;
									case 4://search

										fd1=open("db",O_RDONLY);

										printf("welcome\n");
										printf("enter your username\n");
										scanf("%s",a1.username);
										printf("enter your password\n");
										scanf("%s",a1.password);
										bool flag1=false;
										while(read(fd1,&a2,sizeof(a2)))
										{
											if((strcmp(a1.username,a2.username)==0 ||strcmp(a1.username,a2.username2)==0)&& strcmp(a1.password,a2.password)==0)
											{
												printf("user found\n");
												flag1=true;
												break;
											}
										}
										if(!flag1)
										{
											printf("user not found\n");
										}
										close(fd1);
										break;
									case 5://view_all
										fd1=open("db",O_RDONLY);
										printf("exisiting users:\n\n");
										while(read(fd1,&a1,sizeof(a1)))
										{
											printf("%s %s %s %s\n",a1.username,a1.password,a1.status,a1.username2);
										}
										break;
									case 6://exit
										exit(0);
									default:
										printf("enter again\n");
								}
						}


				}

				break;
			}
		}
		if(!flag)
		{
			printf("login unsuccessful\n");
		}
	}
}
