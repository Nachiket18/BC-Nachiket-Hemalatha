
#include <iostream>
extern "C"
{
    #include "graph.h"
}

#include "munagala_ranade.h"
#include "graph_util.h"
#include <cstring>
#include <queue>
#include <vector>
#include <list>
#include <set>
#include <bits/stdc++.h>
#include <iterator>

using namespace std;


void print_l_data_structure(vector<int>* L,int n){

    for(int i=0;i<n;i++){
        printf("%d",L[i]);
    }

}


std::vector< std::vector<int> > munagala_ranade_BFS(Graph g,int source){

    int L[g->n];
    std::list<int> U;
    std::vector< std::vector<int> > Front_data_structure;

    struct graph *buffer_graph = (struct graph*)malloc (sizeof (struct graph));

    memcpy(&buffer_graph,&g,sizeof(g));

    U.push_back(source);

    for (int i = 0; i < g->n; i++){
        L[i] = 0;
        U.push_back(i);
    }

    //cout << "Start";

    int t = 0;
    int I_O = 0;

    vector<int> t_tmp;
    Front_data_structure.push_back(t_tmp);


    while (U.size() != 0 || Front_data_structure[t-1].size() != 0 ){
            //cout << "In Loop";
            if (Front_data_structure[t-1].size() == 0 || t-1 < 0){

                vector<int> t_tmp;
                t_tmp.push_back(source);
                Front_data_structure.insert(Front_data_structure.begin() + t,t_tmp);
                //cout << "In the first If" << U.front();
            }
            else{
                vector<int> tmp = Front_data_structure[t-1];
                std::set<int> Nbr_t;
                //cout << "Tmp-size:" <<tmp.size() << "\n";
                for(int i=0; i < (int)(tmp.size()); i++){

                    int* tmp_adj = buffer_graph ->alist[tmp[i]]->list_vertices;
                    for (int j=0; j < buffer_graph ->alist[tmp[i]]->d; j++){
                        I_O = I_O + 1;
                        Nbr_t.insert(tmp_adj[j]);
                    }
                }

                vector<int> t_tmp;
                //I_O = I_O + Nbr_t.size();
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

    //cout << "I/O:" << I_O;
    //cout << "t:" << t;
    return Front_data_structure;
}


std::vector< std::vector<int> > munagala_ranade_BFS_ramachandran(Graph g,int source,int d_u_v,std::vector< vector<int>> A){

    int L[g->n];
    std::list<int> U;
    std::vector< std::vector<int> > Front_data_structure;

    struct graph *buffer_graph = (struct graph*)malloc (sizeof (struct graph));

    memcpy(&buffer_graph,&g,sizeof(g));

    //U.push_back(source);

    for (int i = 0; i < g->n; i++){
        L[i] = 0;
        U.push_back(i);

    }

    int t = 0;

    vector<int> t_tmp;
    Front_data_structure.push_back(t_tmp);


    while (U.size() != 0){

            if (Front_data_structure[t-1].size() == 0 || t-1 < 0){

                vector<int> t_tmp;
                t_tmp.push_back(source);

                Front_data_structure.insert(Front_data_structure.begin() + t,t_tmp);
                cout << "t:" << t << "\n";

                for(int j=0; j < t_tmp.size(); j++){
                    cout << t_tmp[j] << "\t";
                }

            }
            else{
                //cout << "t" << t << "\n";

                vector<int> tmp = Front_data_structure[t-1];
                std::set<int> Nbr_t;
                for(int i=0; i < (int)(tmp.size()); i++){
                    cout << "tmp" << tmp[i] << "\n";
                    for(int k = std::max(0,(t-1 - d_u_v)); k <= std::min(((g->n)-1),(t-1 + d_u_v)); k++){
                                //cout << "A:"  << A[k]   << "\n";
                                //cout << "t:"  << t      << "\n";
                        vector<int> tmp_a = A[k];
                        for(int m=0; m < (int)(tmp_a.size()); m++){
                            if (tmp[i] == tmp_a[m]){
                                int* tmp_adj = buffer_graph ->alist[tmp[i]]->list_vertices;
                                for (int j=0; j < buffer_graph ->alist[tmp[i]]->d; j++){
                                    cout << "nbr:" <<tmp_adj[j] <<"\t";
                                    Nbr_t.insert(tmp_adj[j]);
                                }
                            }
                        }
                    }
                }



                vector<int> t_tmp;
                for (int i=0; i < (int)(Nbr_t.size());i++ ){

                    int result = 0;

                    auto it_nbr = Nbr_t.begin();
                    std::advance(it_nbr, i);

                    int x = *it_nbr;
                    vector<int> tMinus_tmp;
                    tMinus_tmp = Front_data_structure[t-1];

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

                    if (result == 0){
                        t_tmp.push_back(x);
                    }
                }

                Front_data_structure.insert(Front_data_structure.begin() + t,t_tmp);

                cout << "t:" << t << "\n";
                cout << "front - data" << "\n";
                for(int j=0; j < t_tmp.size(); j++ ){
                    cout << t_tmp[j] << "\t";
                }
                cout << "\n";
            }


            vector<int> tmp_t = Front_data_structure[t];

            for (int j=0; j < (int)(tmp_t.size());j++){
                L[tmp_t[j]] = U.front();
                U.remove(tmp_t[j]);
            }

            cout << "U Size" << U.size() << "\n";

            t = t+1;
    }

    cout << "Code worked" << "\n";

    return Front_data_structure;
}


std::vector< std::vector<int> > munagala_ranade_BFS_modification(Graph g,int source){

    int L[g->n];
    std::list<int> U;
    std::vector< std::vector<int> > Front_data_structure;

    struct graph *buffer_graph = (struct graph*)malloc (sizeof (struct graph));

    memcpy(&buffer_graph,&g,sizeof(g));

    U.push_back(source);

    for (int i = 0; i < g->n; i++){
        L[i] = 0;
        U.push_back(i);
    }

    //cout << "Start";

    int t = 0;

    vector<int> t_tmp;
    Front_data_structure.push_back(t_tmp);
    int I_O_Op = 0;

    while (U.size() != 0 || Front_data_structure[t-1].size() != 0 ){
            //cout << "In Loop";
            if (Front_data_structure[t-1].size() == 0 || t-1 < 0){

                vector<int> t_tmp;
                t_tmp.push_back(source);
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

                vector<int> t_tmp;
                for (int i=0; i < (int)(Nbr_t.size());i++ ){

                    int result = 1;
                    auto it_nbr = Nbr_t.begin();

                    std::advance(it_nbr, i);

                    //cout << "Passed the second check";

                    int x = *it_nbr;

                    for (auto it_u = std::begin(U); it_u !=std::end(U); ++it_u){
                        if (x == *it_u){
                            result = 0;
                        }
                    }

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


    return Front_data_structure;
}



/*



int main()
{
    std::set<std::pair<int, int>> test_graph;
    std::set<std::pair<int, int>>::iterator it;

    Graph g;

    g = graph_create(10);
    /*
    test_graph = generate_graph();

    cout << "Size:" << test_graph.size() << "\n";

    for (it=test_graph.begin(); it!=test_graph.end(); ++it){
        printf("%d %d\n", it->first, it->second);
        if (it->first != it->second){
            graph_add_edge(g,it->first,it->second);
        }

    }

    std::vector<std::vector<int>> output_MR;
    output_MR = munagala_ranade_BFS(g,0);

    */

    /*



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

    std::vector<std::vector<int>> output_MR_Mod;
    output_MR_Mod = munagala_ranade_BFS_modification(g,0);

    cout << "MR - BFS - Modified" <<"\n";

    for(int i=0; i < g->n; i++){

            vector<int> tmp = output_MR_Mod[i];
            if (tmp.size() == 0){
                break;
            }
            cout << "t:"<<i <<"\t" ;
            for(int j=0; j < tmp.size(); j++ ){
                cout << tmp[j] << "\t";
            }
            cout << "\n";

        }

    cout << "MR - BFS" <<"\n";
    std::vector<std::vector<int>> output_MR;
    output_MR = munagala_ranade_BFS(g,0);

    for(int i=0; i < g->n; i++){

            vector<int> tmp = output_MR[i];
            if (tmp.size() == 0){
                break;
            }
            cout << "t:"<<i<<"\t" ;
            for(int j=0; j < tmp.size(); j++ ){
                cout << tmp[j] << "\t";
            }
            cout << "\n";

        }


    //printf("%d",graph_edge_count(g));




    return 1;
}



*/
