
AS=arm-linux-as
CC=arm-linux-gcc
LD=arm-linux-ld
OBJCOPY=arm-linux-objcopy

AFLAGS=-march=armv5te 
CFLAGS=-march=armv5te -nostdlib
LDFLAGS=-nostartfiles -nostdlib
#LDFLAGS+=-e main -Ttext=0x20008000  -T shell.lds
LDFLAGS+=-e main -T shell.lds 
PROG=shell

OBJS=start.o dram.o irq.o setmmu_table.o \
     vector.o shell.o uart.o \
     delay.o led.o a_strcmp.o \
     cmd.o itoa.o nand.o

BIN=$(PROG).bin

$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) -o $@  $(OBJS)
	
	$(OBJCOPY) -O binary $@  $(BIN)



%.o:%.s
	$(AS) $(AFLAGS) -o $@ $< 

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@  $< 



clean:
	rm -rf  $(OBJS) $(PROG) $(BIN)

