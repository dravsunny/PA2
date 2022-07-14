#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "first.h"

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
        print_err("Usage: ./first <graph> <queries>");

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
        buf[strlen(buf)-1]='\0';
        // buf[] contains 3 elements "<from> <to>"
        int i;
        for (i = 0; buf[i] != ' '; i++)    // find the border
            ;
        buf[i]='\0';    // divide into 2 parts

        // insert first edge
        if (insert_edge(G, buf, &buf[i+1]) == -1) {
            fprintf(stderr, "%s %s: ", buf, &buf[i+1]);
            print_err("problem inserting edge");
        }
        // also insert the reverse edge immediately, as this is undirected
        if (insert_edge(G, &buf[i+1], buf) == -1) {
            fprintf(stderr, "%s %s: ", &buf[i+1], buf);
            print_err("problem inserting edge");
        }
    }

    // file not needed
    fclose(g_file);

    /* ------- PART II -- make queries to this graph ---------- */

    while (fgets(buf, sizeof buf, q_file) != NULL) {
        buf[strlen(buf)-1]='\0';
        if (buf[0] == 'd') {        // command "d <vertex>"
            int d = get_degree(G, buf+2);
            if (d == -1)
                printf("No such vertex\n");
            else 
                printf("%d\n", d);
        } else if (buf[0] == 'a') {    // command "a <vertex>"
            print_adjacent(G, buf+2);
        }
    }
    fclose(q_file);

    // and destroy it
    destroy_graph(G);
    exit(0);
}
