#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
  //fcntl(fd,F_SETLK,flock lock);
  /*
  l_type F_RDLCK F_WRLCK F_UNLCK
  l_whence SEEK_SET : l_start relative to start of file             lock starts from 0+l_start
           SEEK_CUR : l_start relative to current of file           lock starts from current_cursor_position+l_start
           SEEK_END : l_start relative to end of file               lock starts from end_of_file+l_start
  l_start
  l_len
  l_pid
  */
  /*
    l_type  opening_mode return_value
  F_RDLCK -> readonly  : 0
             writeonly : -1
             readwrite : 0
  F_WRLCK -> readonly  : -1
             writeonly : 0
             readwrite : 0
  */
  struct flock lock;
  lock.l_type=F_RDLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start=0;
  lock.l_len=0;
  lock.l_pid=getpid();
  int fd;
  fd=open("black_lock",O_WRONLY);
  for(int i=0;i<10;i++)
  write(fd,"utkarsh",7);
  close(fd);

  fd=open("black_lock",O_RDWR);
  if(fd)
  {
    int res=fcntl(fd,F_SETLKW,&lock);
    printf("%d lock set\n",res);
    getchar();//critical section
    lock.l_type=F_UNLCK;
    res=fcntl(fd,F_SETLKW,&lock);
    printf("%d lock unset\n",res);
  }
  return 0;
}
