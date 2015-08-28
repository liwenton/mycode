NAME=shell
BIN=$(NAME).bin
SRC=$(NAME).s
OBJ=$(NAME).o led.o string.o uart.o 
ELF=$(NAME)
AS=arm-linux-as
CC=arm-linux-gcc
LD=arm-linux-ld
OBJCOPY=arm-linux-objcopy
CFFLAGS=-march=armv5te -nostdlib
LDFLAGS=-nostartfiles -nostdlib
LDFLAGS+=-e shell_exe -Ttext=0x20008000
$(NAME):$(OBJ)
	$(LD) $(LDFLAGS)  -o $@ $(OBJ)
	$(OBJCOPY) -O binary $@ $(BIN)
%.o:%.s 
	$(AS) $(CFFLAGS) -o $@ $<

%.o:%.c  
	$(CC) $(CFFLAGS) -c -o $@ $<
clean:
	rm -f %.o %.bin $(ELF) $(OBJ) 
