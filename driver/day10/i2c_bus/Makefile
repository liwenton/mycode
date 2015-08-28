module_name:=i2c-s3c2410

obj-m:=$(module_name).o

KERNELDIR ?=/home/rick/program/linux/linux-2.6.35.7

PWD :=$(shell pwd)

default:
	$(MAKE) -Wall -C $(KERNELDIR) M=$(PWD) modules
	cp *.ko  ~/nfs/rootfs/home

clean:
	rm -rf *.o *~ *.ko *.mod.c *.order *.symvers .*.o.cmd .*.ko.cmd
