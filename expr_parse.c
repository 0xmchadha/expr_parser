#include<stdio.h>
#include<stdbool.h>

/*
 * Expr -> Term AOP Term | Term
 *
 * Term -> Term MOP Term | Fact | (Expr)
 *
 * 2 + 3 * 4 + 8 * 10 - 10 * (4 + 4 * 4)
 *
 */

//Fact + Fact * Fact + Fact
#define EXPR "is an expr"
#define N_EXPR "is not an expr"

enum symbols {
        factor,
        add,
        mulp,
        END
};

struct expr
{
        enum symbols *arr;
        int num;
} expr1;

bool term(struct expr *e)
{
        int *i = &e->num;

        if (e->arr[*i] != factor) {
                printf("%s %d %d\n", __func__, __LINE__, e->num);
                return false;
        }

        if (e->arr[(*i) + 1] == mulp) {
                (*i) += 2;
                if (e->arr[*i] == factor) {
                        printf("%s %d %d\n", __func__, __LINE__, e->num);
                }
        }

        (*i)++;
        printf("%s %d %d\n", __func__, __LINE__, e->num);
        return true;
}

bool expr(struct expr *e)
{
        int *i = &e->num;

        while (e->arr[*i] != END) {
                printf("expr: %d %d\n", *i, e->arr[*i]);
                if (e->arr[*i] == factor) {
                        if (term(e) == true) {
                                if (e->arr[*i] == add) {
                                        printf("add\n");
                                        (*i)++;
                                        printf("%s %d %d\n", __func__, __LINE__, e->num);
                                        return true & expr(e);
                                } else if (e->arr[*i] != END) {
                                        printf("end\n");
                                        return false;
                                } else
                                        return true;
                        } else {printf("%s %d %d\n", __func__, __LINE__, e->num); return false;}
                }

                if (e->arr[*i] == add) {
                        printf("%s %d %d\n", __func__, __LINE__, e->num);
                        return false;
                }

                if (e->arr[*i] == mulp) {
                        printf("%s %d %d\n", __func__, __LINE__, e->num);
                        return false;
                }

                (*i)++;
        }

        return true;
}

int main()
{
        //   expr1.arr = factor;
        enum symbols expr_test[] = {factor, add, factor, mulp, factor, add, factor, mulp, factor, END};
        expr1.arr = expr_test;

        printf("%s\n", expr(&expr1) == true ? EXPR : N_EXPR);

}
