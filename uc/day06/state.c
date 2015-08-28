#include <stdio.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
  struct stat s={};
  if(argc<2){
  printf("unformat input\n");
  return -1;
 }
  int res=stat(argv[1], &s);
  if(res==-1)perror("open"),exit(-1);
  printf("inode=%d\n",s.st_ino);
  printf("size=%d\n",s.st_size);
  printf("blksize=%d\n",s.st_blksize);
  printf("link=%d\n",s.st_nlink);
  printf("modify time=%s",ctime(&s.st_mtime));
  printf("mode=%o\n",s.st_mode);
  printf("权限=%o\n",s.st_mode&0777);
/*  if(S_ISREG(s.st_mode))
   printf("普通文件\n");
  else if(S_ISCHR(s.st_mode))
   printf("字符设备\n");
  else if(S_ISBLK(s.st_mode))
   printf("块设备\n");
  else if(S_ISDIR(s.st_mode))
   printf("目录\n");
 */  
  if(s.st_mode & S_IFREG)
   printf("普通文件\n");
 
}
