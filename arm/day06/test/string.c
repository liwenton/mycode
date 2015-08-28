#include"stdio.h"

int str_len(char *st){
       int len=0;
      while(*st!='\0'){
        len++;  
        st++;
      }
       return len;
}

//m的n次方
int str_pow(int n,int m){
   int sum=1;
   while(n--){
    sum=sum*m;
    }
   return sum;
}

//整形数字的有效长度//
int int_len(int s,int radix){
      int i=0;
     while(1){
       s=s/radix;
       i++;
      if(s==0)break;
    }
     return i;
}



//字符比较// 
int str_cmp(char *tar,char *src){
     if(str_len(tar)!=str_len(src))return 0;

     while(*tar!='\0'){
      if(*tar!=*src)return 0;
         tar++;
         src++;
      }
      return 1;
}

//整形转成不同进制的字符串//
/*void itoa(char *str,int intvalue,int radix){
     int i,value,temp;
     int size=int_len(intvalue);

     if(radix==16){
      (*str++)=48;
      (*str++)='X';
     }
     for(i=size-1;i>=0;i--){
        value=str_pow(i,radix);
        temp=intvalue/value;
        intvalue=intvalue %value;

      if(radix==16){
        if(temp>=10)
        temp=(temp-10)+'A';
        else
        temp=temp+48;
        }

        if(radix==10)
        temp=temp+48;

        *str=temp;
        str++;
       }
     *str='\0';
}
*/

void itoa(char *buf, unsigned int num)
{
    int i,len;
    if (0 == buf)
    {
        return ;
    }
    buf[0]='0';
    buf[1]='x';
     len=int_len(num,16)+2;
    for(i=len-1;i>=2;i--)
    {
        unsigned int tmp;
        tmp = num % 16;
        if (tmp >= 10)
        {
            buf[i] = tmp - 10 + 'A';
        }
        else
        {
            buf[i] = tmp + '0';
        }
        num /= 16;
    }

    buf[len] ='\0';
}

int main(){
  int shu,len;
  char itoa_buf[16];
   scanf("%d",&shu);
   itoa(itoa_buf,shu);
//   len=int_len(shu,16);
   printf("%s\n",itoa_buf);
//   printf("%d\n",len);
   return 0;
}

