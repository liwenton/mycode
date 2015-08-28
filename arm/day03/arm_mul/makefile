AS=arm-linux-as
LD=arm-linux-ld

mul:mul.s
	$(AS) -o mul.o mul.s
	$(LD) -o mul mul.o
clear:
	rm -rf *.o mul
run:
	qemu-arm -g 1234 mul
sim:
	arm-linux-gdb mul
