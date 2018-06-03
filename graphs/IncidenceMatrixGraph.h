/*
 * Note: This is not a true incidence matrix implementation.
 * This implementation stores edge metrics within the matrix,
 * therefore for any given edge the values are +metric and -metric
 * for the origin node and destination node respectively.
 */

#ifndef DATA_STRUCTURES_PROJECT_INCIDENCEMATRIXGRAPH_H
#define DATA_STRUCTURES_PROJECT_INCIDENCEMATRIXGRAPH_H


#include <string>
#include "Graph.h"

class IncidenceMatrixGraph : public Graph {

private:
	int* incidenceMatrix;
	int nodeCount;
	int edgeCount;
	
public:
	IncidenceMatrixGraph();
	IncidenceMatrixGraph(int nodeCount);
	~IncidenceMatrixGraph() override;
	
	void addNodes(int count) override;
	void addEdge(int origin, int destination, int metric) override;
	void clear() override;
	std::string toString() override;
	
	bool findPathDijkstra(int startingNode, int destinationNode, int& distance, List<int>& path) override;
	bool findPathBellman(int startingNode, int destinationNode, int& distance, List<int>& path) override;

protected:
	inline int index(int node, int edge);
	void getEdgeProperties(int edge, int& originNode, int& destinationNode, int& metric);
	
};


#endif //DATA_STRUCTURES_PROJECT_INCIDENCEMATRIXGRAPH_H
