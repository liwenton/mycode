NAME=shell
BIN=$(NAME).bin
SRC=$(NAME).s
OBJ=$(NAME).o led.o  uart.o delay.o string.o nand.o cmd.o 
ELF=$(NAME)
AS=arm-linux-as
CC=arm-linux-gcc
LD=arm-linux-ld
OBJCOPY=arm-linux-objcopy
CFFLAGS=-march=armv5te -nostdlib
ASFLAGS=-march=armv5te 
LDFLAGS=-nostartfiles -nostdlib
LDFLAGS+=-e shell_exe  -T  shell.lds
$(NAME):$(OBJ)
	$(LD) $(LDFLAGS)  -o $@ $(OBJ)
	$(OBJCOPY) -O binary $@ $(BIN)
	cp $(BIN)  /tftpboot

%.o:%.s 
	$(AS) $(ASFLAGS) -o $@ $<

%.o:%.c  
	$(CC) $(CFFLAGS) -c -o $@ $<
clean:
	rm -f %.o %.bin $(ELF) $(OBJ) 
