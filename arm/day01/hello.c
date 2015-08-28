#include <stdio.h>
#include <stdlib.h>
void func(int a,int b,int c){
    a=b;
    b=c;
}
int main(){
//  int a=10;
//  int b=20;
//  int c=0;
//  a=b;
  func(10,20,30);
  return 0;

}
