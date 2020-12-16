cd ../TEMU/mips_sc
mips-sde-elf-gcc -v
make clean
make USER_PROGRAM=$1
echo 'complete'
