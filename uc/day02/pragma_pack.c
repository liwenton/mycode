//指定结构体的对齐和补齐基准

#include <stdio.h>
#pragma pack(4)//指定某个对齐补齐的基准，节省空间，寻址慢
//一般设置为1、2
int main(){
  struct s{
   char c1;
   short int i;
   int i2;
   char c2;
  };
 printf("size=%d\n",sizeof(struct s));
 return 0;
}
