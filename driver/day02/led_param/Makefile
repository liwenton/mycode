MODNAME=led_param
KERNELDIR=/home/rick/program/linux/linux-3.8
obj-m += $(MODNAME).o

  
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)  modules
	cp *.ko ~/nfs/rootfs/home

clean:
	rm -rf *.o *.ko *.mod.* .$(MODNAME).* .tmp* module* Module*
