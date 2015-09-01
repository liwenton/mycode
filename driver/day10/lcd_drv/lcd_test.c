#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<linux/fb.h>
#include<time.h>

#define COLOR_RED          0x00ff0000
#define COLOR_GREEN      0x0000ff00
#define COLOR_BLUE         0x000000ff

struct lcd_info{
     int fdfb;
     int *fbadd;
     struct fb_fix_screeninfo fix;
     struct fb_var_screeninfo var;
};

struct lcd_info lcd;

int main(int argc,char **argv){
	int x,y,color=0;
        char input[10];
	lcd.fdfb=open(argv[1],O_RDWR);
	if(lcd.fdfb < 0)
	{
		printf("Failure to open framebuffer device: /dev/fb0 !\n");
		exit(-1);
	}

	if(ioctl(lcd.fdfb,FBIOGET_VSCREENINFO,&lcd.var))
	{
		printf("Failure to get var screen information !\n");
		exit(-2);
	}

	if(ioctl(lcd.fdfb,FBIOGET_FSCREENINFO,&lcd.fix))
	{
		printf("Failure to get fixed screen information !\n");
		exit(-3);
	}

	lcd.fbadd=mmap(0, lcd.fix.smem_len, PROT_WRITE | PROT_READ, MAP_SHARED, lcd.fdfb, 0);
    if(lcd.fbadd == NULL)
	{
		printf("Failure to map framebuffer device memory to process's memory !\n");
		exit(-4);
    }
	else
	{
		printf("Success to map framebuffer device memory to process's memory !\n");
	}

	while(1)
	{  
		printf("lcd color test!\n");
        scanf("%s",input);

        if(!strcmp(input,"red"))
		{
           color=COLOR_RED;
		}
        else if(!strcmp(input,"green"))
		{
           color=COLOR_GREEN;
		}
        else if(!strcmp(input,"blue"))
		{
           color=COLOR_BLUE;
		}
        else if(!strcmp(input,"quit"))
		{
            break;
		}
		else{
        	printf("input color error,input again!\n");
           	continue;
		}

		for(y=0;y<lcd.var.yres;y++)
		{
			for(x=0;x<lcd.var.xres;x++)
			{
				*(lcd.fbadd+ y*lcd.var.xres +x)=color;
       		}
   		}

	}

	munmap(lcd.fbadd, lcd.fix.smem_len);
	
	printf("Finished to demo to operate framebuffer !\n");
	close( lcd.fdfb );
 	
  }
