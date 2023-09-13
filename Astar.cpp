#include "Astar.h"

Node FindNode(std::vector<Node> &nodes, Node node) {
	for (Node n : nodes) {
		if (n == node) return n;
	}
	return Node(-1, -1);
}

std::vector<Node> GenerateMap(std::vector<Node> nodes) {
	for (int x = 0; x < nodes.size(); x++) {
		if (!nodes[x].blocked) {
			std::vector<Node*> diagonals;
			for (int y = 0; y < nodes.size(); y++) {
				if (IsDirectNeighbor(nodes[x], nodes[y]) && !nodes[y].blocked) {
					nodes[x].neighbors.push_back(&nodes[y]);
				}
				else if (IsDiagonal(nodes[x], nodes[y]) && !nodes[y].blocked) {
					diagonals.push_back(&nodes[y]);
				}
			}
			for (int y = 0; y < diagonals.size(); y++) {
				for (int i = 0; i < nodes[x].neighbors.size(); i++) {
					if (IsDirectNeighbor(*diagonals[y], *nodes[x].neighbors[i]) && !nodes[x].neighbors[i]->blocked) {
						nodes[x].neighbors.push_back(diagonals[y]);
						break;
					}
				}
			}
		}
	}
	return nodes;
}

int ManhattenDist(Node pos1, Node pos2) {
	int x_dif, y_dif;

	x_dif = pos2.x - pos1.x;
	y_dif = pos2.y - pos1.y;

	if (x_dif < 0) x_dif = -x_dif;
	if (y_dif < 0) y_dif = -y_dif;

	return x_dif + y_dif;
}

double EuclideanDist(Node pos1, Node pos2) {
	return std::sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}

bool IsNeighbor(Node current, Node toCheck) {
	int x_dif = current.x - toCheck.x;
	int y_dif = current.y - toCheck.y;

	if (x_dif < 0) x_dif = -x_dif;
	if (y_dif < 0) y_dif = -y_dif;

	if (x_dif == 0 && y_dif == 0) return false;
	if (x_dif < 2 && y_dif < 2) return true;
	return false;
}

bool IsDirectNeighbor(Node src, Node dest) {
	int x_dif = dest.x - src.x;
	int y_dif = dest.y - src.y;

	if (x_dif < 0) x_dif = -x_dif;
	if (y_dif < 0) y_dif = -y_dif;

	if (src.x == dest.x && src.y == dest.y) return false;
	if (x_dif == 0 && y_dif < 2 || x_dif < 2 && y_dif == 0) return true;
	return false;
}

bool IsDiagonal(Node src, Node dest) {
	int x_dif = dest.x - src.x;
	int y_dif = dest.y - src.y;

	if (x_dif < 0) x_dif = -x_dif;
	if (y_dif < 0) y_dif = -y_dif;

	if (x_dif == 1 && y_dif == 1) return true;
	return false;
}

std::vector<Node> AStar(Node start, Node goal, int maxTime) {
	std::vector<Node*> openSet;
	std::vector<Node*> closedSet;
	std::vector<Node> path;

	openSet.push_back(&start);
	bool foundpath = false;
	Node* end = &goal;
	double t = clock();
	while (!openSet.empty()) {
		// Breaking loop if it is taking too long
		if (clock() - t > maxTime) break;
		Node* current = openSet[0];
		// Searching lowest f
		for (Node* n : openSet) {
			if (n->f < current->f) {
				current = n;
			}
		}
		// Erasing current node from openset
		openSet.erase(std::remove(openSet.begin(), openSet.end(), current), openSet.end());
		// Checking of the current selected node is goal
		if (*current == goal) {
			foundpath = true;
			end = current;
			break;
		}
		// When current is not goal -> put it into closedSet;
		closedSet.push_back(current);

		// Looping neighbor nodes of current node
		for (Node* neighbor : current->neighbors) {
			if (neighbor->blocked) {
				continue;
			}
			// Calculating tentative_g
			double tentative_g = current->g + EuclideanDist(*current, *neighbor);
			// Checking if neighbor is in closed set -> skipping if it is
			if (std::find(closedSet.begin(), closedSet.end(), neighbor) != closedSet.end()) {
				continue;
			}
			// Checking if neighbor is in open set
			bool inOpenSet = (std::find(openSet.begin(), openSet.end(), neighbor) != openSet.end());
			// Skipping if tentative_g is higher than neighbor
			if (tentative_g > neighbor->g && inOpenSet) {
				continue;
			}
			// Setting neighbors parent
			neighbor->parent = current;
			// Calculating neighbor costs and pushing it to open set if it is not in open set
			if (!inOpenSet) {
				neighbor->h = ManhattenDist(*neighbor, goal);
				neighbor->g = tentative_g;
				neighbor->f = neighbor->h + tentative_g;
				openSet.push_back(neighbor);
				continue;
			}
			// Calculating neighbor g and h costs
			neighbor->g = tentative_g;
			neighbor->f = neighbor->h + tentative_g;
		}
	}
	// Traceback and build path
	if (foundpath) {
		Node* current = end;
		while (current) {
			path.push_back(*current);
			current = current->parent;
			if (*current == start) {
				current = nullptr;
				break;
			}
		}
	}
	// Reversing the path
	std::reverse(path.begin(), path.end());
	return path;
}