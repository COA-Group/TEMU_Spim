#include "trap.h"
   .set noat
   .globl main
   .text
main:
   li $s0, 0x00000003           
   li $s1, 0x00000004
   add $s2, $s0, $s1
   li $s0, 0xC0000000           
   li $s1, 0x40000000
   add $s2, $s0, $s1           
   li $s0, 0x80000000           
   addi $s2, $s0, 0x8000              
   li $s0, 0x00000001           
   addi $s2, $s0, 0x0001  
   li $s0, 0xC0000000           
   li $s1, 0x40000000
   addu $s2, $s0, $s1 
   li $s0, 0x80000000           
   addiu $s2, $s0, 0x8000              
   li $s0, 0x00000001           
   addiu $s2, $s0, 0x0001 
   li $s0, 0x0000000C           
   li $s1, 0x00000005
   sub $s2, $s0, $s1  
   li $s0, 0x00000003           
   li $s1, 0x00000005
   sub $s2, $s0, $s1 
   li $s0, 0x0000000C           
   li $s1, 0x00000005
   subu $s2, $s0, $s1  
   li $s0, 0x00000003           
   li $s1, 0x00000005
   subu $s2, $s0, $s1

   li $s0, 0x00000006
   li $s1, 0x00000003
   slt $s2, $s0, $s1
   li $s0, 0x00000002
   li $s1, 0x00000003
   slt $s2, $s0, $s1
   li $s0, 0xfffffffe
   li $s1, 0xffffffff
   slt $s2, $s0, $s1
   li $s0, 0xffffffff
   li $s1, 0xfffffffb
   slt $s2, $s0, $s1
   li $s0, 0x00000006
   li $s1, 0xfffffffe
   slt $s2, $s0, $s1
   li $s0, 0xfffffffc
   li $s1, 0x00000005
   slt $s2, $s0, $s1

   li $s0, 0x00000006
   slti $s2, $s0, 0x0003
   li $s0, 0x00000002
   slti $s2, $s0, 0x0003
   li $s0, 0xfffffffe
   slti $s2, $s0, 0xffff
   li $s0, 0xffffffff
   slti $s2, $s0, 0xfffb
   li $s0, 0x00000006
   slti $s2, $s0, 0xfffe
   li $s0, 0xfffffffc
   slti $s2, $s0, 0x0005

   li $s0, 0x00000006
   li $s1, 0x00000003
   sltu $s2, $s0, $s1
   li $s0, 0x00000002
   li $s1, 0x00000003
   sltu $s2, $s0, $s1
   li $s0, 0xfffffffe
   li $s1, 0xffffffff
   sltu $s2, $s0, $s1
   li $s0, 0xffffffff
   li $s1, 0xfffffffb
   sltu $s2, $s0, $s1
   li $s0, 0x00000006
   li $s1, 0xfffffffe
   sltu $s2, $s0, $s1
   li $s0, 0xfffffffc
   li $s1, 0x00000005
   sltu $s2, $s0, $s1

   li $s0, 0x00000006
   sltiu $s2, $s0, 0x0003
   li $s0, 0x00000002
   sltiu $s2, $s0, 0x0003
   li $s0, 0xfffffffe
   sltiu $s2, $s0, 0xffff
   li $s0, 0xffffffff
   sltiu $s2, $s0, 0xfffb
   li $s0, 0x00000006
   sltiu $s2, $s0, 0xfffe
   li $s0, 0xfffffffc
   sltiu $s2, $s0, 0x0005

   li $s0, 0xa5c4023f
   li $s1, 0xcb460f36
   mult $s0, $s1

   li $s0, 0xa5c4023f
   li $s1, 0xcb460f36
   multu $s0, $s1

   li $s0, 0x0000005c
   li $s1, 0x00000096
   and $s2, $s0, $s1

   li $s0, 0x00009e5c
   andi $s2, $s0, 0xc096

   li $s0, 0x0000005c
   li $s1, 0x00000096
   nor $s2, $s0, $s1

   li $s0, 0x0000005c
   li $s1, 0x00000096
   or $s2, $s0, $s1

   li $s0, 0x00009e5c
   ori $s2, $s0, 0xc096

   li $s0, 0x0000005c
   li $s1, 0x00000096
   xor $s2, $s0, $s1

   li $s0, 0x00009e5c
   xori $s2, $s0, 0xc096

   li $s0, 0xe1ca62a3
   li $s1, 0x00000033
   sllv $s2, $s0, $s1

   sll $s2, $s0, 5
   sll $s2, $s0, 8

   srav $s2, $s0, $s1
   li $s3, 0x61ca62a3
   srav $s2, $s3, $s1

   sra $s2, $s0, 5
   sra $s2, $s0, 8
   li $s4, 0x21ca62a3
   sra $s2, $s4, 5

   srlv $s2, $s0, $s1
   srlv $s2, $s3, $s1

   srl $s2, $s0, 5
   srl $s2, $s0, 8
   srl $s2, $s3, 5

   mfhi $s5
   mflo $s5

   mthi $s0
   mtlo $s0

   li $s0, 0x00000001
   li $s1, 0x01018181
   sb $s1, -1($s0)

   li $s0, 0x00000004
   sh $s1, -2($s0)

   sw $s1, 4($s0)

   lb $s2, -4($s0)

   lbu $s2, -4($s0)

   lh $s2, -2($s0)

   lhu $s2, -2($s0)
  
   lw $s2, 4($s0)


   HIT_GOOD_TRAP
   HIT_DECODE_TRAP 
