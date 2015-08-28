#include <stdio.h>
#include <string.h>
#include <unistd.h>


int main(){
   extern char**environ;
   char **p=environ;
   char value[100]={};
   for(;(*p)!=NULL;p++){
     if(!(strncmp(*p,"LANG=",5))){
        strcpy(value,*p);
        printf("%s\n",value);
      } 
   }
   return 0;
}
