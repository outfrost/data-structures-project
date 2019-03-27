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
#include "../basic-structures/ArrayList.cpp"


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

int IncidenceMatrixGraph::totalEdgeMetric() {
	int result = 0;
	for (int i = 0; i < edgeCount; i++) {
		int metric = -1;
		for (int k = 0; k < nodeCount && metric == -1; k++) {
			if (incidenceMatrix[index(k, i)] != 0) {
				metric = std::abs(incidenceMatrix[index(k, i)]);
			}
		}
		result += metric;
	}
	return result;
}

bool IncidenceMatrixGraph::containsEdge(int from, int to) {
	if (from < nodeCount && to < nodeCount
			&& from >= 0 && to >= 0
			&& from != to) {
		for (int i = 0; i < edgeCount; i++) {
			if (incidenceMatrix[index(from, i)] != 0) {
				int origin = -1;
				int destination = -1;
				int metric = 0;
				getEdgeProperties(i, origin, destination, metric);
				if (origin == to || destination == to) {
					return true;
				}
			}
		}
	}
	return false;
}

Graph* IncidenceMatrixGraph::findMstPrim() {
	Graph* result = new IncidenceMatrixGraph(nodeCount);
	ArrayList<bool> nodeIncluded(nodeCount, false);
	
	ArrayList<int> cheapestConnectionMetric(nodeCount, std::numeric_limits<int>::max());
	ArrayList<int> cheapestConnectionEdge(nodeCount, -1);
	
	int currentNode = 0;
	for (int nodesRemaining = nodeCount; nodesRemaining > 0 && currentNode != -1; nodesRemaining--) {
		nodeIncluded.set(currentNode, true);
		if (cheapestConnectionEdge.get(currentNode) != -1) {
			int origin = -1;
			int destination = -1;
			int metric = 0;
			getEdgeProperties(cheapestConnectionEdge.get(currentNode), origin, destination, metric);
			result->addEdge(origin, destination, metric);
		}
		
		for (int i = 0; i < edgeCount; i++) {
			int origin = -1;
			int destination = -1;
			int metric = 0;
			getEdgeProperties(i, origin, destination, metric);
			if (origin == currentNode
					&& !nodeIncluded.get(destination)
					&& metric < cheapestConnectionMetric.get(destination)) {
				cheapestConnectionMetric.set(destination, metric);
				cheapestConnectionEdge.set(destination, i);
			}
			else if (destination == currentNode
					&& !nodeIncluded.get(origin)
					&& metric < cheapestConnectionMetric.get(origin)) {
				cheapestConnectionMetric.set(origin, metric);
				cheapestConnectionEdge.set(origin, i);
			}
		}
		
		int lowestMetric = std::numeric_limits<int>::max();
		int lowestMetricNode = -1;
		for (int i = 0; i < nodeCount; i++) {
			if (!nodeIncluded.get(i) && cheapestConnectionMetric.get(i) < lowestMetric) {
				lowestMetric = cheapestConnectionMetric.get(i);
				lowestMetricNode = i;
			}
		}
		currentNode = lowestMetricNode;
	}
	return result;
}

Graph* IncidenceMatrixGraph::findMstKruskal() {
	Graph* result = new IncidenceMatrixGraph(nodeCount);
	ArrayList<int> treeId(nodeCount);
	for (int i = 0; i < nodeCount; i++) {
		treeId.set(i, i);
	}
	int trees = nodeCount;
	ArrayList<bool> edgeConsidered(edgeCount, false);
	bool edgesRemain = true;
	
	while (trees > 1 && edgesRemain) {
		int lowestMetric = std::numeric_limits<int>::max();
		int lowestMetricEdge = -1;
		int lowestMetricEdgeOrigin = -1;
		int lowestMetricEdgeDestination = -1;
		
		for (int i = 0; i < edgeCount; i++) {
			if (!edgeConsidered.get(i)) {
				int origin = -1;
				int destination = -1;
				int metric = 0;
				getEdgeProperties(i, origin, destination, metric);
				if (metric < lowestMetric) {
					lowestMetric = metric;
					lowestMetricEdge = i;
					lowestMetricEdgeOrigin = origin;
					lowestMetricEdgeDestination = destination;
				}
			}
		}
		
		if (lowestMetricEdge != -1) {
			edgeConsidered.set(lowestMetricEdge, true);
			if (treeId.get(lowestMetricEdgeOrigin) != treeId.get(lowestMetricEdgeDestination)) {
				result->addEdge(lowestMetricEdgeOrigin, lowestMetricEdgeDestination, lowestMetric);
				int mergedTreeId = treeId.get(lowestMetricEdgeDestination);
				for (int i = 0; i < nodeCount; i++) {
					if (treeId.get(i) == mergedTreeId) {
						treeId.set(i, treeId.get(lowestMetricEdgeOrigin));
					}
				}
				--trees;
			}
		}
		else {
			edgesRemain = false;
		}
	}
	return result;
}

