rm -r ./obj/*

nasm -f bin OS/boot.asm -o os.bin
nasm -f bin OS/stage2.asm -o s.o
nasm -fbin OS/core/Test.asm -o test.o
nasm -fbin OS/core/DoubleBuffer.asm -o db.o

cat s.o >> os.bin
cat db.o >> os.bin

qemu-system-x86_64 -hda os.bin
mv ./*.bin ./obj
mv ./*.o ./obj
