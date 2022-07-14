#ifndef _FOURTH_H
#define _FOURTH_H

typedef struct node {
    char *v;
    int weight;    // used only for nodes representing edges
    struct node *next;
} node;

typedef struct {
    node *V;
    int N_vertex;
} graph;

// building the graph
node *make_node(char *v, node *next);
graph *make_graph(int N_vertex);
int insert_vertex(graph *g, char *v);
int insert_edge(graph *g, char *from, char *to, int weight);
void sort_graph(graph *g);

// clearing memory
void destroy_graph(graph *g);

// debug
void print_graph(graph *g);

// obtaining any vertex
node *get_vertex(graph *g, char *v);

/* part 2 -- DFS */
void print_dfs(graph *g, char *v);

#endif
