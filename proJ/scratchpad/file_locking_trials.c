#include<unistd.h>
#include<fcntl.h>
int main()
{
  //fcntl(fd,F_SETLK,flock lock);
  /*
  l_type
  l_whence
  l_start
  l_len
  l_pid
  */
  struct flock lock;
  lock.l_type=F_RDLCK;
  lock.l_whence
  int fd;
  fd=open();
  return 0;
}
