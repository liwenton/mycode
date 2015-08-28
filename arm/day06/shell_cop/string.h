#ifndef __STRING_H_
#define __STRING_H_

int str_len(char *st);
int str_cmp(char *tar,char *src);
int int_len(int s,int radx);
int str_pow(int n,int m);
//void itoa(char *str,int intvalue,int radix);
void itoa(char *buf, unsigned int num,int radix);

#endif
