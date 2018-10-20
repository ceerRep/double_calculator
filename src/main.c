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
    scanf("%s", str);

    while (*p)
        if ((tokens[num++] = getNextToken(&p)).type == TOKEN_SYNTAX_ERROR) {
            puts("SYNTAX ERROR");
            break;
        }
    puts("\v");

    expr_node_t* node = createExprTree(&begin);
    printExprNode(node);
    puts("\v");

    printf("%lf\n", expr_tree_calc(node));

    return 0;
}