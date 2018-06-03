#include <sstream>
#include <limits>
#include "LinkedGraph.h"

void LinkedGraph::addNodes(int count) {
	for (int i = 0; i < count; i++) {
		nodes->add(new LinkedList<LinkedGraphEdge*>());
	}
}

void LinkedGraph::addEdge(int origin, int destination, int metric) {
	if (origin < nodes->getSize() && destination < nodes->getSize()
	    && origin >= 0 && destination >= 0 && metric > 0) {
		LinkedGraphEdge* edge = new LinkedGraphEdge(origin, destination, metric);
		nodes->get((unsigned int)origin)->add(edge);
		nodes->get((unsigned int)destination)->add(edge);
	}
}

void LinkedGraph::clear() {
	for (int i = 0; i < nodes->getSize(); i++) {
		delete nodes->get((unsigned int)i);
	}
	delete nodes;
	nodes = new ArrayList<LinkedList<LinkedGraphEdge*>*>();
}

std::string LinkedGraph::toString() {
	std::stringstream stringStream;
	for (int i = 0; i < nodes->getSize(); i++) {
		stringStream << std::to_string(i) << " : ";
		for (int k = 0; k < nodes->get(i)->getSize(); k++) {
			if (k > 0) {
				stringStream << ", ";
			}
			stringStream << "{";
			stringStream << std::to_string(nodes->get(i)->get(k)->originNode);
			stringStream << "->";
			stringStream << std::to_string(nodes->get(i)->get(k)->destinationNode);
			stringStream << ", ";
			stringStream << std::to_string(nodes->get(i)->get(k)->metric);
			stringStream << "}";
		}
		stringStream << "\n";
	}
	stringStream.flush();
	return stringStream.str();
}

bool LinkedGraph::findPathDijkstra(int startingNode, int destinationNode, int& distance, List<int>& path) {
	if (startingNode < nodes->getSize() && destinationNode < nodes->getSize()
	        && startingNode >= 0 && destinationNode >= 0) {
		bool visited[nodes->getSize()] = {}; // { false ... }
		int tentativeDistance[nodes->getSize()];
		std::fill_n(tentativeDistance, nodes->getSize(), std::numeric_limits<int>::max());
		int previousHop[nodes->getSize()];
		std::fill_n(previousHop, nodes->getSize(), -1);
		
		tentativeDistance[startingNode] = 0;
		int currentNode = startingNode;
		
		while (currentNode != destinationNode && !visited[destinationNode]
		       && currentNode != -1) {
			for (int i = 0; i < nodes->get((unsigned int)currentNode)->getSize(); i++) {
				LinkedGraphEdge* currentEdge = nodes->get((unsigned int)currentNode)->get((unsigned int)i);
				if (!visited[currentEdge->destinationNode]) {
					if (tentativeDistance[currentNode] + currentEdge->metric
						    < tentativeDistance[currentEdge->destinationNode]) {
						tentativeDistance[currentEdge->destinationNode] =
								tentativeDistance[currentNode] + currentEdge->metric;
						previousHop[currentEdge->destinationNode] = currentNode;
					}
				}
			}
			visited[currentNode] = true;
			
			int smallestTentativeDistance = std::numeric_limits<int>::max();
			int nodeWithSmallestDistance = -1;
			for (int i = 0; i < nodes->getSize(); i++) {
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

bool LinkedGraph::findPathBellman(int startingNode, int destinationNode, int& distance, List<int>& path) {
	return false;
}
