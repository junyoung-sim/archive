
#include <iostream>
#include <cmath>
#include <vector>
#include "pathfinder_algorithm.hpp"
#include "map.hpp"
#include "node.hpp"

using namespace std;

void Stack::push(Node node) { // push in new open node to the stack
	node_stack.push_back(node);
}

// pop out the node on the bottom layer (minimum value)
Node Stack::pop() {
	Node pop_node = node_stack[0];
	return pop_node;
}

void Stack::swap(int idx1, int idx2) {
	Node tmp = node_stack[idx1];
	node_stack[idx1] = node_stack[idx2];
	node_stack[idx2] = tmp;
}

int Stack::partition(int left, int right) {
	int pivot = left;
	int low = left;
	int high = right;

	while (low < high) {
		while (node_stack[pivot].return_f_cost() >= node_stack[low].return_f_cost() && low < right) low++;
		while (node_stack[pivot].return_f_cost() <= node_stack[high].return_f_cost() && high > (left + 1)) high--;

		// when an exchange point bigger/smaller than model[pivot]
		if (low < high) swap(low, high);
	}

	swap(left, high); // partition and swap the data sets by if their bigger/smaller than model[pivot]
	return high;
}

void Stack::quicksort(int left, int right) {
	if (left <= right)
	{
		int pivot = partition(left, right);
		quicksort(left, pivot - 1);
		quicksort(pivot + 1, right);
	}
}

void Stack::verify_sorted_stack() {
	int i = 0;
	while (i < return_stack_right()) {
		if (node_stack[i].return_f_cost() > node_stack[i + 1].return_f_cost()) {
			swap(i, i + 1);
		}
		else {}
		i++;
	}
}

