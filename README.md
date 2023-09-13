# AStar
 A Star pathfinding algorithm

# Installation
Simply add the "AStar.cpp" and "AStar.h" files to your project.
Include them like so: #include "AStar.h".

# Usage
It is used to find a path from point A to point B in a grid based system.

# How to use:
To implement simply add the "Astar.h" and "Astar.cpp" into
your projects folder and include them as always.

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

# Terms of use
You can freely use my project in your projects.
Just don't sell it as "your" project.

# Versions
1.0.0 - First release