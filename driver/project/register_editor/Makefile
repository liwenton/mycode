MODNAME=register_drv
APPNAME=register_test
KERNELDIR=/home/rick/program/linux/linux-3.8_webee210
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
