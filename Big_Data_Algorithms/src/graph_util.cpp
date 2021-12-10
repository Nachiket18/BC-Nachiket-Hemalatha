#include <iostream>

extern "C"{
    #include "graph.h"
}
#include "graph_util.h"
#include<bits/stdc++.h>
#include <queue>
#include <list>
#include <stack>
#include <set>
// Define the number of runs for the test data
// generated
#define RUN 5

// Define the maximum number of vertices of the graph
#define MAX_VERTICES 10

// Define the maximum number of edges
#define MAX_EDGES 45

using namespace std;


Graph spanning_tree(Graph graph){

    int source = 0;
    int length = graph->n;
    int visited[length];
    vector<int> spanning_tree;
    Graph g_spanning_tree;
    g_spanning_tree = graph_create(length);
    queue<int> Q;
    Q.push(source);
    visited[source] = 1;


    while(!Q.empty()){
        int v = Q.front();
        //cout << " V:" << v;
        Q.pop();
        int length_nb = graph->alist[v]->d;
        int* neighbours = graph->alist[v]->list_vertices;

        for (int i=0; i < length_nb; i++){
            //cout << "Neigbour" << neighbours[i];
            if (visited[neighbours[i]] != 1){
                    Q.push(neighbours[i]);
                    visited[neighbours[i]] = 1;
                    graph_add_edge(g_spanning_tree,v,neighbours[i]);
                    graph_add_edge(g_spanning_tree,neighbours[i],v);
            }
        }

    }

    return g_spanning_tree;


}

vector<int> euler_path(Graph g_tree){

    int odd_vertices_count = 0;
    int odd_vertex;

    stack<int> cpath;
    stack<int> epath;
    std::vector<int> output;

    for(int i=0; i < g_tree-> n; i++){

        int tmp = graph_out_degree(g_tree,i);

        if (tmp % 2 == 1){
            odd_vertices_count++;
            odd_vertex = i;
        }
    }
    cout << "odd vertices Count" << odd_vertices_count<< "\n";
    if (odd_vertices_count == 0 || odd_vertices_count == 2 ){


        if (odd_vertices_count == 0){
            cpath.push(0);
        }
        else{
            cpath.push(odd_vertex);
        }

        while(!cpath.empty()){

            int u = cpath.top();
            if (g_tree -> alist[u]->d == 0){
                cpath.pop();
                epath.push(u);
            }
            else{

                int length_nb = g_tree->alist[u]->d;
                int* neighbours = g_tree -> alist[u]-> list_vertices;
                cpath.push(neighbours[length_nb - 1]);
                remove_last_edge(g_tree,u);

            }

        }
    }

    for (int i=0; i<epath.size(); i++){
        output.push_back(epath.top());
        epath.pop();
    }

    return output;


}

set<pair<int, int>> generate_graph() {
    set<pair<int, int>> container;


    // Uncomment the below line to store
    // the test data in a file
    // freopen("Test_Cases_Undirected_Unweighted_Graph.in",
    //         "w", stdout);

    // For random values every time
    srand(time(NULL));

    int NUM;    // Number of Vertices
    int NUMEDGE; // Number of Edges

    for (int i=1; i<=RUN; i++)
    {
        NUM = MAX_VERTICES;

        // Define the maximum number of edges of the graph
        // Since the most dense graph can have N*(N-1)/2 edges
        // where N =  nnumber of vertices in the graph
        NUMEDGE =  MAX_EDGES;
        /*
        while (NUMEDGE > NUM*(NUM-1)/2)
            NUMEDGE = 1 + rand() % MAX_EDGES;
        */

        // First print the number of vertices and edges
        //printf("%d %d\n", NUM, NUMEDGE);

        // Then print the edges of the form (a b)
        // where 'a' is connected to 'b'
        for (int j=1; j<=NUMEDGE; j++)
        {
            int a,b;


            do
            {
                a = rand() % NUM;
            }
            while(a > NUM);


            do
            {
                b = rand() % NUM;
            }
            while(b > NUM);

            pair<int, int> p = make_pair(a, b);
            pair<int, int> reverse_p = make_pair(b, a);

            // Search for a random "new" edge everytime
            // Note - In a tree the edge (a, b) is same
            // as the edge (b, a)
            while (container.find(p) != container.end() ||
                    container.find(reverse_p) != container.end())
            {
                int a,b;

                do{
                    a = rand() % NUM;
                }
                while(a > NUM);

                do{
                    b = rand() % NUM;
                }
                while(b > NUM);


                p = make_pair(a, b);
                reverse_p = make_pair(b, a);
            }
            container.insert(p);
            container.insert(reverse_p);
        }

        if (container.size() > (MAX_EDGES * 0.75)){
            break;
        }

    }

    return container;

}




