#ifndef _EXPR_TOKENIZER_H

#define _EXPR_TOKENIZER_H

typedef enum {
    TOKEN_IMME,
    TOKEN_OPER_ADD,
    TOKEN_OPER_SUB,
    TOKEN_OPER_MUL,
    TOKEN_OPER_DIV,
    TOKEN_OPER_LBRACE,
    TOKEN_OPER_RBRACE,
    TOKEN_SYNTAX_ERROR
} token_type_t;

typedef struct {
    token_type_t type;
    double       data;
} token_t;

token_t getNextToken(char** const str);

#endif