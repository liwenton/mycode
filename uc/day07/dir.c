#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

int main(){
  DIR *dir=opendir("../day05");
  //while(dp=readdir(dir));
  while(1){
  struct dirent * dp=readdir(dir);
  if(dp==NULL)break;
  //d_type=4为目录，d_type=8为普通文件
  printf("d_type=%d,d_name=%s\n",dp->d_type,dp->d_name);
  printf("\n");
  }
}
