MODNAME=helloworld
KERNELDIR=/home/rick/program/linux/linux-3.8
obj-m += $(MODNAME).o
  
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)  modules
