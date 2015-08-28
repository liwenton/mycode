MODNAME=timer_led_drv
KERNELDIR=/home/rick/program/linux/linux-3.8
obj-m += $(MODNAME).o

  
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)  modules
	cp *.ko ~/nfs/rootfs/home

test_module:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)  modules

test_app:
	arm-linux-gcc -o $(APPNAME) $(APPNAME).c



clean:
	rm -rf *.o *.ko *.mod.* .$(MODNAME).* .tmp* module* Module* $(APPNAME)
