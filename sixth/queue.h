#ifndef _QUEUE_H
#define _QUEUE_H

#include "sixth.h"

#define INF (-1)

typedef struct record {
    char *cur_v;
    char *prev_v;
    int source_dist;
    int visited;
} record;

typedef struct {
    record *V;
    int N_vertex;
} pri_queue;

pri_queue *make_queue(graph *g);
void destroy_queue(pri_queue *q);
void print_queue(pri_queue *q);
record *get_queue(pri_queue *q, char *cur_v);
void set_queue(pri_queue *q, char *cur_v, char *prev_v, int dist, int visited);
record *get_closest(pri_queue *q);

#endif
