#include <iostream>
#include <vector>
#include "Astar.h"

int randi(int min, int max) {
	int num = rand() % max + min;
	return num;
}

void test() {
	std::vector<Node> nodes;
	Node start(0, 4);
	Node goal(4, 0);
	for (int x = 0; x < 400/16; x++) {
		for (int y = 0; y < 400/16; y++) {
			bool blocked = false;
			if (randi(0, 100) > 75) blocked = true;
			if (x == start.x && y == start.y) blocked = false;
			if (x == goal.x && y == goal.y) blocked = false;
			Node n(x, y, blocked);
			nodes.push_back(n);
		}
	}

	nodes = GenerateMap(nodes);

	start = FindNode(nodes, start);
	std::vector<Node> path = AStar(start, goal);

	std::cout << "Current path:\n";
	for (Node n : path) {
		std::cout << "(" << n.x << ", " << n.y << ")\n";
	}
	if (path.empty()) std::cout << "no path found!\n";
}

int main() {
	test();
	return 0;
}