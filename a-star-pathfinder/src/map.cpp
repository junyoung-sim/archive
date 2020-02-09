#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <vector>
#include "node.hpp"
#include "map.hpp"

using namespace std;

void Map::print_initial_map(int mode) {
	for (unsigned int i = 0; i < nodes.size(); i++) {
		for (unsigned int j = 0; j < nodes[i].size(); j++) {
			if (nodes[i][j].return_node_type() == STARTING) {
				// YELLOW for starting node
				SetConsoleTextAttribute(console, YELLOW);
				cout << "SS";
			}
			else if (nodes[i][j].return_node_type() == ENDING) {
				// RED for ending node
				SetConsoleTextAttribute(console, RED);
				cout << "EE";
			}
			else if (nodes[i][j].return_node_type() == OPEN_NODE) {
				// WHITE for other nodes during initial visualization
				SetConsoleTextAttribute(console, WHITE);
				cout << "XX";
			}
			else if (nodes[i][j].return_node_type() == COMPUTED || nodes[i][j].return_node_type() == CLOSED) {
				SetConsoleTextAttribute(console, GREEN); // GREEN for open node with f cost
				cout << nodes[i][j].return_f_cost();
			}
			else if (nodes[i][j].return_node_type() == PATH) {
				SetConsoleTextAttribute(console, LIGHT_BLUE);
				cout << "PP";
			}
			else { // OBSTACLE
				SetConsoleTextAttribute(console, PINK);
				cout << "OO";
			}

			cout << " ";
		}
		cout << endl;
	}

	SetConsoleTextAttribute(console, WHITE);
}

void Map::configurate_obstacles(unsigned int amount_of_obstacles) {
	int allocated_obstacles = 0;

	srand(time(NULL));
	for (unsigned int i = 0; i < nodes.size(); i++) {
		for (unsigned int j = 0; j < nodes[i].size(); j++) {
			if (nodes[i][j].return_node_type() == STARTING || nodes[i][j].return_node_type() == ENDING) {
			}
			else if (nodes[i][j].return_node_type() == OPEN_NODE) {
				if (rand() % 10 >= 8) {
					nodes[i][j].set_node_pos_type(i, j, OBSTACLE);
					allocated_obstacles++;
				}
			}
			else {}

			if (allocated_obstacles == amount_of_obstacles) break;
		}
	}
}
