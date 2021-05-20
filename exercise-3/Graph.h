#ifndef Graph_h
#define Graph_h 1


#include <vector>
#include "Edge.h"
#include "Vertex.h"


class Graph{
	public:
		Graph();
		Graph(int n,vector<vector<int>> list_of_edges);
		vector<Vertex> vertices; 
		vector<Edge> edges;

	private: 


};

#endif