#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "sixth.h"

/*
 * create array-based priority queue based on the graph
 */
pri_queue *make_queue(graph *g)
{
    // allocate queue itself
    pri_queue *q = malloc(sizeof(pri_queue));
    if (q == NULL)
        return NULL;

    // allocate array for vertices (maximum size is the count of vert.)
    q->N_vertex = g->N_vertex;
    q->V = malloc(sizeof(record) * q->N_vertex);
    if (q->V == NULL) {
        free(q);
        return NULL;
    }

    // initially previous are undefined, and distances from source are infinity    
    for (int i = 0; i < q->N_vertex; i++) {
        q->V[i].cur_v = g->V[i].v;    // copy by reference
        q->V[i].prev_v = NULL;
        q->V[i].source_dist = INF;
        q->V[i].visited = 0;
    }

    return q;
}

void destroy_queue(pri_queue *q)
{
    free(q->V);
    free(q);
}

void print_queue(pri_queue *q)
{
    for (int i = 0; i < q->N_vertex; i++) {
        printf("%s ", q->V[i].cur_v);
        if (q->V[i].source_dist == INF)
            printf("INF\n");
        else
            printf("%d\n", q->V[i].source_dist);
    }
    printf("\n");
}

record *get_queue(pri_queue *q, char *cur_v)
{
    for (int i = 0; i < q->N_vertex; i++) {
        if (strcmp(q->V[i].cur_v, cur_v)==0) {
            return &q->V[i];
        }
    }
    return NULL;
}

void set_queue(pri_queue *q, char *cur_v, char *prev_v, int dist, int visited)
{
    record *rec = get_queue(q, cur_v);
    rec->prev_v = prev_v;
    rec->source_dist = dist;
    rec->visited = visited;
}

/*
 * find the vertex with the smallest dist, which is NOT visited yet
 */
record *get_closest(pri_queue *q)
{
    record *closest = NULL;
    for (int i = 0; i < q->N_vertex; i++) {
        if (q->V[i].visited==0 && 
            (closest==NULL || closest->source_dist==INF || 
                ((q->V[i].source_dist != INF) && q->V[i].source_dist < closest->source_dist))) {
            closest = &q->V[i];
         }
    }
    return closest;
}
