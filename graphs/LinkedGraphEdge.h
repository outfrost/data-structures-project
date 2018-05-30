#ifndef DATA_STRUCTURES_PROJECT_LINKEDGRAPHEDGE_H
#define DATA_STRUCTURES_PROJECT_LINKEDGRAPHEDGE_H


class LinkedGraphEdge {

public:
	int originNode;
	int destinationNode;
	int metric;
	
	LinkedGraphEdge() = default;
	LinkedGraphEdge(int origin, int destination, int metric);
	~LinkedGraphEdge() = default;
	
};


#endif //DATA_STRUCTURES_PROJECT_LINKEDGRAPHEDGE_H
