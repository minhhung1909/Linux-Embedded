obj-m+=i2cexbar.o

KDIR=/mnt/D4D2E800D2E7E4A8/linuxCompoment/BBB/src/kernelbuildscripts/KERNEL

all:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -C $(KDIR) M=$(shell pwd) modules

clean:
	make -C $(KDIR) M=$(shell pwd) clean