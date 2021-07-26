rm -r ./obj/*

nasm -f elf OS/entry.asm -o entry.o
g++ -w -fpermissive -m32 -fno-stack-protector -c OS/kernel.cpp -o kernel.o
ld -m elf_i386 -T OS/link.ld -o kernel.bin entry.o kernel.o
grub-mkrescue -o AwkieOS.iso ./

qemu-system-i386 -kernel ./kernel.bin

sudo mv ./*.o ./obj/
sudo mv ./*.bin ./obj/