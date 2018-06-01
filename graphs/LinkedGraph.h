#ifndef DATA_STRUCTURES_PROJECT_LINKEDGRAPH_H
#define DATA_STRUCTURES_PROJECT_LINKEDGRAPH_H


#include <string>
#include "../basic-structures/ArrayList.cpp"
#include "../basic-structures/LinkedList.cpp"
#include "LinkedGraphEdge.h"
#include "Graph.h"

class LinkedGraph : public Graph {

private:
	ArrayList<LinkedList<LinkedGraphEdge*>*>* nodes = new ArrayList<LinkedList<LinkedGraphEdge*>*>();

public:
	LinkedGraph() = default;
	~LinkedGraph() override = default;
	
	void addNodes(int count) override;
	void addEdge(int origin, int destination, int metric) override;
	void clear() override;
	std::string toString() override;
	
	bool findPathDijkstra(int startingNode, int destinationNode, int& distance, List<int>& path) override;
	
};


#endif //DATA_STRUCTURES_PROJECT_LINKEDGRAPH_H
