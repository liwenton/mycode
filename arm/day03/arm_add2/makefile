
AS=arm-linux-as
LD=arm-linux-ld
add:add.s
	$(AS) -o add.o add.s
	$(LD) -o add add.o

run:
	qemu-arm -g 1234 add

sim:
	arm-linux-gdb add

clear:
	rm -rf *.o add
