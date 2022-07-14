#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

stack *make_stack(int n_max)
{
    stack *s = malloc(sizeof (stack));
    if (s == NULL)
        return NULL;
    s->V = calloc(n_max, sizeof(char *));
    if (s->V == NULL) {
        free(s);
        return NULL;
    }
    s->n_max = n_max;
    s->top = -1;
    return s;
}

void destroy_stack(stack *s)
{
    free(s->V);
    free(s);
}

int is_stack_empty(stack *s)
{
    return s->top == -1;
}

void push_stack(stack *s, char *v)
{
    s->top++;
    s->V[s->top] = v;
}

char *pop_stack(stack *s)
{
    if (is_stack_empty(s))
        return NULL;
    char *v = s->V[s->top];
    s->top--;
    return v;
}

int contains_stack(stack *s, char *v)
{
    for (int i = 0; i <= s->top; i++) {
        if (strcmp(s->V[i],v)==0)
            return 1;
    }
    return 0;
}

void print_stack(stack *s)
{
    printf("stack: ");
    for (int i = 0; i <= s->top; i++)
        printf("%s ", s->V[i]);
    printf("\n");
}
