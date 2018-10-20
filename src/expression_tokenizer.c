#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

#include "expression_tokenizer.h"

#define DOUBLE_NUM_BEFORE_DOT 1
#define DOUBLE_NUM_AFTER_DOT 3
#define DOUBLE_EXPO_START 5
#define DOUBLE_EXPO_SIGN 6
#define DOUBLE_EXPO_VAL 7

const char* double_pattern = "^([0-9]*)(\\.?)([0-9]*)(([eE])([+-]?)([0-9]+))?";
const char* oper_pattern   = "^[*/()+-]";

const size_t nmatch = 10;
regmatch_t   pmatch[nmatch];

regex_t double_reg;
regex_t oper_reg;

int tokenizerInit()
{
    return regcomp(&double_reg, double_pattern, REG_EXTENDED)
           || regcomp(&oper_reg, oper_pattern, REG_EXTENDED);
}

int isMismatched(regmatch_t pm)
{
    return pm.rm_so >= pm.rm_eo;
}

int checkIfIMME(const char* str)
{
    if (regexec(&double_reg, str, nmatch, pmatch, 0)) {
        return 0;
    }
    else if (isMismatched(pmatch[DOUBLE_NUM_BEFORE_DOT]) && isMismatched(pmatch[DOUBLE_NUM_AFTER_DOT])) {
        return 0;
    }
    else
        return 1;
}

int checkIfOper(const char* str)
{
    if (regexec(&oper_reg, str, nmatch, pmatch, 0))
        return 0;
    else
        return 1;
}

token_t getNextToken(char** const str)
{
    token_t ret;

    while ((**str) && isspace(**str))
        (*str)++;
    if (!(**str)) {
        ret.type = TOKEN_SYNTAX_ERROR;
        return ret;
    }

    if (checkIfIMME(*str)) {
        ret.type = TOKEN_IMME;
        ret.data = atof(*str);
        printf("IMME#%.1le ", ret.data);
    }
    else if (checkIfOper(*str)) {
        switch (**str) {
        case '+':
            ret.type = TOKEN_OPER_ADD;
            break;
        case '-':
            ret.type = TOKEN_OPER_SUB;
            break;
        case '*':
            ret.type = TOKEN_OPER_MUL;
            break;
        case '/':
            ret.type = TOKEN_OPER_DIV;
            break;
        case '(':
            ret.type = TOKEN_OPER_LBRACE;
            break;
        case ')':
            ret.type = TOKEN_OPER_RBRACE;
            break;
        default:
            ret.type = TOKEN_SYNTAX_ERROR;
            break;
        }
        printf("OPER#%c ", **str);
    }
    else {
        ret.type = TOKEN_SYNTAX_ERROR;
    }
    if (ret.type != TOKEN_SYNTAX_ERROR) {
        *str += pmatch[0].rm_eo - pmatch[0].rm_so;
    }
    return ret;
}
