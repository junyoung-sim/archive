#ifndef __PATHFINDER_HPP_
#define __PATHFINDER_HPP_

#include <iostream>
#include <vector>
#include "node.hpp"
#include "map.hpp"

class Pathfinder
{
private:
	unsigned int path_update_interval; // in milliseconds
	std::vector<Map> map;
public:
	Pathfinder(HANDLE _console, unsigned int row, unsigned int col, unsigned _scale,
		Pos start_node, Pos end_node, unsigned int amount_of_obstacles, unsigned int _update_interval) : path_update_interval(_update_interval) {

		// create and configurate map here
		map.push_back(Map(_console, row, col, _scale, start_node, end_node));
		map[0].configurate_obstacles(amount_of_obstacles);
	}

	Map pathfinding();
};

class Stack
{
private:
	unsigned int stack_size;
	std::vector<Node> node_stack;
public:
	Stack() {}

	unsigned int return_stack_right() {
		return node_stack.size() - 1;
	}

	void push(Node node);
	Node pop();

	void deallocate_stack() {
		node_stack.clear();
	}

	void quicksort(int left, int right);
	int partition(int left, int right);
	void swap(int idx1, int idx2);
	void verify_sorted_stack();
};

#endif
