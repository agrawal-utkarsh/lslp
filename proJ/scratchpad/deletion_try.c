#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
typedef struct data
{
  char u[50],p[50];
}data;

int main(void)
{
  int fd;
  fd=creat("black2",0744);
  close(fd);
  fd=open("black2",O_RDWR);
  data a1,a2,a3,a4;
  strcpy(a1.u,"utkarsh");strcpy(a1.p,"agrawal");
  strcpy(a2.u,"satyam");strcpy(a2.p,"khare");
  strcpy(a3.u,"anirudh");strcpy(a3.p,"singh");
  strcpy(a4.u,"abhay");strcpy(a4.p,"nanda");

  write(fd,&a1,sizeof(a1));
  write(fd,&a2,sizeof(a2));
  write(fd,&a3,sizeof(a1));
  write(fd,&a4,sizeof(a2));

  close(fd);
  fd=open("black2",O_RDWR);
  while(read(fd,&a1,sizeof(a1)))
  {
    printf("%s %s\n",a1.u,a1.p);
    getchar();
    printf("%ld\n",lseek(fd,0,SEEK_CUR));
    if(strcmp(a1.u,"abhay")==0&&strcmp(a1.p,"nanda")==0)
    {
      printf("found\n");
      printf("%ld\n",lseek(fd,-1*sizeof(data),SEEK_CUR));
      break;
    }
  }

  strcpy(a1.u,"prabhanjan");strcpy(a1.p,"mentl");
  write(fd,&a1,sizeof(a1));
  close(fd);


















  fd=open("black2",O_RDONLY);
  while(read(fd,&a1,sizeof(a1)))
  {
    printf("%s %s\n",a1.u,a1.p);
    getchar();
    printf("%ld\n",lseek(fd,0,SEEK_CUR));
    if(strcmp(a1.u,"abhay")==0&&strcmp(a1.p,"nanda")==0)
    {
      printf("found\n");
      printf("%ld\n",lseek(fd,-1*sizeof(data),SEEK_CUR));
    }
  }




  close(fd);
}
