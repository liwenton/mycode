
AS=arm-linux-as
CC=arm-linux-gcc
LD=arm-linux-ld
OBJCOPY=arm-linux-objcopy

AFLAGS=-march=armv5te 
CFLAGS=-march=armv5te -nostdlib
LDFLAGS=-nostartfiles -nostdlib
LDFLAGS+=-e uart_test -Ttext=0x20008000 
PROG=uart
OBJS=uart_test.o uart.o delay.o
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

