#ifndef __MAP_HPP_
#define __MAP_HPP_

#include <vector>
#include <cmath>
#include <Windows.h>
#include "node.hpp"

class Map : public Node
{
private:
	HANDLE console;
	unsigned int map_scale;
	unsigned int diagonal_len;

	Pos starting_node;
	Pos ending_node;

	std::vector<std::vector<Node>> nodes;
public:
	// row = amount of rows of the map, col = amount of cols of the map (dimensions)
	Map(HANDLE _console, unsigned int row, unsigned int col,
		unsigned _scale, Pos start_node, Pos end_node) : console(_console), map_scale(_scale), starting_node(start_node), ending_node(end_node) {
		// compute the diagonal length in the map
		diagonal_len = sqrt(2 * (pow(map_scale, 2)));

		nodes.resize(row);
		for (unsigned int i = 0; i < nodes.size(); i++) nodes[i].resize(col);

		for (unsigned int i = 0; i < nodes.size(); i++) {
			for (unsigned int j = 0; j < nodes[i].size(); j++) {
				if (i == start_node.x && j == start_node.y) {
					nodes[i][j].set_node_pos_type(i, j, STARTING); // set up starting node
				}
				else if (i == end_node.x && j == end_node.y) {
					nodes[i][j].set_node_pos_type(i, j, ENDING); // set up ending node
				}
				else {
					nodes[i][j].set_node_pos_type(i, j, OPEN_NODE); // set up open nodes
				}
			}
		}
	}

	Node return_node(Pos pos) {
		return nodes[pos.x][pos.y];
	}
	int node_available(Pos node_pos) {
		return nodes[node_pos.x][node_pos.y].return_node_type();
	}

	int return_start_pos_x() {
		return starting_node.x;
	}
	int return_start_pos_y() {
		return starting_node.x;
	}

	int return_ending_pos_x() {
		return ending_node.x;
	}
	int return_ending_pos_y() {
		return ending_node.y;
	}

	int rows() {
		return nodes.size();
	}
	int cols() {
		return nodes[0].size();
	}
	int _scale() {
		return map_scale;
	}
	int _diagonal() {
		return diagonal_len;
	}

	int get_g(Pos pos) {
		return nodes[pos.x][pos.y].return_g_cost();
	}
	void set_g(Pos pos, int _g) {
		nodes[pos.x][pos.y]._set_g(_g);
	}
	void set_h(Pos pos, int _h) {
		nodes[pos.x][pos.y]._set_h(_h);
	}
	void set_f(Pos pos, int _f) {
		nodes[pos.x][pos.y]._set_f(_f);
	}
	int return_f(Pos pos) {
		return nodes[pos.x][pos.y].return_f_cost();
	}

	void set_nodeType(Pos pos, int type) {
		nodes[pos.x][pos.y].set_node_type(type);
	}

	void print_initial_map(int mode);
	void configurate_obstacles(unsigned int amount_of_obstacles);
};

#endif
