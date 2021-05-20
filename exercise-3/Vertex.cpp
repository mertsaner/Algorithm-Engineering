#include "Vertex.h"
#include <vector>
#include <string>

using namespace std;


Vertex::Vertex() {
	return;
}

Vertex::Vertex(int vertex_number) {
	this->vertex_number = vertex_number;
	return;
}

string Vertex::to_string() {
	return "V" + std::to_string(this->vertex_number);
}