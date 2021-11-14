#include <iostream>

extern "C"{
    #include "graph.h"
}

#include <queue>

using namespace std;

Graph spanning_tree(Graph graph){

    int source = 0;
    int length = graph->n;
    int visited[length];

    queue<int> Q;
    Q.push(source);
    visited[source] = 1;

    while(!Q.empty()){
        int v = Q.front();
        Q.pop();
        int length_nb = graph->alist[v]->d;
        for (int i=0; length_nb; i++){
            int* neighbours = graph->alist[v]->list_vertices;
            for(int j=0; j < length_nb; j++){

                if (visited[neighbours[j]] != 1){
                    Q.push(neighbours[j]);
                    visited[neighbours[j]] =1;
                }



            }
        }

    }




}




