#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sixth.h"

/* 
 * abort the program if nonrecoverable error (e.g. CLI format error) 
 */
void print_err(const char *err)
{
    fprintf(stderr, "%s\n", err);
    exit(1);
}


#define MAX_LINE    100

int main(int argc, char *argv[])
{

    char buf[MAX_LINE];

    /* **** PART 0 ---- prepare input files ********** */
    // check CLI
    if (argc != 3) 
        print_err("Usage: ./sixth <graph> <queries>");

    // file with graph
    FILE *g_file;
    g_file = fopen(argv[1], "r");
    if (g_file==NULL)
        print_err("Cannot open graph file");

    // file with queries
    FILE *q_file;
    q_file = fopen(argv[2], "r");
    if (q_file == NULL) {
        fclose(g_file);
        print_err("Cannot open query file");
    }


    /* ******** PART I -- build the graph *********** */
    
    // read graph vertix count
    int N_vertex;
    fscanf(g_file, "%d\n", &N_vertex);

    // build a graph on them
    graph *G = make_graph(N_vertex);
    if (G == NULL)
        print_err("Cannot build graph");

    // read all vertices
    for (int i = 0; i < N_vertex; i++) {
        fgets(buf, sizeof buf, g_file);
        buf[strlen(buf)-1]='\0';
        if (insert_vertex(G, buf) != 0) {
            fprintf(stderr, "Cannot insert vertex %s\n", buf);
            exit(1);
        }
    }
    
    // sort graph    
    sort_graph(G);

    // now read edges
    while (fgets(buf, sizeof buf, g_file) != NULL) {
        char from[30], to[30];
        int weight;
        sscanf(buf, "%s %s %d\n", from, to, &weight);

        // insert first edge
        if (insert_edge(G, from, to, weight) == -1) {
            fprintf(stderr, "%s %s: ", from, to);
            print_err("problem inserting edge");
        }
    }

    // file not needed
    fclose(g_file);

    /* ------- PART II -- make queries to this graph ---------- */

    while (fgets(buf, sizeof buf, q_file) != NULL) {
        buf[strlen(buf)-1]='\0';
        print_dijkstra(G, buf);
    }
    fclose(q_file);

    // and destroy it
    destroy_graph(G);
    exit(0);
}
