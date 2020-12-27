### how to run this programme

1. open the project with Qt 5.9.0.
2. goto "project" and add path to mips-sde-elf-gcc in Build Environment.
3. add path to Sourcery_CodeBench_Lite_for_MIPS_ELF/bin in Run Environment.
3. ctrl_r to run the program.

### how to use

1. click file in MenuBar and click open.
2. select a .S file that you want to test.
  - caution: 
    - you need to add "HIT_GOOD_TRAP" at the end of the main function to tell TEMU_Spim that the running has ended.
    - you need to add "HIT_DECODE_TRAP" at the end of the code to tell the TEMU_Spim that the program's end is here.
3. input command in the lineEdit at tht bottom then you can debug your program
