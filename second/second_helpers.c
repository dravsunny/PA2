#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "second.h"    // graph definitions

// make one node in graph (in adjacency lists only, as array is allocated at once)
node *make_node(char *v, node *next)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
        return NULL;
    n->v = malloc(strlen(v)+1);
    if (n->v == NULL) {
        free(n);
        return NULL;
    }
    strcpy(n->v, v);
    n->next = next;
    n->weight = 0;
    return n;
}

// make a graph from a set of vertices
graph *make_graph(int N_vertex)
{
    // allocate memory for graph
    graph *g = malloc(sizeof (graph));
    if (g == NULL)    // no memory
        return NULL;

    // determine how many vertices and allocate them
    g->N_vertex = N_vertex;
    g->V = malloc(sizeof(node) * g->N_vertex);
    if (g->V == NULL) {    // no memory
        free(g);
        return NULL;
    }
    // no links and vertices for now (can be with calloc, but better directly)
    for (int i = 0; i < g->N_vertex; i++) {
        g->V[i].v = NULL;
        g->V[i].next = NULL;
        g->V[i].weight = -1;    // unused
    }

    return g;
}

int insert_vertex(graph *g, char *v)
{
    for (int i = 0; i < g->N_vertex; i++) {
        if (g->V[i].v == NULL) {    // empty place
            g->V[i].v = malloc(strlen(v)+1);
            if (g->V[i].v==NULL)
                return -1;
            strcpy(g->V[i].v, v);
            return 0;
        }
        // already here
        if (strcmp(g->V[i].v, v)==0)
            return 0;
    }
    return -1;    // some other error
}

// sort graph in lexic order
static int str_cmp(const void *p1, const void *p2)
{
    char *s1 = ((node *)p1)->v;
    char *s2 = ((node *)p2)->v;
    return strcmp(s1, s2);
}

void sort_graph(graph *g)
{
    qsort(g->V, g->N_vertex, sizeof(node),str_cmp);
}


// get a given vertex by its name
node *get_vertex(graph *g, char *v)
{
    for (int i = 0; i < g->N_vertex; i++) {
        if (strcmp(g->V[i].v, v)==0)
            return &g->V[i];
    }
    return NULL;    //not found
}

// insert edge into the graph, into sorted order,
// returns -1 if failed, 0 if success
int insert_edge(graph *g, char *from, char *to, int weight)
{
    node *base = get_vertex(g, from);
    if (base == NULL) {   // there is no such vertex!    
        return -1;
    }

    // start looping through neighbors, and input in sorted order
    node **cur = &(base->next);
    for (; *cur != NULL; cur = &((*cur)->next)) {
        int cmp = strcmp((*cur)->v, to);
        if (cmp == 0)    // already here
            return 0;
        if (cmp > 0) {    // must insert here
            break;
        }
    }

    // insert
    node *new = make_node(to, *cur);
    if (new == NULL) {   // memory 
         return -1;
    }
    new->weight = weight;
    *cur = new;
    return 0;
}

// destroy the graph
void destroy_graph(graph *g)
{
    for (int i = 0; i < g->N_vertex; i++) {
        node *cur = g->V[i].next;
        node *next;
        for (; cur != NULL; cur = next) {
            next = cur->next;
            free(cur->v);
            free(cur);
        }
        free(g->V[i].v);
    }
    free(g->V);
    free(g);
}

// printing: DEBUG
void print_graph(graph *g)
{
    for (int i = 0; i < g->N_vertex; i++) {
        // vertex itself
        printf("%s:", g->V[i].v);
        // nodes
        node *cur = g->V[i].next;
        while (cur != NULL) {
            printf(" %s(%d)", cur->v, cur->weight);
            cur = cur->next;
        }
        printf("\n");
    }
}

/* PART II -- two operations ----- */

// returns -1 if no such vertex
int get_out_degree(graph *g, char *v)
{
    node *base = get_vertex(g, v);
    if (base == NULL)
        return -1;
    int d = 0;
    for (node *cur = base->next; cur != NULL; cur = cur->next)
        d++;
    return d;
}

// returns -1 if no such vertex
int get_in_degree(graph *g, char *v)
{
    // here we have to find how many times v is found in adjacent lists of other vertices
    // (and possibly itself if we have a 1-vertex loop)
    int d = 0;
    for (int i = 0; i < g->N_vertex; i++) {
        for (node *cur = g->V[i].next; cur != NULL; cur = cur->next)
            if (strcmp(v, cur->v)==0)
                d++;
    }
    return d;
}

// return list of adjacent vertices to the given vertex
void print_adjacent(graph *g, char *v)
{
    node *base = get_vertex(g, v);
    if (base == NULL)
        printf("No such vertex\n");

    for (node *cur = base->next; cur != NULL; cur = cur->next) {
        printf("%s%s", cur->v, cur->next == NULL ? "" : " ");
    }
    printf("\n");
}
