NAME=led_s
BIN=$(NAME).bin
SRC=$(NAME).s
OBJ=$(NAME).o
ELF=$(NAME)
AS=arm-linux-as
LD=arm-linux-ld
OBJCOPY=arm-linux-objcopy
CFFLAGS=-march=armv5te
LDFLAGS=-nostartfiles -nostdlib
LDFLAGS+=-e led_main -Ttext=0x20008000
$(NAME):$(OBJ)
	$(LD) $(LDFLAGS)  -o $@ $(OBJ)
	$(OBJCOPY) -O binary $@ $(BIN)
%.o:%.s 
	$(AS) $(CFFLAGS) -o $@ $<

clean:
	rm -f %.o %.bin led_s
