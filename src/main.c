#include <stdio.h>
#include <string.h>

#include "double_t_util.h"
#include "expression.h"
#include "expression_calc_util.h"
#include "expression_tokenizer.h"

int      num = 0;
token_t  tokens[1024];
token_t* begin = tokens;

int main(void)
{

    //DOUBLET naive = float10ToDOUBLET("2", "225073858507200394958941034839315711", -308);

    //printf("%lf\n", 1e100);

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
    //puts("\v");

    expr_node_t* node = createExprTree(&begin);

    if (node == NULL || begin->type != TOKEN_LIST_END) {
        puts("SYNTAX ERROR ON PARSING");
        exit(0);
    }

    //printExprNode(node);
    //puts("\v");

    DOUBLET ans = expr_tree_calc(node);

    printf("%le\n", REINTERPRET_TO_DOUBLE(ans));

    freeExprTree(node);

    return 0;
}