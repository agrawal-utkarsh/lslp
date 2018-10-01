#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
int main(void)
{
  int fd;
  fd=open("black_lock",O_RDONLY);

  struct flock lock;
  lock.l_type=F_RDLCK;
  lock.l_start=0;
  lock.l_len=0;
  lock.l_pid=getpid();
  lock.l_whence=SEEK_SET;
  fcntl(fd,F_SETLKW,&lock);


  printf("file opened\n");
  char buf[50];
  int output=read(fd,buf,50);
  printf("%d\n",output);
}
