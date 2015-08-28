MODNAME=adc_drv
APPNAME=misc_led_test
KERNELDIR=/home/rick/program/linux/android-kernel-samsung-dev
obj-m += $(MODNAME).o
  
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)  modules
#	arm-linux-gcc -o $(APPNAME) $(APPNAME).c
	cp *.ko /tftpboot
#	cp $(APPNAME)  ~/nfs/rootfs/home

test_module:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)  modules

test_app:
	arm-linux-gcc -o $(APPNAME) $(APPNAME).c



clean:
	rm -rf *.o *.ko *.mod.* .$(MODNAME).* .tmp* module* Module* $(APPNAME)
