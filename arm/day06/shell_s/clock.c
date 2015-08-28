#include"clock.h"

//APLL:1GHz MPLL:667MHz EPLL:96MHz VPLL:54Mhz 
#define APLL_PDIV 0x03 
#define APLL_MDIV 0x7D
#define APLL_SDIV 0x01

#define MPLL_PDIV 0x0C
#define MPLL_MDIV 0x29B
#define MPLL_SDIV 0x01

#define EPLL_PDIV 0x03
#define EPLL_MDIV 0x30
#define EPLL_SDIV 0x02

#define VPLL_PDIV 0x06
#define VPLL_MDIV 0x6C
#define VPLL_SDIV 0x03

#define set_pll(mdiv,pdiv,sdiv)  ((1<<31)|(mdiv<<16)|(pdiv<<8)|(sidv))

void sys_clock_init(void){

     CLK_SRC0=0;
 
     APLL_LOCK=0xFFFF; 
     MPLL_LOCK=0xFFFF; 
    
     CLK_DIV0=0x14131440;

     APLL_CON0 =set_pll(APLL_MDIV,APLL_PDIV,APP_SDIV); 
     MPLL_CON  =set_pll(MPLL_MDIV,MPLL_PDIV,MPP_SDIV); 

      
     CLK_SRC0=0x10001111;
   
}
