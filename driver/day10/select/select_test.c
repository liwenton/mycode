#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
int main(void){

           fd_set rfds;
           struct timeval tv;
           int retval;
           char buf[1024];
           
           memset(buf,0,1024);

           /* Watch stdin (fd 0) to see when it has input. */

           /* Wait up to five seconds. */
             
         while(1){
           FD_ZERO(&rfds);  //清除读文件描述符集合
           FD_SET(0, &rfds);//添加对标准输入的监听
           tv.tv_sec = 3;
           tv.tv_usec = 0;
           retval = select(1, &rfds, NULL, NULL, &tv);
           /* Don't rely on the value of tv now! */

           if (retval == -1)   //调用出错
               perror("select()");

           else if(retval){
               printf("Data is available now.\n");
               if(FD_ISSET(0,&rfds)){
                  read(0,buf,1024);
                  printf("massega:%s\n",buf);
              }
           }
           else
               printf("No data within five seconds.\n");
        }
           exit(EXIT_SUCCESS);
       }
