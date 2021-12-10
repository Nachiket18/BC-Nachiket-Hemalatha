#include <iostream>
extern "C"
{
    #include "graph.h"
}
#include "graph_util.h"
#include "munagala_ranade.h"

#include <cstring>
#include <queue>
#include <vector>
#include <list>
#include <set>
#include <stack>
#include <bits/stdc++.h>

using namespace std;

void print_graph(Graph g){

    int length = g->n;

    for (int i=0; i < length; i++){
        int length_nb = g -> alist[i]->d;
        int* neighbours = g ->alist[i]->list_vertices;

        for (int j=0; j < length_nb; j++ ){
            cout << i << "-->" << neighbours[j] << "\n";
        }

    }


}

std::vector< std::vector<int> > incremental_BFS(Graph g,int u,int v,std::vector < std::vector<int> > front_u){

        std::vector< std::vector<int> > A;

        int d_u_v = -1;



        for(int i=0; i < g ->n; i++){

            std::vector<int> tmp = front_u[i];

            if (tmp.size() == 0 ){
                break;
            }

            for(int j=0; j < tmp.size(); j++ ){

                if (tmp[j] == v){
                    d_u_v = i;
                }
            }

        }

        /*
        cout << "A:" << "\n";

        for(int j=0; j < A.size(); j++){
            cout << A[j] << "\t";
        }*/



        //cout << "D:U_V" << d_u_v;
        std::vector< std::vector<int> > front_v;

        front_v = munagala_ranade_BFS_ramachandran(g,v,d_u_v,front_u);

       for(int i=0; i < g->n; i++){

            vector<int> tmp = front_v[i];
            if (tmp.size() == 0){
                break;
            }

            for(int j=0; j < tmp.size(); j++ ){
                cout << tmp[j] << "\t";
            }
            cout << "\n";

        }

    return front_v;


}



int main()
{
    Graph g;

    vector<int> v_list;

    g = graph_create(6);

    graph_add_edge(g,0,1);
    graph_add_edge(g,1,0);

    graph_add_edge(g,1,2);
    graph_add_edge(g,2,1);

    graph_add_edge(g,0,3);
    graph_add_edge(g,3,0);

    graph_add_edge(g,2,4);
    graph_add_edge(g,4,2);

    graph_add_edge(g,3,4);
    graph_add_edge(g,4,3);

    graph_add_edge(g,4,5);
    graph_add_edge(g,5,4);

    Graph g_spanning_tree;
    std::vector< std::vector<int> > Front_output;
    g_spanning_tree = spanning_tree(g);
    v_list = euler_path(g_spanning_tree);

    for (auto it = v_list.begin(); it != v_list.end(); ++it){
        cout << ' ' << *it;
    }
    cout << "\n";

    Front_output = munagala_ranade_BFS(g,v_list[0]);



    //cout << "V_0" << v_list[0];
    //cout << "V_1" << v_list[1];
    std::vector< std::vector<std::vector<int>> > front_output_v;

    //Front_output = incremental_BFS(g,v_list[0],v_list[1],Front_output);
    //front_output_v = incremental_BFS(g,v_list[1],v_list[2],front_output_v);

    for (int i=1; i < g->n; i++){
        Front_output = incremental_BFS(g,v_list[i-1],v_list[i],Front_output);
        front_output_v.push_back(Front_output);
    }

    for(int i=0; i < front_output_v.size();i++){
        cout << "V:" << v_list[i+1] << "\n \n";
        std::vector< std::vector<int> > output_final = front_output_v[i];
        for(int j=0; j< g ->n; j++){
            vector<int> tmp = output_final[j];
            if (tmp.size() == 0){
                break;
            }

            cout << "t:"<< j << "\t";

            for(int k=0; k < tmp.size(); k++ ){
                cout << tmp[k] << "\t";
            }
        cout << "\n";
        }
        cout << "\n";
    }

    cout << "V:" << v_list[0] << "\n \n";

    for(int i=0; i < g ->n; i++){
        vector<int> tmp = Front_output[i];

        if (tmp.size() == 0){
                break;
        }
        cout << "t:"<< i << "\t";
        for(int j=0; j < tmp.size(); j++ ){
            cout << tmp[j] << "\t";
        }
     cout << "\n";
    }


    return 1;
}


