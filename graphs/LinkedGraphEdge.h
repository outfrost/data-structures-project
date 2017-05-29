#ifndef DATA_STRUCTURES_PROJECT_LINKEDGRAPHEDGE_H
#define DATA_STRUCTURES_PROJECT_LINKEDGRAPHEDGE_H
#include "LinkedGraphNode.h"

class LinkedGraphEdge {

private:
	LinkedGraphNode * connectedNode;
	int metric;
	
public:
	LinkedGraphEdge(LinkedGraphNode * connectedNode, int metric);
	~LinkedGraphEdge();
	
	LinkedGraphNode * getConnectedNode();
	void setConnectedNode(LinkedGraphNode * node);
	int getMetric();
	void setMetric(int metric);
};


#endif //DATA_STRUCTURES_PROJECT_LINKEDGRAPHEDGE_H
