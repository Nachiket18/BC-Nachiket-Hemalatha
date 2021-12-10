/* basic directed graph type */
/* the implementation uses adjacency lists
 * represented as variable-length arrays */

/* these arrays may or may not be sorted: if one gets long enough
 * and you call graph_has_edge on its source, it will be */


struct graph {
    int n;              /* number of vertices */
    int m;              /* number of edges */
    struct successors {
        int d;          /* number of successors */
        int len;        /* number of slots in array */
        char is_sorted; /* true if list_vertices is already sorted */
        int list_vertices[1];    /* actual list_vertices of successors */
    } *alist[1];
};


/* basic directed graph type */

typedef struct graph *Graph;


/* create a new graph with n vertices labeled 0..n-1 and no edges */
Graph graph_create(int n);

/* free all space used by graph */
void graph_destroy(Graph);

/* add an edge to an existing graph */
/* doing this more than once may have unpredictable results */
void graph_add_edge(Graph, int source, int sink);

void remove_last_edge(Graph g,int u );

/* return the number of vertices/edges in the graph */
int graph_vertex_count(Graph);
int graph_edge_count(Graph);

/* return the out-degree of a vertex */
int graph_out_degree(Graph, int source);

/* return 1 if edge (source, sink) exists), 0 otherwise */
int graph_has_edge(Graph, int source, int sink);

/* invoke f on all edges (u,v) with source u */
/* supplying data as final parameter to f */
/* no particular order is guaranteed */
void graph_foreach(Graph g, int source,
        void (*f)(Graph g, int source, int sink, void *data),
        void *data);


