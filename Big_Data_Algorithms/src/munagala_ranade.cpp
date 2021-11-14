
#include <iostream>
extern "C"
{
    #include "graph.h"
}




#include <cstring>
#include <queue>
#include <vector>
#include <list>
#include <set>

using namespace std;


void print_l_data_structure(vector<int>* L,int n){

    for(int i=0;i<n;i++){
        printf("%d",L[i]);
    }

}


void munagala_ranade_BFS(Graph g){

    std::vector<vector<int>> Front_data_structure;
    int L[g->n];
    std::list<int> U;

    struct graph *buffer_graph = (struct graph*)malloc (sizeof (struct graph));

    memcpy(&buffer_graph,&g,sizeof(g));



    for (int i = 0; i < g->n; i++){

        L[i] = 0;
        U.push_back(i);
    }

    //cout << "Start";

    int t = 0;

    vector<int> t_tmp;
    Front_data_structure.push_back(t_tmp);

    //cout << Front_data_structure[t-1].size() << "\n";
    //cout << U.size() << "\n";

    //cout << "Start";



    while (U.size() != 0){
            //cout << "In Loop";
            if (Front_data_structure[t-1].size() == 0 || t-1 < 0){

                vector<int> t_tmp;
                t_tmp.push_back(U.front());
                Front_data_structure.insert(Front_data_structure.begin() + t,t_tmp);
                //cout << "In the first If" << U.front();
            }
            else{
                vector<int> tmp = Front_data_structure[t-1];
                std::set<int> Nbr_t;
                for(int i=0; i < (int)(tmp.size()); i++){
                    int* tmp_adj = buffer_graph ->alist[tmp[i]]->list_vertices;
                    for (int j=0; j < buffer_graph ->alist[tmp[i]]->d; j++){
                        Nbr_t.insert(tmp_adj[j]);
                    }
                }
                //cout << "Passed the first check" << Nbr_t.size() ;
                vector<int> t_tmp;
                for (int i=0; i < (int)(Nbr_t.size());i++ ){

                    int result = 0;
                    auto it_nbr = Nbr_t.begin();

                    std::advance(it_nbr, i);

                    //cout << "Passed the second check";

                    int x = *it_nbr;
                    vector<int> tMinus_tmp;
                    tMinus_tmp = Front_data_structure[t-1];

                    //std::set<int>::iterator it_tminus = tMinus_tmp.begin();

                    for (auto it_tminus = std::begin(tMinus_tmp); it_tminus !=std::end(tMinus_tmp); ++it_tminus){
                        if (x == *it_tminus){
                            result = 1;
                        }
                    }

                    if (t-2 >= 0){
                        vector<int> tMinusTwo_tmp;
                        tMinusTwo_tmp = Front_data_structure[t-2];
                        //std::set<int>::iterator it_tminus_two = tMinus_tmp.begin();

                        for (auto it_tminus_two = std::begin(tMinusTwo_tmp); it_tminus_two !=std::end(tMinusTwo_tmp); ++it_tminus_two){
                            if (x == *it_tminus_two){
                            result = 1;
                            }
                        }
                    }
                    //cout << "Passed the Second check" << "\n";

                   // cout << "result:" << result <<"\n";
                   // cout <<"x"<<x << "\n";
                    if (result == 0){
                        t_tmp.push_back(x);


                    }
                }
                Front_data_structure.insert(Front_data_structure.begin() + t,t_tmp);
                //cout << "Passed the Third check" << "\n";

            }

            vector<int> tmp_t = Front_data_structure[t];
            //cout <<"Size" << tmp_t.size() << "\n";

            for (int j=0; j < (int)(tmp_t.size());j++){


            //    cout <<"U Front" << U.front() << "\n";
            //    cout << "V" << tmp_t[j] << "\n";
            //    cout << "L list data" << "\t";

                //cout << "Index" << (L.begin() + tmp_t[j] ) << "\n";
                L[tmp_t[j]] = U.front();
                //cout << "L(V)" << L[tmp_t[j]]<< "\n";
                U.remove(tmp_t[j]);
                /*
                for(int i=0; i< buffer_graph ->n; i++){
                    cout << L[i] << "\t";
                }
                cout << "\n";
                */
            }

            t = t+1;

    }

    for(int i=0; i< buffer_graph ->n; i++){
        printf("%d",L[i]);
    }

}




int main()
{
    Graph g;
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


    //printf("%d",graph_edge_count(g));

    munagala_ranade_BFS(g);


    return 1;
}


