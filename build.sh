rm -r ./obj/*

nasm -f elf -i OS/Assembly OS/entry.asm -o entry.o
g++ -w -fpermissive -m32 -fno-stack-protector -c OS/kernel.cpp -o kernel.o -I OS/Core -I OS/Drivers
ld -m elf_i386 -T OS/link.ld -o kernel.bin kernel.o entry.o 

#grub-mkrescue -o AwkieOS.iso ./OS
rm OS/kernel.bin
qemu-system-i386 -kernel kernel.bin -hda Sector -fda Sector

sudo mv ./*.o ./obj/
sudo mv ./*.bin ./obj/