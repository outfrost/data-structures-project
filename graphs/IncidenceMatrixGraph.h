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
	
	std::string toString() override;
	
};


#endif //DATA_STRUCTURES_PROJECT_INCIDENCEMATRIXGRAPH_H
