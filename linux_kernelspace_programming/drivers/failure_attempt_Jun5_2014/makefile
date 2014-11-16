#obj-m += hello-1.o
#DESTINATION="/home/alshamlan/vtilt_git/minerva-5.x/sigma/kernel_source/linux-2.6.22.19/"
obj-m += kernel_mod_hello_word

all:
	sudo apt-get install linux-headers-$(shell uname -r)
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
