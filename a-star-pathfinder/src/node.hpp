#ifndef __NODE_HPP_
#define __NODE_HPP_

#include <Windows.h>
#include <vector>

enum COLOR_SET { GREEN = 10, LIGHT_BLUE, RED, PINK, YELLOW, WHITE };
enum NODE_TYPE { STARTING = 0, ENDING, COMPUTED, OPEN_NODE, CLOSED, OBSTACLE, PATH };

typedef struct coordinate {
	unsigned int x;
	unsigned int y;
}Pos;

class Node
{
private:
	Pos position;
	int node_type;
	int f_cost, g_cost, h_cost; // (g cost = distance from starting node), (h cost = distance from ending node), (f cost = g + h)
public:
	Node() {
		f_cost = 0, g_cost = 0, h_cost = 0;
	}

	void set_node_pos_type(unsigned int pos_x, unsigned int pos_y, int _node_type) {
		node_type = _node_type;
		position.x = pos_x, position.y = pos_y;
	}
	void set_node_type(int type) {
		node_type = type;
	}
	int return_node_type() {
		return node_type;
	}

	void _set_g(int _g) {
		g_cost = _g;
	}
	void _set_h(int _h) {
		h_cost = _h;
	}
	void _set_f(int _f) {
		f_cost = _f;
	}

	int return_g_cost() {
		return g_cost;
	}
	int return_f_cost() {
		return f_cost;
	}

	int pos_x() {
		return position.x;
	}
	int pos_y() {
		return position.y;
	}
};

#endif