bool IncidenceMatrixGraph::findPathDijkstra(int startingNode, int destinationNode, int& distance, List<int>& path) {
	if (startingNode < nodeCount && destinationNode < nodeCount
	        && startingNode >= 0 && destinationNode >= 0) {
		ArrayList<bool> visited(nodeCount, false);
		ArrayList<int> tentativeDistance(nodeCount, std::numeric_limits<int>::max());
		ArrayList<int> previousHop(nodeCount, -1);
		
		tentativeDistance.set(startingNode, 0);
		int currentNode = startingNode;
		
		while (currentNode != destinationNode && !visited.get(destinationNode)
		       && currentNode != -1) {
			for (int i = 0; i < edgeCount; i++) {
				if (incidenceMatrix[index(currentNode, i)] > 0) {
					int currentNeighbor = -1;
					for (int k = 0; k < nodeCount && currentNeighbor == -1; k++) {
						if (incidenceMatrix[index(k, i)] < 0) {
							currentNeighbor = k;
						}
					}
					if (!visited.get(currentNeighbor)) {
						if (tentativeDistance.get(currentNode) + incidenceMatrix[index(currentNode, i)]
							    < tentativeDistance.get(currentNeighbor)) {
							tentativeDistance.set(currentNeighbor,
									tentativeDistance.get(currentNode) + incidenceMatrix[index(currentNode, i)]);
							previousHop.set(currentNeighbor, currentNode);
							// TODO This somehow creates infinite loops NOT ANY MORE
						}
					}
				}
			}
			visited.set(currentNode, true);
			
			int smallestTentativeDistance = std::numeric_limits<int>::max();
			int nodeWithSmallestDistance = -1;
			for (int i = 0; i < nodeCount; i++) {
				if (!visited.get(i) && tentativeDistance.get(i) < smallestTentativeDistance) {
					smallestTentativeDistance = tentativeDistance.get(i);
					nodeWithSmallestDistance = i;
				}
			}
			currentNode = nodeWithSmallestDistance;
		}
		
		distance = tentativeDistance.get(destinationNode);
		if (currentNode != -1) {
			currentNode = destinationNode;
			while (currentNode != -1) {
				path.addStart(currentNode);
				currentNode = previousHop.get(currentNode);
			}
			return true;
		}
	}
	return false;
}

bool IncidenceMatrixGraph::findPathBellman(int startingNode, int destinationNode, int& distance, List<int>& path) {
	if (startingNode < nodeCount && destinationNode < nodeCount
		    && startingNode >= 0 && destinationNode >= 0) {
		ArrayList<int> tentativeDistance(nodeCount, std::numeric_limits<int>::max());
		ArrayList<int> previousHop(nodeCount, -1);
		
		tentativeDistance.set(startingNode, 0);
		
		for (int i = 0; i < nodeCount - 1; i++) {
			for (int k = 0; k < edgeCount; k++) {
				int origin = -1;
				int destination = -1;
				int metric = 0;
				getEdgeProperties(k, origin, destination, metric);
				if (tentativeDistance.get(origin) < std::numeric_limits<int>::max()) {
					if (tentativeDistance.get(origin) + metric < tentativeDistance.get(destination)) {
						tentativeDistance.set(destination, tentativeDistance.get(origin) + metric);
						previousHop.set(destination, origin);
					}
				}
			}
		}
		
		for (int k = 0; k < edgeCount; k++) {
			int origin = -1;
			int destination = -1;
			int metric = 0;
			getEdgeProperties(k, origin, destination, metric);
			if (tentativeDistance.get(origin) < std::numeric_limits<int>::max()) {
				if (tentativeDistance.get(origin) + metric < tentativeDistance.get(destination)) {
					return false; // TODO Handle problems better maybe™?
				}
			}
		}
		
		distance = tentativeDistance.get(destinationNode);
		if (tentativeDistance.get(destinationNode) < std::numeric_limits<int>::max()) {
			int currentNode = destinationNode;
			while (currentNode != -1) {
				path.addStart(currentNode);
				currentNode = previousHop.get(currentNode);
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
