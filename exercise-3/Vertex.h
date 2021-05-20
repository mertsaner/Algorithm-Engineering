#ifndef Vertex_h
#define Vertex_h 1

#include <vector>
#include <string>

using namespace std;

class Vertex {
	public:
		Vertex();
		Vertex(int vertex_number);

		string to_string();

		int vertex_number; 


	private: 

};

#endif