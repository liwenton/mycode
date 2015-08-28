
#include "itoa.h"

void itoa(char *buf, unsigned int num)
{
    int i;
    if (0 == buf)
    {
        return ;
    }

    buf[0]='0';
    buf[1]='x';

    i = 9;
    while(num)
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
        i--;
    }

    while (i >= 2)
    {
        buf[i--] = '0';
    }
    buf[10] = 0;
}

