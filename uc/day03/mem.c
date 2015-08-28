#include <stdio.h>
#include <stdlib.h>

int i1=10;//全局区
int i2; //BSS
static int i3=30;//全局区
const int i4=40;//只读区
void fa(int i5,int i9){//盏区
  int i6;//盏区
  static int i7=70;//全局
  const int i8=80;//盏区
  int *pi=malloc(4);//堆区
  char s1[]="abcd";//盏区
  char* s2="abcd";//只读区
  printf("s1[]=%p\n",s1);
  printf("------------------\n");
  printf("栈区\n"); 
  printf(" int   i5=%p\n",&i5);
  printf(" int   i9=%p\n",&i9);
  printf(" int   i6=%p\n",&i6);
  printf("const  i8=%p\n",&i8);
  
  printf("------------------\n");
  printf("堆区\n"); 
  printf(" int*  pi=%p\n",pi);

  printf("------------------\n");
  printf("BSS区\n"); 
  printf(" int   i2=%p\n",&i2);
 
  printf("------------------\n");
  printf("全局区\n");
  printf("static i7=%p\n",&i7);
  printf("static i3=%p\n",&i3);
  printf(" int   i1=%p\n",&i1);

  printf("------------------\n");
  printf("只读区\n");
  printf("char*  s2=%p\n",s2);
  printf("const  i4=%p\n",&i4);
}
int main(){

  fa(100,200);
  printf("------------------\n");
  printf("代码区\n");
  printf("       fa=%p\n",fa);
  printf("%d\n",getpid());
  while(1);
  return 0; 
}

