/*
 * note: due to implementation this queue will always have a place for new element 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

queue *make_queue(int n_max)
{
    queue *q = malloc(sizeof (queue));
    if (q == NULL)
        return NULL;
    q->V = calloc(n_max, sizeof(char *));
    if (q->V == NULL) {
        free(q);
        return NULL;
    }
    q->head = q->tail = -1;
    return q;
}

// everything must be taken off by algorithm
void destroy_queue(queue *q)
{
     free(q->V);
    free(q);   
}

int is_queue_empty(queue *q)
{
    return q->head == -1 && q->tail == -1;
}

char *get_queue(queue *q)
{
    if (is_queue_empty(q))
        return NULL;
    char *v = q->V[q->head];
    q->head++;
    if (q->head > q->tail) { // became empty
        q->head = q->tail = -1;
    }
    return v;
}

void put_queue(queue *q, char *v)
{
    q->tail++;
    q->V[q->tail] = v;
    if (q->head == -1) { // were empty
        q->head = 0;
    }
}

int contains_queue(queue *q, char *v)
{
    if (is_queue_empty(q))
        return 0;
    for (int i = q->head; i <= q->tail; i++) {
        if (strcmp(q->V[i], v)==0)
            return 1;
    }
    return 0;
}
