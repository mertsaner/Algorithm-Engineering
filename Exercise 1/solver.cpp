#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

std::vector<int> parse_input_adjacents(string input_line);
int parse_input_vertex_count(string input_line);
vector<vector<int>> build_adjacent_matrix(int vertex_count, vector<vector<int>> edges);
vector<vector<int>> build_adjacent_combination(unsigned int combination_no, vector<vector<int>> base_matrix, vector<vector<int>> target_vector);
int calculate_change_cost(vector<vector<int>> base_matrix, vector<vector<int>> combination_matrix);
bool is_cluster(vector<vector<int>> adjacent_matrix);

int main(int argc, char **argv) {
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
		std::vector<int> parsed_line = parse_input_adjacents(input_line);
		if (!parsed_line.empty()) {
			adjacent_lines.push_back(parsed_line);
		}
	}
	
	cout << vertex_count << endl;
	cout << adjacent_lines.size() << endl;
	cout << "Building Adjacent-Matrix" << endl;
	vector<vector<int>> adjacent_matrix = build_adjacent_matrix(vertex_count, adjacent_lines);
	for (int x = 0; x < vertex_count; x++) {
		for (int y = 0; y < vertex_count; y++) {
			cout << adjacent_matrix.at(x).at(y) << " ";
		}
		cout << endl;
	}
	double entry_to_calculate = (double)(pow(((double) vertex_count - 1.),2.) + vertex_count - 1.) / 2.;
	unsigned int combination_count = (unsigned int) pow(2., entry_to_calculate);
	cout << combination_count << endl;
	std::vector<vector<int>> target_vector;
	for (int i = 0; i < vertex_count; i++) {
		for (int j = i+1; j < vertex_count; j++) {
			target_vector.push_back({i,j});
		}

	}

	//for (int i = 0; i < target_vector.size(); i++) {
	//	cout << target_vector.at(i).at(0) << "-" << target_vector.at(i).at(1) << endl;
	//}
	int cost = 100000;
	unsigned int best_combination = 0;
	unsigned int snd_combination = 0;
	int snd_cost = 10000;
	int cluster_counter = 0;
	for (unsigned int i = 1; i <= combination_count; i++) {
		vector<vector<int>> adjacent_matrix_2 = build_adjacent_combination(i, adjacent_matrix, target_vector);
		bool cluster_detected = is_cluster(adjacent_matrix_2);
		if (!cluster_detected) {
			continue;
		}
		cluster_counter += 1;
		int single_cost = calculate_change_cost(adjacent_matrix, adjacent_matrix_2);
		if (single_cost < cost) {
			snd_cost = cost;
			snd_combination = best_combination;
			cost = single_cost;
			best_combination = i;
			continue;
		}
		if (single_cost < snd_cost) {
			snd_cost = single_cost;
			snd_combination = i;
		}

	}
	/*
	for (int x = 0; x < vertex_count; x++) {
		for (int y = 0; y < vertex_count; y++) {
			cout << adjacent_matrix_2.at(x).at(y) << " ";
		}
		cout << endl;
	}
	*/
	cout << "minimal cost: " << cost << endl;
	cout << "2nd cost: " << snd_cost << endl;
	cout << "best combination: " << best_combination << endl;
	cout << "2nd combination: " << snd_combination << endl;
	cout << "clusters detected: " << cluster_counter << endl;
	return 0;
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
	while (position != string::npos) {
		position = input_line.find(" ");
		token = stoi(input_line.substr(0, position));
		edge_tokens.push_back(token);
		input_line.erase(0, position + 1);
	}
	return edge_tokens;
}

vector<vector<int>> build_adjacent_matrix(int vertex_count, vector<vector<int>> edges) {
	vector<vector<int>> adjacent_matrix;
	for (int i = 0; i < vertex_count; i++) {
		vector<int> row;
		for (int j = 0; j < vertex_count; j++) {
			row.push_back(0);
		}
		adjacent_matrix.push_back(row);
	}
	cout << adjacent_matrix.at(0).size() << endl;
	for (unsigned int i = 0; i < edges.size(); i++) {
		adjacent_matrix.at(edges.at(i).at(0)-1).at(edges.at(i).at(1)-1) = edges.at(i).at(2);
	}
	return adjacent_matrix;
}

vector<vector<int>> build_adjacent_combination(unsigned int combination_no, vector<vector<int>> base_matrix, vector<vector<int>> target_vector) {
	unsigned int entry_to_calculate = target_vector.size();
	vector<vector<int>> result_matrix = base_matrix;
	for (unsigned int i = 0; i < entry_to_calculate; i++) {
		unsigned int change = (combination_no >> i) & 1;
		if (change > 0) {
			result_matrix.at(target_vector.at(i).at(0)).at(target_vector.at(i).at(1)) = (result_matrix.at(target_vector.at(i).at(0)).at(target_vector.at(i).at(1))) * -1;
		}
	}
	return result_matrix;
}

int calculate_change_cost(vector<vector<int>> base_matrix, vector<vector<int>> combination_matrix) {
	int cost = 0;
	for (unsigned int i = 0; i < base_matrix.size(); i++) {
		for (unsigned int j = i+1; j < base_matrix.at(i).size(); j++) {
			if (base_matrix.at(i).at(j) == combination_matrix.at(i).at(j)) {
				continue;
			}
			cost += abs(base_matrix.at(i).at(j));
		}
	}
	return cost;
}

bool is_cluster(vector<vector<int>> adjacent_matrix) {
	// fill lower left corner
	for (unsigned int i = 0; i < adjacent_matrix.size(); i++) {
		for (unsigned int j = 0; j < adjacent_matrix.at(i).size(); j++) {
			adjacent_matrix.at(j).at(i) = adjacent_matrix.at(i).at(j);
		}
	}

	for (unsigned int i = 0; i < adjacent_matrix.size(); i++) {
		vector<int> row = adjacent_matrix.at(i);
		for (unsigned int j = 0; j < row.size(); j++) {
			if (row.at(j) <= 0) {
				continue;
			}
			for (unsigned int k = j+1; k < row.size(); k++) {
				if (row.at(k) <= 0) {
					continue;
				}
				if (adjacent_matrix.at(j).at(k) <= 0) {
					return false;
				}
			}
		}
	}
	return true;
}