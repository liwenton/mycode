MODNAME=at24c02_drv
APPNAME=at24c02_test
KERNELDIR=/home/rick/program/linux/linux-2.6.35.7
obj-m += $(MODNAME).o
  
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)  modules
	arm-linux-gcc -o $(APPNAME) $(APPNAME).c
	cp *.ko ~/nfs/rootfs/home
	cp $(APPNAME)  ~/nfs/rootfs/home

test_module:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)  modules

test_app:
	arm-linux-gcc -o $(APPNAME) $(APPNAME).c



clean:
	rm -rf *.o *.ko *.mod.* .$(MODNAME).* .tmp* module* Module* $(APPNAME)
