#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fourth.h"    // graph definitions
#include "stack.h"     // for DFS

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

/* ------ PART II --- BFS -------- */

static int contains(char **arr, int n, char *v)
{
    for (int i = 0; i < n; i++)
        if (strcmp(arr[i], v)==0)
            return 1;
    return 0;
}

void print_dfs(graph *g, char *v)
{
    // check if there is such
    node *start = get_vertex(g, v);
    if (start == NULL) {
        fprintf(stderr, "no node %s\n", v);
        return;
    }

    // keep visited nodes here
    char **visited = calloc(g->N_vertex, sizeof(char*));
    if (visited==NULL) {
        fprintf(stderr, "fail allocate visited\n");
        return;
    }
    int nvisited = 0;    // empty yet

    // keep stack of nodes here
    stack *s = make_stack(g->N_vertex);
    if (s == NULL) {
        fprintf(stderr, "failed creating stack\n");
        return;
    }

    //  ------ BFS algorithm itself -----------
    node *cur = start;
    int found;        // marker that we found next
    do {
        // 1) print current 
        // and
        // 2) mark it visited
        // if not visited
        if (!contains(visited, nvisited, cur->v)) {
            printf("%s ", cur->v);
            visited[nvisited++] = cur->v;
        }

        // 3) put it into stack
        push_stack(s, cur->v);

        found = 0;
        // 4) loop through children, find first not visited
        for (node *child = cur->next; child != NULL; child = child->next) {
            if (!contains(visited, nvisited, child->v)) {
                cur = get_vertex(g, child->v);
                found = 1;
                break;
            }
        }

        // 5) not found further -- take this one from stack
        if (found == 0) {
            pop_stack(s);
            // 6) if possible -- step backwards
            if (!is_stack_empty(s)) {
                char *v = pop_stack(s);
                cur = get_vertex(g, v);
                found = 1;
            } else {
             // 7) no -- then graph can be disconnected, take first unvisited
                for (int i = 0; i < g->N_vertex; i++) {
                    if (!contains(visited, nvisited, g->V[i].v)) {
                        cur = &g->V[i];
                        found = 1;
                        break;
                    }
                }
            }
        }

        // if found still 0 -- nothing left
    } while (found);
    printf("\n");

    free(visited);
    destroy_stack(s);
}

