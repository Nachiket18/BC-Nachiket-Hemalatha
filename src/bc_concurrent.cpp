#include <iostream>      
#include <atomic>         
#include <thread>         
#include <vector>


struct node {
  int vertex;
  struct node* next;
};
struct node* createNode(int);

struct Graph {
  int numVertices;
  struct node** adjLists;
};

// Create a node
struct node* createNode(int v) {
  struct node* newNode = malloc(sizeof(struct node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}

// Create a graph
struct Graph* createAGraph(int vertices) {
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->numVertices = vertices;

  graph->adjLists = malloc(vertices * sizeof(struct node*));

  int i;
  for (i = 0; i < vertices; i++)
    graph->adjLists[i] = NULL;

  return graph;
}

// Add edge
void addEdge(struct Graph* graph, int s, int d) {
  // Add edge from s to d
  struct node* newNode = createNode(d);
  newNode->next = graph->adjLists[s];
  graph->adjLists[s] = newNode;

  // Add edge from d to s
  newNode = createNode(s);
  newNode->next = graph->adjLists[d];
  graph->adjLists[d] = newNode;
}
// Code to calculate the value of number of shortest path containing v divided by number of shortest path for given set of vertices


int calculate_sigma_shortest_path_ratio(Graph * graph,int s,int t,int v)
{

}


// Concurrent code to calculate betweeness_centrality

int betweeness_centrality(Graph* graph,int v)
{
	
	std::vector<std::thread> threads;
	j = 0
	for (i = 0; i < graph->numVertices; i++) {
 	   struct node* temp = graph->adjLists[i];
    	   printf("\n Vertex %d\n: ", i);
    	   
    	   while(temp)
    	   {
 		s = i;
 		t = temp -> vertex;   	   
    	   	j++;
    	   	threads.push_back(std::thread(calculate_sigma_betweeness_ratio,&graph,s,t,v));
    	   }
    	   
  }
  
  for (auto &th : threads) {
    th.join();
  }
  
  

}
