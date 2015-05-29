#include<stdio.h>

char buf[3000];
char address_space[30000];
char *ptr;
int state;
int skip;
int exec = 1;

#define OP(op) if (exec == 1) {         \
        op;                             \
    }                                   \

void func()
{
    int ret;

    while ((ret = getc(stdin)) != EOF && feof(stdin) == 0) {
        char val = ret;

        switch (val) {
            case '>':
                OP(ptr++);
                break;
            case '<':
                OP(ptr--);
                break;
            case '+':
                OP(++(*ptr));
                break;
            case '-':
                OP(--(*ptr));
                break;
            case '.':
                OP(putchar(*ptr));
                break;
            case ',':
                OP(*ptr = getc(stdin));
                break;
            case '[':
                if (exec == 1) {
                    for (;;) {
                        if (*ptr == 0) {
                            exec = 0;
                            skip++;
                            break;
                        } else {
                            state++;
                            func();
                            state--;
                        }
                    }
                } else
                    skip++;
                break;
            case ']':
                if (exec == 1) {
                    ungetc(val, stdin);
                    return;
                } else {
                    skip--;
                    if (skip == 0)
                        exec = 1;
                }
        }

        if (state) {
            func();
            ungetc(val, stdin);
            return;
        }
    }
}

int main()
{
    setbuf(stdin, buf);
    ptr = address_space;
    func();
}
