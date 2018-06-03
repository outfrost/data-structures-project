#ifndef DATA_STRUCTURES_PROJECT_GRAPH_H
#define DATA_STRUCTURES_PROJECT_GRAPH_H


#include <string>
#include "../basic-structures/List.cpp"

class Graph {

public:
	virtual ~Graph() = default;
	
	virtual void addNodes(int count) = 0;
	virtual void addEdge(int origin, int destination, int metric) = 0;
	virtual void clear() = 0;
	virtual std::string toString() = 0;
	
	virtual bool findPathDijkstra(int startingNode, int destinationNode, int& distance, List<int>& path) = 0;
	virtual bool findPathBellman(int startingNode, int destinationNode, int& distance, List<int>& path) = 0;
	
};


#endif //DATA_STRUCTURES_PROJECT_GRAPH_H
