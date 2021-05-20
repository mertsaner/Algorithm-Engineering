#ifndef Edge_h
#define Edge_h 1

#include "Vertex.h"
#include <vector>


class Vertex;

class Edge{
	public:
		Edge();
		Edge(int vertex1, int vertex2, int weight);
		int weight; 
		bool set;
		bool forbidden;
		Vertex vertex_1;
		Vertex vertex_2; 




	private: 
};

#endif