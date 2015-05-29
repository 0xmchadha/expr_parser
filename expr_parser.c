#include<stdio.h>
#include<stdbool.h>
#include<assert.h>

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
int factor_arr[1024];
int ptr;

#define EXPR "is an expr"
#define N_EXPR "is not an expr"

#define EMIT(e) fprintf(stdout, e"\n")

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

char str[] = {'(', ')', '+', '*'};
enum symbols str_sym[] = {openb, closeb, add, mulp};

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
        //EMIT("PSH %d", factor_arr[ptr++]);
        fprintf(stdout,"PSH %d\n", factor_arr[ptr++]);
        NEXT(e);

        if (Mop(e) == true) {
            bool ret = Term(e);
            //EMIT("MUL");
            fprintf(stdout, "MUL\n");
            return ret;
        }

        return true;
    }

    if (sym == openb) {
        NEXT(e);

        if (Expr(e) == true) {
            if (CUR(e) == closeb) {
                NEXT(e);

                if (Mop(e) == true) {
                    bool ret = Term(e);
                    //EMIT("MUL");
                    fprintf(stdout, "MUL\n");
                    return ret;
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
            bool ret = Expr(e);
            //EMIT("ADD\n");
            fprintf(stdout, "ADD\n");
            return ret;
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
    enum symbols expr_test[1024];
    //= {openb, openb, openb, factor, closeb, mulp, factor, closeb, closeb, END};
    unsigned char c;
    int i = 0;

    while ((c = getchar()) && !feof(stdin)) {
        int j;
        bool is_factor = false;

        /* This is LF character */
        if (c == '\n')
            continue;

        for (j = 0; j < strlen(str); j++) {
            if (c == str[j]) {
                expr_test[i++] = str_sym[j];

                break;
            }
        }

        if (j == strlen(str)) {
            expr_test[i++] = factor;
            factor_arr[ptr++] = atoi(&c);
            is_factor = true;
        }

        assert(j < strlen(str) || is_factor == true);
    }

    expr_test[i] = END;

    ptr = 0;
    expr1.arr = expr_test;

    printf("%s\n", parse(&expr1) == true ? EXPR : N_EXPR);
}

//(((f*f-f/f) * f))
//(((f) * f))
//(((f)*f))
