AS=arm-linux-as
LD=arm-linux-ld
mem:mem.s
	$(AS) -g -o mem.o mem.s
	$(LD) -Tdata=0x8e00 -o mem mem.o
run:
	qemu-arm -g 1234 mem

sim:
	arm-linux-gdb mem

clear:
	rm -rf *.o mem

