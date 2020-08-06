mkdir -p build
cd build
sh3eb-elf-gcc -Wall -c ../src/*.c `fxsdk --cflags` -O2
sh3eb-elf-gcc *.o -o tmp.elf `fxsdk --cflags --libs`
sh3eb-elf-objcopy -R .comment -R .bss -O binary tmp.elf tmp.bin
g1a-wrapper tmp.bin -o ../MrJint.g1a -i ../assets/icon.bmp
cd ..
rm build/*
