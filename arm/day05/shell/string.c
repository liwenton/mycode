#include"string.h"

int str_len(char *st){
       int len=0;
      while(*st!='\0'){
        len++;  
        st++;
      }
       return len;
}
 
int str_cmp(char *tar,char *src){
     if(str_len(tar)!=str_len(src))return 0;

     while(*tar!='\0'){
      if(*tar!=*src)return 0;
         tar++;
         src++;
      }
      return 1;
}
