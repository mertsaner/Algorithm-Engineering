#include <string>
#include <vector>
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"



using namespace std;

Graph parse_input();

int parse_input_vertex_count(string input_line);

vector<int> parse_input_adjacents(string input_line);

bool cluster_detection(Graph graph);

tuple<vector<Edge>,int> recursion_main(Graph graph);

tuple<vector<Edge>,bool> recursion(Graph graph,int k);