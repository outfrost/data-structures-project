#ifndef DATA_STRUCTURES_PROJECT_MATRIXGRAPH_H
#define DATA_STRUCTURES_PROJECT_MATRIXGRAPH_H


class MatrixGraph {

private:
	int **neighbourMatrix;
	int nodeCount;
	static const int nullEdge = std::numeric_limits<int>::min();
	
public:
	MatrixGraph();
	MatrixGraph(int nodeCount);
	
	int getEdgeMetric(int fromNode, int toNode);
	void setEdgeMetric(int fromNode, int toNode, int metric, bool bidirectional);
	void removeEdge(int fromNode, int toNode, bool bidirectional = true);
	
	void addNodes(int count);
	void clear();
	void print();
};


#endif //DATA_STRUCTURES_PROJECT_MATRIXGRAPH_H