Map Pathfinder::pathfinding() {
	int frame_num = 0;
	int g_cost_x, g_cost_y, g;
	int h_cost_x, h_cost_y, h;
	int f;

	Stack path_nodes;
	Stack node_stack;

	Pos path_pos; // position of the last open node detected as the ending point of the path
	Pos current_nodePos; // current open node position

	current_nodePos.x = map[0].return_start_pos_x(); // starting from the starting node of the map
	current_nodePos.y = map[0].return_start_pos_y() + 1;

	path_pos.x = -1, path_pos.y = -1;

	bool found_path = false;

	// A* PATHFINDING ALGORITHM (COMPUTING NODE EFFICIENCY (F/G/H COSTS))
	while (found_path != true) {
		for (unsigned int i = current_nodePos.x - 1; i <= current_nodePos.x + 1; i++) {
			for (unsigned int j = current_nodePos.y - 1; j <= current_nodePos.y + 1; j++) {
				// check if surrounding coordinates are out of bounds
				if (i < 0 || i >= map[0].rows() || j < 0 || j >= map[0].cols()) {}
				else {
					if (i == current_nodePos.x && j == current_nodePos.y) {}
					else {
						Pos pos;
						pos.x = i, pos.y = j;

						// do not manipulate the following nodes:
						if (map[0].node_available(pos) == OBSTACLE || map[0].node_available(pos) == STARTING
							|| map[0].node_available(pos) == ENDING || map[0].node_available(pos) == COMPUTED || map[0].node_available(pos) == CLOSED) {
						}
						else {
							// compute g cost of surrounding nodes
							// calculate the distance from the starting node
							// figure out if the node is vertically/horizontally locate from parent node (current open node)
							// then add scaled coordinate/diagonal values as the g cost of the node
							g_cost_x = pos.x - current_nodePos.x;
							g_cost_y = pos.y - current_nodePos.y;
							g = map[0].get_g(current_nodePos);

							// if the node is diagonal to the parent node, x and y differences will not be 0
							if (g_cost_x != 0 && g_cost_y != 0) {
								g += map[0]._diagonal();
							}
							else {
								g += map[0]._scale();
							}

							// compute h cost
							// calculate the distance to ending node by subtracting x and y coordinate differences
							h_cost_x = map[0].return_ending_pos_x() - pos.x;
							h_cost_y = map[0].return_ending_pos_y() - pos.y;
							h = abs(h_cost_x + h_cost_y);

							f = g + h;
							map[0].set_g(pos, g);
							map[0].set_h(pos, h);
							map[0].set_f(pos, f);

							map[0].set_nodeType(pos, COMPUTED);
						}
					}
				}
			}
		}

		if (frame_num != 0) {
			map[0].set_nodeType(current_nodePos, CLOSED); // close the parent node (make it inaccessible to change f value)
		}
		else {}

		// observe all nodes surrounding the ending node
		// to check if there are any computed nodes adjacent to it --> (detecting if the path is found)
		bool adjacent_node = false;
		for (unsigned i = map[0].return_ending_pos_x() - 1; i < map[0].return_ending_pos_x() + 1; i++) {
			for (unsigned j = map[0].return_ending_pos_y() - 1; j < map[0].return_ending_pos_y() + 1; j++) {
				// check if the coordinates are out of bounds
				if (i < 0 || i >= map[0].rows() || j < 0 || j >= map[0].cols()) {}
				else {
					Pos pos; pos.x = i, pos.y = j;
					// check if any adjacent nodes are computed ==> path is found!
					if (map[0].node_available(pos) == COMPUTED) {
						path_nodes.push(map[0].return_node(pos)); // accumulate possible final path nodes
						adjacent_node = true;
					}
					else {}
				}
			}
		}

		if (adjacent_node == true) { // when the algorithm found a node adjacent to the ending node
			path_nodes.quicksort(0, path_nodes.return_stack_right()); // sort the possible final path nodes by their f cost
			path_nodes.verify_sorted_stack();
			found_path = true; // breaks out of the while loop
		}
		else {
			// following code will only proceed when path isn't found yet
			for (unsigned int i = 0; i < map[0].rows(); i++) {
				for (unsigned int j = 0; j < map[0].cols(); j++) {
					Pos pos; pos.x = i, pos.y = j;
					if (map[0].node_available(pos) == COMPUTED) {
						node_stack.push(map[0].return_node(pos)); // push in all computed nodes in the map
					}
					else {}
				}
			}

			node_stack.quicksort(0, node_stack.return_stack_right()); // sort the nodes by their f cost (min -> max)
			node_stack.verify_sorted_stack(); // verify the sorted vector

			Node nd = node_stack.pop(); // return the node with the smallest f cost
			current_nodePos.x = nd.pos_x(), current_nodePos.y = nd.pos_y(); // use it as the next parent node --> explore new way

			node_stack.deallocate_stack(); // free up stack memory for further use
			frame_num++;
		}
	}

	// return the node with the lowest f cost among the nodes adjacent to the ending node
	Node node = path_nodes.pop();
	path_pos.x = node.pos_x(), path_pos.y = node.pos_y();

	path_nodes.deallocate_stack(); // free up memory
	map[0].set_nodeType(path_pos, PATH); // set the detected final path node to PATH type

	map[0].print_initial_map(1);
	cout << endl;

	bool finalized_path = false;

	// starting from the final path node detected beforehand, use it as the indicator
	// for backtracking the nodes with the smallest f cost values to finalize it in the path
	while (finalized_path != true) {
		// this process below will only be executed when the process above 
		// did not detect the starting node adjacent to the node
		for (unsigned int i = path_pos.x - 1; i < path_pos.x + 2; i++) {
			for (unsigned int j = path_pos.y - 1; j < path_pos.y + 2; j++) {
				// check out of bounds
				if (i < 0 || i >= map[0].rows() || j < 0 || j >= map[0].cols()) { cout << " X "; }
				else {
					Pos pos; pos.x = i, pos.y = j;
					if (map[0].node_available(pos) != PATH && map[0].return_f(pos) != 0) {
						cout << map[0].return_f(pos) << " ";
						path_nodes.push(map[0].return_node(pos));
					}
				}
			}
		}

		cout << path_nodes.return_stack_right() << " --> ";
		path_nodes.quicksort(0, path_nodes.return_stack_right());
		path_nodes.verify_sorted_stack();

		node = path_nodes.pop();
		path_pos.x = node.pos_x(), path_pos.y = node.pos_y();
		cout << node.return_f_cost() << endl << endl;

		map[0].set_nodeType(path_pos, PATH); // set the nodes to PATH type
		path_nodes.deallocate_stack();

		// check if the PATH node is adjacent to the starting node --> (CHECK IF THE ALGORITHM IS DONE!)
		for (unsigned int i = path_pos.x - 1; i < path_pos.x + 2; i++) {
			for (unsigned int j = path_pos.y - 1; j < path_pos.y + 2; j++) {
				// check out of bounds
				if (i < 0 || i >= map[0].rows() || j < 0 || j >= map[0].cols()) {}
				else {
					Pos pos; pos.x = i, pos.y = j;
					if (map[0].node_available(pos) == STARTING) {
						finalized_path = true;
					}
				}
			}
		}
	}

	map[0].print_initial_map(1);

	return map[0];
}
