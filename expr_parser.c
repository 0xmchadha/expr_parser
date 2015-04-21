#include<stdio.h>
#include<stdbool.h>

//(((f) * f))

/*
 * Grammar for Expressions:
 *
 * Expr -> Expr AOP Expr | Term
 *
 * Term -> Term MOP Term | Factor | (Expr)
 *
 * AOP -> + | -
 *
 * MOP -> * | /
 *
 * Factor -> 0-9
 */

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

                                if (Mop(e) == true) {
                                        return Term(e);
                                }
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
                }

                return true;
        }

        if (CUR(e) == END)
                return true;

        return false;
}

bool parse(struct expr *e)
{
        bool ret = Expr(e);

        if (e->arr[e->num] != END)
                return false;

        return ret;
}

int main()
{
        enum symbols expr_test[] = {openb, openb, openb, factor, closeb, mulp, factor, closeb, closeb, END};
        expr1.arr = expr_test;

        printf("%s\n", parse(&expr1) == true ? EXPR : N_EXPR);
}

//(((f*f-f/f) * f))
//(((f) * f))
//(((f)*f))
