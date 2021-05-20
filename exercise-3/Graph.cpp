#include "Graph.h"
#include <vector>
#include <iostream>

using namespace std;

Graph::Graph() {
	return;
}

Graph::Graph(int n,vector<vector<int>> list_of_edges) {
	this->build_adjacent_matrix(n, list_of_edges);
	return;
}

void Graph::build_adjacent_matrix(int vertex_count, vector<vector<int>> list_of_edges) {
	vector<vector<Edge>> adjacent_matrix;
	vector<Vertex> vertices;
	for (int i = 0; i < vertex_count; i++) {
		vector<Edge> row;
		for (int j = 0; j < vertex_count; j++) {
			if (i == j) {
				Vertex new_vertex(i+1);
				(this->vertices).push_back(new_vertex);
				Vertex* ref_vertex = &((this->vertices).at(i));
				Edge new_edge(ref_vertex, ref_vertex, 0);
				//std::cout << "i = " << i << ": " << (new_edge).to_string(TRIPLE) << std::endl;
				row.push_back(new_edge);
				continue;
			}
			Edge null_edge(0,0,0);
			row.push_back(null_edge);
		}
		adjacent_matrix.push_back(row);
	}

	for (unsigned int i = 0; i < list_of_edges.size(); i++) {
		Vertex* saved_vertex_0 = &((this->vertices).at(list_of_edges.at(i).at(0) -1));
		Vertex* saved_vertex_1 = &((this->vertices).at(list_of_edges.at(i).at(0) -1));
		Vertex* saved_vertex_2 = &((this->vertices).at(list_of_edges.at(i).at(1) -1));
		
		Edge new_edge(saved_vertex_1, saved_vertex_2, list_of_edges.at(i).at(2));
		adjacent_matrix.at(list_of_edges.at(i).at(0) -1).at(list_of_edges.at(i).at(1) -1) = new_edge;
		adjacent_matrix.at(list_of_edges.at(i).at(1) -1).at(list_of_edges.at(i).at(0) -1) = new_edge;
		
		Edge self_edge(saved_vertex_0, saved_vertex_0, 0);
		adjacent_matrix.at(list_of_edges.at(i).at(0) -1).at(list_of_edges.at(i).at(0) -1) = self_edge;
	}
	Vertex* saved_vertex_last = &((this->vertices).at((this->vertices).size() -1));
	Edge self_edge_last(saved_vertex_last, saved_vertex_last, 0);
	adjacent_matrix.at(vertex_count-1).at(vertex_count-1) = self_edge_last;

	this->adjacent_matrix = adjacent_matrix;
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

string Graph::to_string(int flag) {
	string result = "";
	for (uint i = 0; i < this->adjacent_matrix.size(); i++) {
		for (uint j = 0; j < this->adjacent_matrix.at(i).size(); j++) {
			result += this->adjacent_matrix.at(i).at(j).to_string(flag);
			if (j < this->adjacent_matrix.at(i).size() -1) {
				result += " ";
			}
		}
		result += "\n";
	}
	return result;
}

string Graph::to_string() {
	return this->to_string(WEIGHT_ONLY);
}

int Graph::get_next_vertex_number() {
	return (this->vertices).size() + 1;
}