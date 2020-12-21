//addadd
#include "../TEMU/temu/include/temu.h"
#include "stdlib.h"
#include <sys/types.h>
#include <regex.h>


enum {
    NOTYPE = 256, //spaces
    NUM,          //decimal number 十进制
    HEX,          //hexadecimal number 十六进制0x开头
    REG,          //reg name 寄存器 $开头

    EQ,           //equal
    NEQ,          //not equal

    AND,          //与
    OR,           //或
};

static struct rule {
    char *regex;
    int token_type;
} rules[] = {
    {"\\b0[xX][0-9a-fA-F]+\\b",HEX},      // hexadecimal number
    {"\\$(zero|at|v0|v1|a0|a1|a2|a3|t0|t1|t2|t3|t4|t5|t6|t7|s0|s1|s2|s3|s4|s5|s6|s7|t8|t9|k0|k1|gp|sp|fp|ra|pc)",REG},                 // reg name
    {"!=",NEQ},                           // not equal
    {"&&",AND},                           // and
    {"\\|\\|",OR},                         // or
    {" +",	NOTYPE},		      // spaces
    {"==", EQ},			      // equal
    {"\\+",'+'},                          // add
    {"-",'-'},                            // sub
    {"\\*",'*'},                          // multi
    {"/",'/'},                            // divide
    {"\\(",'('},                          // left bracket
    {"\\)",')'},                          // right bracket
    {"\\b[0-9]+\\b",NUM},               // number
    {"!",'!'}                          //
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

void init_regex() {
    int i;
    char error_msg[128];
    int ret;

    for(i = 0; i < NR_REGEX; i ++) {
        ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
        if(ret != 0) {
            regerror(ret, &re[i], error_msg, 128);
            Assert(ret == 0, "regex compilation failed: %s\n%s", error_msg, rules[i].regex);
        }
    }
}

typedef struct token {
    int type;
    char str[32];
} Token;

Token tokens[32];
int nr_token;

static bool make_token(char *e) {
    int position = 0;
    int i;
    regmatch_t pmatch;
    nr_token = 0;
    while(e[position] != '\0') {//check all token
        for(i = 0; i < NR_REGEX; i ++) {//for a token, check all roles
            if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {//the token is valid
                char *substr_start = e + position;
                int substr_len = pmatch.rm_eo;
                position += substr_len;
                switch(rules[i].token_type) {//confirm token type
                    case NOTYPE: break;
                    case NUM: case HEX: case REG:
                        sprintf(tokens[nr_token].str, "%.*s", substr_len, substr_start);
                    default:
                        tokens[nr_token].type = rules[i].token_type;
                        nr_token ++;
                }
                break;
            }
        }
        if(i == NR_REGEX) {//invalid token, return failed
            printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
            return false;
        }
    }
    return true;
}

bool check_parentheses(int p, int q) {
    if (tokens[p].type == '(' && tokens[q].type == ')') {//there are a pair of brackets
        int buf[32];
        int i, j = 0, rec = -1;
        for (i = p; i <= q; i++) {//Make sure the brackets appear in pairs
            if (tokens[i].type == '(') buf[j++] = i;
            else if (tokens[i].type == ')') {
                if (j == 0) return false;
                rec = buf[--j];
            }
        }
        if (rec == p) return true;
    }
    return false;//not in pairs
}

int find_domn(int p, int q) {
    int i;
    int bracket_level = 0;
    int dominated_op = -1;
    for(i = p; i <= q; i ++) {//check all tokens
        switch(tokens[i].type) {//check the caculate level by token type
            case REG: case NUM: case HEX: break;
            case '(':
                bracket_level ++;
                break;
            case ')':
                bracket_level --;
                if(bracket_level < 0) {
                    return 0;
                }
                break;
            default:
                if(bracket_level == 0) {
                    if(dominated_op == -1) {
                        dominated_op = i;
                    }
                }
                break;
        }
    }
    return dominated_op;
}

int eval(int p, int q) {
    if (p > q) {// bad expression!
        assert(0);
    }
    else if (p == q) {// this is a value or a register
        switch (tokens[p].type) {//find result by the given token
            //char* rec = NULL;
            char temp[5];
            case NUM:
                return atoi(tokens[p].str);
            case HEX:
                return strtol(tokens[p].str, NULL, 16);
            case REG:
                strcpy(temp, tokens[p].str);

                if (!strcmp(temp, "$zero")) return cpu.gpr[0]._32;
                else if (!strcmp(temp, "$at")) return cpu.gpr[1]._32;

                else if (!strcmp(temp, "$v0")) return cpu.gpr[2]._32;
                else if (!strcmp(temp, "$v1")) return cpu.gpr[3]._32;

                else if (!strcmp(temp, "$a0")) return cpu.gpr[4]._32;
                else if (!strcmp(temp, "$a1")) return cpu.gpr[5]._32;
                else if (!strcmp(temp, "$a2")) return cpu.gpr[6]._32;
                else if (!strcmp(temp, "$a3")) return cpu.gpr[7]._32;

                else if (!strcmp(temp, "$t0")) return cpu.gpr[8]._32;
                else if (!strcmp(temp, "$t1")) return cpu.gpr[9]._32;
                else if (!strcmp(temp, "$t2")) return cpu.gpr[10]._32;
                else if (!strcmp(temp, "$t3")) return cpu.gpr[11]._32;
                else if (!strcmp(temp, "$t4")) return cpu.gpr[12]._32;
                else if (!strcmp(temp, "$t5")) return cpu.gpr[13]._32;
                else if (!strcmp(temp, "$t6")) return cpu.gpr[14]._32;
                else if (!strcmp(temp, "$t7")) return cpu.gpr[15]._32;

                else if (!strcmp(temp, "$s0")) return cpu.gpr[16]._32;
                else if (!strcmp(temp, "$s1")) return cpu.gpr[17]._32;
                else if (!strcmp(temp, "$s2")) return cpu.gpr[18]._32;
                else if (!strcmp(temp, "$s3")) return cpu.gpr[19]._32;
                else if (!strcmp(temp, "$s4")) return cpu.gpr[20]._32;
                else if (!strcmp(temp, "$s5")) return cpu.gpr[21]._32;
                else if (!strcmp(temp, "$s6")) return cpu.gpr[22]._32;
                else if (!strcmp(temp, "$s7")) return cpu.gpr[23]._32;

                else if (!strcmp(temp, "$t8")) return cpu.gpr[24]._32;
                else if (!strcmp(temp, "$t9")) return cpu.gpr[25]._32;

                else if (!strcmp(temp, "$k0")) return cpu.gpr[26]._32;
                else if (!strcmp(temp, "$k1")) return cpu.gpr[27]._32;


                else if (!strcmp(temp, "$gp")) return cpu.gpr[28]._32;
                else if (!strcmp(temp, "$sp")) return cpu.gpr[29]._32;
                else if (!strcmp(temp, "$fp")) return cpu.gpr[30]._32;
                else if (!strcmp(temp, "$ra")) return cpu.gpr[31]._32;
                else if (!strcmp(temp, "$pc")) return cpu.pc;
        }
    }
    else if (check_parentheses(p, q) == true) return eval(p + 1, q - 1);//there are a pair of brackets
    else {//need to calculate
        int op = find_domn(p, q);
        if (tokens[op].type == '!') {
            uint32_t val= eval(op + 1, q);
            return !val;
        }
        int eval1 = eval(p, op - 1);
        int eval2 = eval(op + 1, q);
        switch(tokens[op].type) {
            case '+': return eval1 + eval2;
            case '-': return eval1 - eval2;
            case '*': return eval1 * eval2;
            case '/': return eval1 / eval2;
            case AND: return eval1 && eval2;
            case OR:  return eval1 || eval2;
            case EQ: return eval1 == eval2;
            case NEQ: return eval1 != eval2;
            default: assert(0);
        }
    }
    return 0;
}

uint32_t expr(char *e, bool *success) {
    if(!make_token(e)) {
        *success = false;
        return 0;
    }
       *success =true;
    return eval(0, nr_token - 1);
}

