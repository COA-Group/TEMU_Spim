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
   
   li $s0, 0x10
   li $s1, 0x4
   mult $s0, $s1
   
   mfhi $a0
   mflo $a1
   
   li $s0, 0x80000000
   li $s1, 0x2
   multu $s0, $s1
   
   mfhi $a0
   mflo $a1
   
   syscall
   nop
   HIT_GOOD_TRAP
   HIT_DECODE_TRAP 
