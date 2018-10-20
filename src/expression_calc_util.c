#include "expression_calc_util.h"

double expr_oper_add(double l, double r)
{
    return l + r;
}

double expr_oper_sub(double l, double r)
{
    return l - r;
}

double expr_oper_mul(double l, double r)
{
    return l * r;
}

double expr_oper_div(double l, double r)
{
    return l / r;
}

double expr_oper_neg(double l)
{
    return -l;
}

double expr_tree_calc(expr_node_t* node)
{
    double ret;
    switch (node->type) {
    case EXPR_IMME:
        ret = node->data;
        break;
    case EXPR_ADD:
        ret = expr_oper_add(expr_tree_calc(node->node1), expr_tree_calc(node->node2));
        break;
    case EXPR_SUB:
        ret = expr_oper_sub(expr_tree_calc(node->node1), expr_tree_calc(node->node2));
        break;
    case EXPR_MUL:
        ret = expr_oper_mul(expr_tree_calc(node->node1), expr_tree_calc(node->node2));
        break;
    case EXPR_DIV:
        ret = expr_oper_div(expr_tree_calc(node->node1), expr_tree_calc(node->node2));
        break;
    case EXPR_NEG:
        ret = expr_oper_neg(expr_tree_calc(node->node1));
        break;
    default:
        ret = expr_oper_div(0, 0);
        break;
    }

    return ret;
}