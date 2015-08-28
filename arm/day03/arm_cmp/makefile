AS=arm-linux-as
LD=arm-linux-ld

cmp:cmp.s
	$(AS) -g -o cmp.o cmp.s
	$(LD) -o cmp cmp.o
run:
	qemu-arm -g 1234 cmp
sim:
	arm-linux-gdb cmp
