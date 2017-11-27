CC=i686-elf-gcc
CFLAGS=-c -ffreestanding -O2 -Wall -Wextra -Werror
LDFLAGS=-T linker.ld -ffreestanding -O2 -nostdlib -lgcc
all: myos grub
myos: kernel.o boot.o vgatm.o
	$(CC) $(LDFLAGS) kernel.o boot.o vgatm.o -o myos.bin
kernel.o: kernel.c 
	$(CC) $(CFLAGS) kernel.c -o kernel.o
vgatm.o: vgatm.c
	$(CC) $(CFLAGS) vgatm.c -o vgatm.o
boot.o: boot.s
	$(CC) $(CFLAGS) boot.s -o boot.o
grub:
	cp myos.bin isodir/boot
	grub2-mkrescue -o myos.iso isodir
clean:
	rm -f *.o *.bin *.iso
