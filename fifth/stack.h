#ifndef _STACK_H
#define _STACK_H

typedef struct {
    int n_max;
    char **V;    // char*[n_max]
    int top;
} stack;

stack *make_stack(int n_max);
void destroy_stack(stack *s);
int is_stack_empty(stack *s);
void push_stack(stack *s, char *v);
char *pop_stack(stack *s);
int contains_stack(stack *s, char *v);
void print_stack(stack *s);

#endif
