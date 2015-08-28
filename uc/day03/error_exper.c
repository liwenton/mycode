#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//通过max函数，比较两个数字。当数字相同，返回错误，当数字不相同，通过指针带出
int max(int x,int y,int* r){
  if(x==y)return -1;
  else *r=(x>y)?x:y;
  return 0;
}

//通过rand10函数，得到一个随即数，不存在负数的结果，当ran=5就返回失败
int rand10(){
  srand(time(0));
  int ran=rand()%10;
  if(ran==5)return -1;
  return ran;  
}

//等于NULL表示错误
char* isError(const char* str){
  if(strcmp(str,"error"))return NULL;
   return "ok";
}
 
void print(const char * str){
  printf("%s\n",str);
} 
  
int main(){
  int i;
  int r=max(2,4,&i);
  if(r==-1)printf("数据无大小\n");
   else printf("max=%d\n",i);
  r=rand10();
  printf("rand=%d\n",r);
  char*s=isError("error");
  printf("%s\n",s);

}

