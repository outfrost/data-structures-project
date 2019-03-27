#include <sstream>
#include <limits>
#include "LinkedGraph.h"

LinkedGraph::LinkedGraph(int nodeCount) {
	addNodes(nodeCount);
}

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

int LinkedGraph::totalEdgeMetric() {
	int result = 0;
	for (unsigned int i = 0; i < nodes->getSize(); i++) {
		for (unsigned int k = 0; k < nodes->get(i)->getSize(); k++) {
			result += nodes->get(i)->get(k)->metric;
		}
	}
	result >>= 1;
	return result;
}

bool LinkedGraph::containsEdge(int from, int to) {
	if (from < nodes->getSize() && to < nodes->getSize()
			&& from >= 0 && to >= 0
			&& from != to) {
		List<LinkedGraphEdge*>* adjacencyList = nodes->get((unsigned int)from);
		for (int i = 0; i < adjacencyList->getSize(); i++) {
			if (adjacencyList->get((unsigned int)i)->originNode == to
					|| adjacencyList->get((unsigned int)i)->destinationNode == to) {
				return true;
			}
		}
	}
	return false;
}

Graph* LinkedGraph::findMstPrim() {
	Graph* result = new LinkedGraph(nodes->getSize());
	ArrayList<bool> nodeIncluded(nodes->getSize(), false);
	
	ArrayList<int> cheapestConnectionMetric(nodes->getSize(), std::numeric_limits<int>::max());
	ArrayList<LinkedGraphEdge*> cheapestConnectionEdge(nodes->getSize(), nullptr);
	
	int currentNode = 0;
	for (int nodesRemaining = nodes->getSize(); nodesRemaining > 0 && currentNode != -1; nodesRemaining--) {
		nodeIncluded.set(currentNode, true);
		if (cheapestConnectionEdge.get(currentNode) != nullptr) {
			LinkedGraphEdge* edge = cheapestConnectionEdge.get(currentNode);
			result->addEdge(edge->originNode, edge->destinationNode, edge->metric);
		}
		
		for (int i = 0; i < nodes->get((unsigned int)currentNode)->getSize(); i++) {
			LinkedGraphEdge* edge = nodes->get((unsigned int)currentNode)->get((unsigned int)i);
			if (edge->originNode == currentNode
					&& !nodeIncluded.get(edge->destinationNode)
					&& edge->metric < cheapestConnectionMetric.get(edge->destinationNode)) {
				cheapestConnectionMetric.set(edge->destinationNode, edge->metric);
				cheapestConnectionEdge.set(edge->destinationNode, edge);
			}
			else if (edge->destinationNode == currentNode
					&& !nodeIncluded.get(edge->originNode)
					&& edge->metric < cheapestConnectionMetric.get(edge->originNode)) {
				cheapestConnectionMetric.set(edge->originNode, edge->metric);
				cheapestConnectionEdge.set(edge->originNode, edge);
			}
		}
		
		int lowestMetric = std::numeric_limits<int>::max();
		int lowestMetricNode = -1;
		for (int i = 0; i < nodes->getSize(); i++) {
			if (!nodeIncluded.get(i) && cheapestConnectionMetric.get(i) < lowestMetric) {
				lowestMetric = cheapestConnectionMetric.get(i);
				lowestMetricNode = i;
			}
		}
		currentNode = lowestMetricNode;
	}
	return result;
}

Graph* LinkedGraph::findMstKruskal() {
	Graph* result = new LinkedGraph(nodes->getSize());
	ArrayList<int> treeId(nodes->getSize());
	for (int i = 0; i < treeId.getSize(); i++) {
		treeId.set(i, i);
	}
	int trees = nodes->getSize();
	LinkedList<LinkedGraphEdge*> remainingEdges = LinkedList<LinkedGraphEdge*>();
	for (int i = 0; i < nodes->getSize(); i++) {
		for (int k = 0; k < nodes->get((unsigned int)i)->getSize(); k++) {
			if (!remainingEdges.contains(nodes->get((unsigned int)i)->get((unsigned int)k))) {
				remainingEdges.add(nodes->get((unsigned int) i)->get((unsigned int) k));
			}
		}
	}
	
	while (trees > 1 && remainingEdges.getSize() > 0) {
		int lowestMetric = std::numeric_limits<int>::max();
		LinkedGraphEdge* lowestMetricEdge = nullptr;
		
		for (int i = 0; i < remainingEdges.getSize(); i++) {
			LinkedGraphEdge* edge = remainingEdges.get((unsigned int)i);
			if (edge->metric < lowestMetric) {
				lowestMetric = edge->metric;
				lowestMetricEdge = edge;
			}
		}
		
		if (lowestMetricEdge != nullptr) {
			remainingEdges.remove(lowestMetricEdge);
			if (treeId.get(lowestMetricEdge->originNode) != treeId.get(lowestMetricEdge->destinationNode)) {
				result->addEdge(lowestMetricEdge->originNode, lowestMetricEdge->destinationNode, lowestMetricEdge->metric);
				int mergedTreeId = treeId.get(lowestMetricEdge->destinationNode);
				for (int i = 0; i < treeId.getSize(); i++) {
					if (treeId.get(i) == mergedTreeId) {
						treeId.set(i, treeId.get(lowestMetricEdge->originNode));
					}
				}
				--trees;
			}
		}
	}
	return result;
}

