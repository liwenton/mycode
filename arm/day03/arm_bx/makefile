NAME=bx
OBJ=$(NAME).o
SRC=$(NAME).s
BIN=$(NAME).bin

AS=arm-linux-as
LD=arm-linux-ld
OBJCOPY=arm-linux-objcopy
CFFLAGS=-march=armv5te 
LDFLAGS=-nostartfiles -nostdlib 
LDFLAGS+=-e _start -Ttext=0x20008000

$(NAME):$(OBJ)
	$(LD) $(LDFLAGS)  -o $@ $(OBJ)
	$(OBJCOPY) -O binary $@ $(BIN)

%.o:%.s
	$(AS) $(CFFLAGS) -o $@ $<


clear:
	rm -f %.o %.bin $(ELF) $(OBJ) 
