#include "Graph.h"
#include <vector>

using namespace std;

Graph::Graph() {
	return;
}

Graph::Graph(int n,vector<vector<int>> list_of_edges) {
	return;
}

void Graph::add_vertex(int vertex_number) {
	Vertex new_vertex(vertex_number);
	(this->vertices).push_back(new_vertex);
	return;
}

void Graph::add_vertex(Vertex new_vertex) {
	(this->vertices).push_back(new_vertex);
	return;
}

string Graph::to_string() {
	string result = "";
	for (uint i = 0; i < this->vertices.size(); i++) {
		result += this->vertices.at(i).to_string();
		if (i < this->vertices.size() -1) {
			result += " ";
		}
	}
	return result;
}

int Graph::get_next_vertex_number() {
	return (this->vertices).size() + 1;
}