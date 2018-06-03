/*
 * Note: This is not a true incidence matrix implementation.
 * This implementation stores edge metrics within the matrix,
 * therefore for any given edge the values are +metric and -metric
 * for the origin node and destination node respectively.
 */

#include <iostream>
#include <cstring>
#include <sstream>
#include <limits>
#include "../common/padString.h"
#include "../basic-structures/LinkedList.cpp"
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

void IncidenceMatrixGraph::addNodes(int count) {
	if (edgeCount > 0) {
		int* newIncidenceMatrix = new int[(nodeCount + count) * edgeCount]();
		std::memcpy(newIncidenceMatrix, incidenceMatrix, nodeCount * edgeCount * sizeof(int));
		delete[] incidenceMatrix;
		incidenceMatrix = newIncidenceMatrix;
	}
	nodeCount += count;
}

void IncidenceMatrixGraph::addEdge(int origin, int destination, int metric) {
	if (origin < nodeCount && destination < nodeCount
	    && origin >= 0 && destination >= 0 && origin != destination
	    && metric > 0) {
		int* newIncidenceMatrix = new int[nodeCount * (edgeCount + 1)]();
		for (int i = 0; i < nodeCount; i++) {
			std::memcpy(newIncidenceMatrix + i * (edgeCount + 1), incidenceMatrix + i * edgeCount, edgeCount * sizeof(int));
		}
		++edgeCount;
		delete[] incidenceMatrix;
		incidenceMatrix = newIncidenceMatrix;
		incidenceMatrix[index(origin, edgeCount - 1)] = metric;
		incidenceMatrix[index(destination, edgeCount - 1)] = -metric;
	}
}

void IncidenceMatrixGraph::clear() {
	delete[] incidenceMatrix;
	incidenceMatrix = new int[0];
	nodeCount = 0;
	edgeCount = 0;
}

std::string IncidenceMatrixGraph::toString() {
	std::stringstream stringStream;
	stringStream << "Node  ";
	for (int i = 0; i < edgeCount; i++) {
		stringStream << " | " << padString(std::to_string(i), 6, ' ');
	}
	stringStream << "\n";
	stringStream << "------";
	for (int i = 0; i < edgeCount; i++) {
		stringStream << "-|-------";
	}
	stringStream << "\n";
	for (int i = 0; i < nodeCount; i++) {
		stringStream << padString(std::to_string(i), 6, ' ');
		for (int k = 0; k < edgeCount; k++) {
			stringStream << " | " << padString(std::to_string(incidenceMatrix[index(i, k)]), 6, ' ');
		}
		stringStream << "\n";
	}
	stringStream.flush();
	return stringStream.str();
}

bool IncidenceMatrixGraph::findPathDijkstra(int startingNode, int destinationNode, int& distance, List<int>& path) {
	if (startingNode < nodeCount && destinationNode < nodeCount
	        && startingNode >= 0 && destinationNode >= 0) {
		bool visited[nodeCount] = {}; // { false ... }
		int tentativeDistance[nodeCount];
		std::fill_n(tentativeDistance, nodeCount, std::numeric_limits<int>::max());
		int previousHop[nodeCount];
		std::fill_n(previousHop, nodeCount, -1);
		
		tentativeDistance[startingNode] = 0;
		int currentNode = startingNode;
		
		while (currentNode != destinationNode && !visited[destinationNode]
		       && currentNode != -1) {
			for (int i = 0; i < edgeCount; i++) {
				if (incidenceMatrix[index(currentNode, i)] > 0) {
					int currentNeighbor = -1;
					for (int k = 0; k < nodeCount && currentNeighbor == -1; k++) {
						if (incidenceMatrix[index(k, i)] < 0) {
							currentNeighbor = k;
						}
					}
					if (!visited[currentNeighbor]) {
						if (tentativeDistance[currentNode] + incidenceMatrix[index(currentNode, i)]
							    < tentativeDistance[currentNeighbor]) {
							tentativeDistance[currentNeighbor] =
									tentativeDistance[currentNode] + incidenceMatrix[index(currentNode, i)];
							previousHop[currentNeighbor] = currentNode;
							// TODO This somehow creates infinite loops NOT ANY MORE
						}
					}
				}
			}
			visited[currentNode] = true;
			
			int smallestTentativeDistance = std::numeric_limits<int>::max();
			int nodeWithSmallestDistance = -1;
			for (int i = 0; i < nodeCount; i++) {
				if (!visited[i] && tentativeDistance[i] < smallestTentativeDistance) {
					smallestTentativeDistance = tentativeDistance[i];
					nodeWithSmallestDistance = i;
				}
			}
			currentNode = nodeWithSmallestDistance;
		}
		
		distance = tentativeDistance[destinationNode];
		if (currentNode != -1) {
			currentNode = destinationNode;
			while (currentNode != -1) {
				path.addStart(currentNode);
				currentNode = previousHop[currentNode];
			}
			return true;
		}
	}
	return false;
}

bool IncidenceMatrixGraph::findPathBellman(int startingNode, int destinationNode, int& distance, List<int>& path) {
	if (startingNode < nodeCount && destinationNode < nodeCount
		    && startingNode >= 0 && destinationNode >= 0) {
		int tentativeDistance[nodeCount];
		std::fill_n(tentativeDistance, nodeCount, std::numeric_limits<int>::max());
		int previousHop[nodeCount];
		std::fill_n(previousHop, nodeCount, -1);
		
		tentativeDistance[startingNode] = 0;
		
		for (int i = 0; i < nodeCount - 1; i++) {
			for (int k = 0; k < edgeCount; k++) {
				int origin = -1;
				int destination = -1;
				int metric = 0;
				getEdgeProperties(k, origin, destination, metric);
				if (tentativeDistance[origin] < std::numeric_limits<int>::max()) {
					if (tentativeDistance[origin] + metric < tentativeDistance[destination]) {
						tentativeDistance[destination] = tentativeDistance[origin] + metric;
						previousHop[destination] = origin;
					}
				}
			}
		}
		
		for (int k = 0; k < edgeCount; k++) {
			int origin = -1;
			int destination = -1;
			int metric = 0;
			getEdgeProperties(k, origin, destination, metric);
			if (tentativeDistance[origin] < std::numeric_limits<int>::max()) {
				if (tentativeDistance[origin] + metric < tentativeDistance[destination]) {
					return false; // TODO Handle problems better maybe™?
				}
			}
		}
		
		distance = tentativeDistance[destinationNode];
		if (tentativeDistance[destinationNode] < std::numeric_limits<int>::max()) {
			int currentNode = destinationNode;
			while (currentNode != -1) {
				path.addStart(currentNode);
				currentNode = previousHop[currentNode];
			}
			return true;
		}
	}
	return false;
}

inline int IncidenceMatrixGraph::index(int node, int edge) {
	return node * edgeCount + edge;
}

void IncidenceMatrixGraph::getEdgeProperties(int edge, int& originNode, int& destinationNode, int& metric) {
	for (int i = 0; i < nodeCount; i++) {
		if (incidenceMatrix[index(i, edge)] > 0) {
			originNode = i;
			metric = incidenceMatrix[index(i, edge)];
		}
		else if (incidenceMatrix[index(i, edge)] < 0) {
			destinationNode = i;
		}
	}
}
