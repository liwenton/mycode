#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

void print(const char *name){
  char buf[100]={};
  DIR *dp=opendir(name);
   if(dp==NULL)return;
//  chdir(name);
  while(1){
  struct dirent* dir=readdir(dp);
  if(dir==NULL)break;
  if((dir->d_type==4)){ //d_type=4时是目录，d_type=8时是文件
   if(strcmp(dir->d_name,".")&&strcmp(dir->d_name,"..")){
      printf("[%s]\n",dir->d_name);
      sprintf(buf,"%s/%s",name,dir->d_name);
      print(dir->d_name);
      printf("\n");
    }
  }
  else if(dir->d_type==8){ 
   printf("%s\n",dir->d_name);
  }
 }
//  chdir("..");
}

int main(){
  print("../day05");
}