bool LinkedGraph::findPathDijkstra(int startingNode, int destinationNode, int& distance, List<int>& path) {
	if (startingNode < nodes->getSize() && destinationNode < nodes->getSize()
	        && startingNode >= 0 && destinationNode >= 0) {
		ArrayList<bool> visited(nodes->getSize(), false);
		ArrayList<int> tentativeDistance(nodes->getSize(), std::numeric_limits<int>::max());
		ArrayList<int> previousHop(nodes->getSize(), -1);
		
		tentativeDistance.set(startingNode, 0);
		int currentNode = startingNode;
		
		while (currentNode != destinationNode && !visited.get(destinationNode)
		       && currentNode != -1) {
			for (int i = 0; i < nodes->get((unsigned int)currentNode)->getSize(); i++) {
				LinkedGraphEdge* currentEdge = nodes->get((unsigned int)currentNode)->get((unsigned int)i);
				if (!visited.get(currentEdge->destinationNode)) {
					if (tentativeDistance.get(currentNode) + currentEdge->metric
						    < tentativeDistance.get(currentEdge->destinationNode)) {
						tentativeDistance.set(currentEdge->destinationNode,
								tentativeDistance.get(currentNode) + currentEdge->metric);
						previousHop.set(currentEdge->destinationNode, currentNode);
					}
				}
			}
			visited.set(currentNode, true);
			
			int smallestTentativeDistance = std::numeric_limits<int>::max();
			int nodeWithSmallestDistance = -1;
			for (int i = 0; i < nodes->getSize(); i++) {
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

bool LinkedGraph::findPathBellman(int startingNode, int destinationNode, int& distance, List<int>& path) {
	if (startingNode < nodes->getSize() && destinationNode < nodes->getSize()
	        && startingNode >= 0 && destinationNode >= 0) {
		ArrayList<int> tentativeDistance(nodes->getSize(), std::numeric_limits<int>::max());
		ArrayList<int> previousHop(nodes->getSize(), -1);
		
		tentativeDistance.set(startingNode, 0);
		
		for (int i = 0; i < nodes->getSize() - 1; i++) {
			for (int k = 0; k < nodes->getSize(); k++) {
				for (int l = 0; l < nodes->get((unsigned int)k)->getSize(); l++) {
					LinkedGraphEdge* edge = nodes->get((unsigned int)k)->get((unsigned int)l);
					if (k == edge->originNode) {
						if (tentativeDistance.get(edge->originNode) < std::numeric_limits<int>::max()) {
							if (tentativeDistance.get(edge->originNode) + edge->metric
									< tentativeDistance.get(edge->destinationNode)) {
								tentativeDistance.set(edge->destinationNode,
										tentativeDistance.get(edge->originNode) + edge->metric);
								previousHop.set(edge->destinationNode, edge->originNode);
							}
						}
					}
				}
			}
		}
		
		for (int k = 0; k < nodes->getSize(); k++) {
			for (int l = 0; l < nodes->get((unsigned int)k)->getSize(); l++) {
				LinkedGraphEdge* edge = nodes->get((unsigned int)k)->get((unsigned int)l);
				if (k == edge->originNode) {
					if (tentativeDistance.get(edge->originNode) < std::numeric_limits<int>::max()) {
						if (tentativeDistance.get(edge->originNode) + edge->metric
						        < tentativeDistance.get(edge->destinationNode)) {
							return false; // TODO Handle problems better maybe™?
						}
					}
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
