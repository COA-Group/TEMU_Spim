#include "trap.h"
   .set noat
   .globl main
   .text
main:
   li $s0, 0x7fffffff
   li $s2, -1          
   sub $s1 , $s0 , $s2

   HIT_GOOD_TRAP		#stop temu
   HIT_DECODE_TRAP
