#include "solver.h"
#include <vector>
#include <iostream>
#include <tuple>



int main() {
	
	//Edge test_edge(1,2,5);
	//cout << test_edge.to_string() << endl;
	Graph g = parse_input();
	cout << g.to_string() << endl;


	return 0;
}

tuple<vector<Edge>,int> recursion_main(Graph graph){
	int k = 0;

	tuple<vector<Edge>,bool> result;

	while (true) {
		cout << "test with k= " << k << endl;
		result = recursion(graph, k);
		if (get<1>(result) == true) {
			break;
		}
		k += 1;
	
	}
	tuple<vector<Edge>,int> solution(get<0>(result),k);

	return solution;
}

tuple<vector<Edge>,bool> recursion(Graph graph,int k){
	if (k < 0) {
		vector<Edge> subresult;
		tuple<vector<Edge>, bool> result(subresult, false);
		return result;
	}

	bool is_graph = cluster_detection(graph);
	if(is_graph){
		cout << endl;
	}

	// -------------------- find p3 not clique in graph -------------------------
	

	// ------------- recursive call with first edge changed ---------------------
	//	-> clone actual graph
	Graph sub_graph_1 = graph.clone();
	//	-> change the edge if not forbidden (is_set = !is_set)
	//	-> make recursive call with decreased budget
	//	-> check result and if this branch is a solution
	//		-> add the changed edge to the result
	//		-> return the result

	// ------------- recursive call with second edge changed -------------------
	//	-> clone actual graph
	Graph sub_graph_2 = graph.clone();
	//	-> change the edge if not forbidden (is_set = !is_set)
	//	-> make recursive call with decreased budget
	//	-> check result and if this branch is a solution
	//		-> add the changed edge to the result
	//		-> return the result

	// ------------- recursive call with third edge changed --------------------
	//	-> clone actual graph
	Graph sub_graph_3 = graph.clone();
	//	-> change the edge if not forbidden (is_set = !is_set)
	//	-> make recursive call with decreased budget
	//	-> check result and if this branch is a solution
	//		-> add the changed edge to the result
	//		-> return the result



	vector<Edge> empty_subresult;
	tuple<vector<Edge>,bool> result(empty_subresult, false);
	return result;
}

bool cluster_detection(Graph graph){
	return false;
}

vector<uint> find_p3_not_clique(Graph graph) {
	return {};
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