#include "trap.h"
   .set noreorder
   .globl main
   .text
main:
   ori $v0, $zero, 0x100         
   ori $v1, $zero, 0x99
   divu $v0, $v1
   
   mfhi $a0
   mflo $a1
   syscall
   nop
   HIT_GOOD_TRAP
   HIT_DECODE_TRAP 
