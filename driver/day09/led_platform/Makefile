MODNAME=led_platformdriver
#APPNAME
KERNELDIR=/home/rick/program/linux/linux-3.8
obj-m += $(MODNAME).o
obj-m +=led_platformdevice.o
  
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)  modules
	#arm-linux-gcc -o $(APPNAME) $(APPNAME).c -lm
	cp *.ko ~/nfs/rootfs/home
	#cp $(APPNAME)  ~/nfs/rootfs/home

test_module:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)  modules

test_app:
	arm-linux-gcc -o $(APPNAME) $(APPNAME).c



clean:
	rm -rf *.o *.ko *.mod.* .$(MODNAME).* .tmp* module* Module* $(APPNAME)
