#include <stdio.h>

#include "expression.h"
#include "expression_calc_util.h"
#include "expression_tokenizer.h"

int      num = 0;
token_t  tokens[1024];
token_t* begin = tokens;

int main(void)
{
    tokenizerInit();
    char  str[1024];
    char* p = str;
    fgets(str, sizeof str, stdin);

    while (*p) {
        if ((tokens[num++] = getNextToken(&p)).type == TOKEN_SYNTAX_ERROR) {
            puts("SYNTAX ERROR ON TOKENIZING");
            exit(0);
        }
    }
    puts("\v");

    expr_node_t* node = createExprTree(&begin);

    if (node == NULL || begin->type != TOKEN_LIST_END) {
        puts("SYNTAX ERROR ON PARSING");
        exit(0);
    }

    printExprNode(node);
    puts("\v");

    printf("%lf\n", expr_tree_calc(node));

    freeExprTree(node);

    return 0;
}