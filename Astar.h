#pragma once

/*
	##############################
	# AStar algorithm			 #
	# Written by: Adrian Jahraus #
	# Version: 1.0.0			 #
	##############################
*/

/*
	To see how to use it i highly recommend reading the README.md file
	To implement simply add the "Astar.h" and "Astar.cpp" into
	your projects folder and include them as always

	After loading your map (GameObjects or whatever you are using)
	loop through your opjects and generate Nodes out of it.
	If you have for example Tiles that are 16x16 you devide their
	x and y position by 16 and generate a Node out of it. Add
	generated Node to a vector<Node>.
	After computing all your gameobjects into Nodes just run the
	GenerateMap function giving it your generated vector.
	It then returns a new vector with computed map.
	Example:
	
	int gridSize = 16;
	vector<Nodes> nodes;
	for (Object obj : GameObjects){
		nodes.push_back(Node(obj.x / gridSize, obj.y / gridSize, obj.isWall));
	}
	nodes = GenerateMap(nodes);
*/

#include <cmath>
#include <vector>
#include <time.h>
#include <algorithm>
#include <string>

#ifndef ASTAR_H
#define ASTAR_H

struct Node {
	int x, y;
	double g = 0.0f;
	double f = 0.0f;
	double h = 0.0f;
	bool blocked = false;
	std::vector<Node*> neighbors;
	Node* parent = nullptr;
	// \return sets position and handling state of node
	Node(int xpos, int ypos, bool isBlocked = false) {
		x = xpos;
		y = ypos;
		blocked = isBlocked;
	}
	Node() = default;

	bool operator==(Node rn) {
		if (x == rn.x && y == rn.y) return true;
		return false;
	}
	
	bool operator!=(Node rn) {
		if (x == rn.x && y == rn.y) return false;
		return true;
	}
};

// \return finds the corrosponding node in a list (same position) and returns it
Node FindNode(std::vector<Node> &nodes, Node node);

// \return Computes all neighbors for each Node and returns finished vector
std::vector<Node> GenerateMap(std::vector<Node> nodes);

// \return Calculates the Manhatten distance between 2 Nodes, returns int
int ManhattenDist(Node pos1, Node pos2);

// \return Calculates the Euclidean distance between 2 Nodes, returns double
double EuclideanDist(Node pos1, Node pos2);

// \return Checks if the two Nodes are neighbors returns bool
bool IsNeighbor(Node current, Node toCheck);

// \return Checks if the two Nodes are direct neighbors (4 directions)
bool IsDirectNeighbor(Node src, Node dest);

// \return Checks if the two Nodes are diagonal to each other
bool IsDiagonal(Node src, Node dest);

// \return AStar algorithm that returns a path to goal(if possible)
std::vector<Node> AStar(Node start, Node goal, int maxTime = 50);

#endif ASTAR_H