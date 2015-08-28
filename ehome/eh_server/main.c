#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <dirent.h>

#include <dlfcn.h>

#include "emi/emi.h"

#define RECEIVER_DIR  "/home/receiver/"


int main(){
   DIR *pdir=NULL;
   struct dirent *ent=NULL;
   char tmp[1024]=RECEIVER_DIR;
   void *handle=NULL;

   int (*func)()=NULL;

   emi_init();

	/*1.open directory "/home/receiver"*/
    pdir=opendir(RECEIVER_DIR);
    if(pdir==NULL){
       printf("cann't open /home/receiver\n");
       return -1;
    }

	/*2.cycle read file name*/
    while((ent==readdir(pdir))!=NULL){
       printf("file name=%s\n",ent->d_name);
     	/*3.compare file name "*.so"*/
     if(strstr(ent->d_name,".so")){
     	/*4.loader.so*/
        strcat(tmp,ent->d_name);
        handle=dlopen(tmp,RTLD_LAZY);  //打开共享库
        if(!handle){
          dlerror();
          continue;
        }

     /*5.register msg_nu handl*/
       func=dlsym(handle,"__receiver_plugin_register_init");

        if(func()){
	  printf("register failed!\n");
          continue;
        }
        else{
          printf("register successed!\n");
        }  
       }
    }

     closedir(pdir);
     while(1){
      pause();
     }

    return 0;
}
