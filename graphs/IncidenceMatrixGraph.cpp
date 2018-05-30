/*
 * Note: This is not a true incidence matrix implementation.
 * This implementation stores edge metrics within the matrix,
 * therefore for any given edge the values are +metric and -metric
 * for the origin node and destination node respectively.
 */

#include <iostream>
#include "IncidenceMatrixGraph.h"


IncidenceMatrixGraph::IncidenceMatrixGraph() {
	incidenceMatrix = new int[0];
	nodeCount = 0;
	edgeCount = 0;
}

IncidenceMatrixGraph::IncidenceMatrixGraph(int nodeCount) {
	incidenceMatrix = new int[0];
	this->nodeCount = nodeCount;
	this->edgeCount = 0;
}

IncidenceMatrixGraph::~IncidenceMatrixGraph() {
	delete[] incidenceMatrix;
}

std::string IncidenceMatrixGraph::toString() {
	return std::string();
}
