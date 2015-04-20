#include<stdio.h>
#include<stdbool.h>

/*
 * Expr -> Expr AOP Expr | Term
 *
 * Term -> Term MOP Term | Factor | (Expr)
 *
 * AOP -> + | -
 * MOP -> * | /
 * Factor -> 0-9
 */

/*
 * 2 + 3 * 4 + 8 * 10 - 10 * (4 + 4 * 4)
 *
 */
//Fact + Fact * Fact + Fact


#define EXPR "is an expr"
#define N_EXPR "is not an expr"

struct expr
{
        enum symbols *arr;
        int num;
} expr1;

bool Mop(struct expr *);
bool Aop(struct expr *);
bool Term(struct expr *);
bool Expr(struct expr *);

#define NEXT(e) do {++e->num;}while(0)
#define CUR(e) e->arr[e->num]

enum symbols {
        factor,
        add,
        sub,
        mulp,
        div,
        openb,
        closeb,
        END
};

bool Aop(struct expr *e)
{
        enum symbols sym = CUR(e);

        if (sym == add || sym == sub) {
                NEXT(e);
                return true;
        }

        return false;
}

bool Mop(struct expr *e)
{
        enum symbols sym = CUR(e);

        if (sym == mulp || sym == div) {
                NEXT(e);
                return true;
        }

        return false;
}

bool Term(struct expr *e)
{
        enum symbols sym = CUR(e);

        if (sym == factor) {
                NEXT(e);

                if (Mop(e) == true) {
                        return Term(e);
                }

                return true;
        }

        if (sym == openb) {
                NEXT(e);

                if (Expr(e) == true) {
                        if (CUR(e) == closeb) {
                                NEXT(e);
                                return true;
                        }
                }
        }

        return false;
}

bool Expr(struct expr *e)
{
        if (Term(e) == true) {
                if (Aop(e) == true) {
                                return Expr(e);
                } else return true;
        }

        if (CUR(e) == END)
                return true;

        return false;
}

int main()
{
        //   expr1.arr = factor;
        //enum symbols expr_test[] = {factor, add, openb, factor, mulp, factor, closeb, add, factor, mulp, factor, END};
        //enum symbols expr_test[] = {factor, add, factor, mulp, factor, add, factor, mulp, factor, END};

        enum symbols expr_test[] = {openb, factor, add, factor, closeb, closeb, END};

        expr1.arr = expr_test;

        printf("%s\n", Expr(&expr1) == true ? EXPR : N_EXPR);
}
