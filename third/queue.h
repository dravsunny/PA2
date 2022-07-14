#ifndef _QUEUE_H
#define _QUEUE_H

typedef struct {
    int n_max;
    char **V;    // V[n_max]
    int head;
    int tail;
} queue;

queue *make_queue(int n_max);
void destroy_queue(queue *);
int is_queue_empty(queue *);
char *get_queue(queue *q);
void put_queue(queue *q, char *v);
int contains_queue(queue *q, char *v);

#endif
