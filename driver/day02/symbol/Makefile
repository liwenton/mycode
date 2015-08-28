MODNAME=printk_all
KERNELDIR=/home/rick/program/linux/linux-3.8
obj-m += $(MODNAME).o
obj-m += test_module.o
  
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)  modules
clean:
	rm -rf *.o *.ko *.mod.* .$(MODNAME).* .tmp* module* Module*
