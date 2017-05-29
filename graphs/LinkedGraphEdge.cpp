#include "LinkedGraphEdge.h"

LinkedGraphEdge::LinkedGraphEdge(LinkedGraphNode *connectedNode, int metric) {
	this->connectedNode = connectedNode;
	this->metric = metric;
}

LinkedGraphEdge::~LinkedGraphEdge() {}

LinkedGraphNode *LinkedGraphEdge::getConnectedNode() {
	return this->connectedNode;
}

void LinkedGraphEdge::setConnectedNode(LinkedGraphNode *node) {
	this->connectedNode = node;
}

int LinkedGraphEdge::getMetric() {
	return this->metric;
}

void LinkedGraphEdge::setMetric(int metric) {
	this->metric = metric;
}
