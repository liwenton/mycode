#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
void print(const char *name){
   DIR* dir=opendir(name);
   char buf[100]={};
   if(dir==NULL)return ;
   struct dirent* dp;
   while(dp=readdir(dir)){
    if(dp->d_type==4&&strcmp(dp->d_name,".")&&strcmp(dp->d_name,"..")){
      printf("[%s]\n",dp->d_name);
      sprintf(buf,"%s/%s",name,dp->d_name);
      print(buf);
    }     
    else if(dp->d_type==8){
      printf("%s\n",dp->d_name);
    }
   }
}

int main(){
  print("../day05");
}
