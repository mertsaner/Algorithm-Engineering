#include "solver.h"
#include <vector>
#include <iostream>



int main() {
	
	//Edge test_edge(1,2,5);
	//cout << test_edge.to_string() << endl;
	Graph g = parse_input();
	cout << g.to_string(TRIPLE) << endl;
	return 0;
}

Graph parse_input() {
	string input_line;
	int i = 1;
	int vertex_count = 0;
	vector<vector<int>> adjacent_lines;
	while (getline(cin, input_line)) {
		if (i == 1) {
			// parse vertex count
			vertex_count = parse_input_vertex_count(input_line);
			if (vertex_count > 0) {
				i += 1;
			}
			continue;
		}
		vector<int> parsed_line = parse_input_adjacents(input_line);
		if (!parsed_line.empty() && parsed_line.size() == 3) {
			// graph add edge and/or vertex
			adjacent_lines.push_back(parsed_line);
		}
	}
	Graph graph(vertex_count, adjacent_lines);
	return graph;
}


int parse_input_vertex_count(string input_line) {
	if (input_line.empty()) {
		return 0;
	}
	int count = stoi(input_line);
	return count;
}

std::vector<int> parse_input_adjacents(string input_line) {
	if (input_line.empty()) {
		return {};
	}
	std::vector<int> edge_tokens;
	int token;
	size_t position = 0;
	size_t comment_position = input_line.find("#");
	if (comment_position != string::npos) {
		input_line = input_line.substr(0, comment_position);
	}
	while (position != string::npos) {
		position = input_line.find(" ");
		if (!input_line.substr(0, position).empty()) {
			token = stoi(input_line.substr(0, position));
			edge_tokens.push_back(token);
		}
		input_line.erase(0, position + 1);
	}
	return edge_tokens;
}