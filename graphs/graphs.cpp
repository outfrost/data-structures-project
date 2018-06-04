#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include "../common/string_consts.h"
#include "../common/getValueFromString.h"
#include "../common/time_measurement.h"
#include "graphs.h"
#include "IncidenceMatrixGraph.h"
#include "LinkedGraph.h"

void graphs() {
	char choice = '\0';
	while (choice != '0') {
		readMainMenuChoice(&choice);
		if (choice == '1') {
			IncidenceMatrixGraph incidenceMatrixGraph = IncidenceMatrixGraph();
			LinkedGraph linkedGraph = LinkedGraph();
			
			char choice = '\0';
			while (choice != '0') {
				readStructureMenuChoice(&choice, "Graph");
				if (choice == '1') {
					buildGraphsFromFile(incidenceMatrixGraph, linkedGraph);
				}
				else if (choice == '2') {
					generateRandomGraphs(incidenceMatrixGraph, linkedGraph);
				}
				else if (choice == '3') {
					printGraphs(incidenceMatrixGraph, linkedGraph);
				}
				else if (choice == '4') {
					findMstPrim(incidenceMatrixGraph, linkedGraph);
				}
				else if (choice == '5') {
					findMstKruskal(incidenceMatrixGraph, linkedGraph);
				}
				else if (choice == '6') {
					findPathDijkstra(incidenceMatrixGraph, linkedGraph);
				}
				else if (choice == '7') {
					findPathBellman(incidenceMatrixGraph, linkedGraph);
				}
			}
		}
		else if (choice == 'F' || choice == 'f') {
			benchmark();
		}
		else if (choice == 'Z' || choice == 'z') {
			debugTest();
		}
	}
}

void readMainMenuChoice(char* choice) {
	std::cout << "# " << STR_LANG_MAINMENU << " #\n";
	std::cout << "---\n";
	std::cout << "1. " << STR_LANG_GRAPH << "\n";
	std::cout << "---\n";
	std::cout << "F. " << STR_LANG_TIME_MEASUREMENT << "\n";
	std::cout << "---\n";
	std::cout << "0. " << STR_LANG_QUIT << "\n";
	std::cout << "(graphs) ";
	do {
		*choice = (char)std::cin.get();
	} while (*choice == '\n');
}

void readStructureMenuChoice(char* choice, const std::string& structureName) {
	std::cout << "# " << structureName << " #\n";
	std::cout << "---\n";
	std::cout << "1. " << STR_LANG_STRUCTURE_FROM_FILE << "\n";
	std::cout << "2. " << STR_LANG_GEN_RAND_STRUCTURE << "\n";
	std::cout << "3. " << STR_LANG_PRINT_STRUCTURE << "\n";
	std::cout << "---\n";
	std::cout << "4. " << STR_LANG_MST_PRIM << "\n";
	std::cout << "5. " << STR_LANG_MST_KRUSKAL << "\n";
	std::cout << "6. " << STR_LANG_PATH_DIJKSTRA << "\n";
	std::cout << "7. " << STR_LANG_PATH_BELLMAN << "\n";
	std::cout << "---\n";
	std::cout << "0. " << STR_LANG_BACKTOMAIN << "\n";
	std::cout << "(" << structureName << ") ";
	do {
		*choice = (char)std::cin.get();
	} while (*choice == '\n');
}

void buildGraphsFromFile(Graph& graph1, Graph& graph2) {
	graph1.clear();
	graph2.clear();
	
	int nodeCount = 0;
	int edgeCount = 0;
	std::ifstream * file = openStreamForReading();
	std::string word;
	
	bool success = true;
	*file >> word;
	success &= getValueFromString<int>(word, edgeCount);
	if (!success) {
		std::cerr << STR_LANG_ERR_BUILDING_FROM_FILE << "\n";
		return;
	}
	*file >> word;
	success &= getValueFromString<int>(word, nodeCount);
	if (!success) {
		std::cerr << STR_LANG_ERR_BUILDING_FROM_FILE << "\n";
		return;
	}
	
	graph1.addNodes(nodeCount);
	graph2.addNodes(nodeCount);
	
	for (int i = 0; i < edgeCount; i++) {
		int origin;
		int destination;
		int metric;
		*file >> word;
		success &= getValueFromString<int>(word, origin);
		if (!success) {
			std::cerr << STR_LANG_ERR_BUILDING_FROM_FILE << "\n";
			return;
		}
		*file >> word;
		success &= getValueFromString<int>(word, destination);
		if (!success) {
			std::cerr << STR_LANG_ERR_BUILDING_FROM_FILE << "\n";
			return;
		}
		*file >> word;
		success &= getValueFromString<int>(word, metric);
		if (!success) {
			std::cerr << STR_LANG_ERR_BUILDING_FROM_FILE << "\n";
			return;
		}
		graph1.addEdge(origin, destination, metric);
		graph2.addEdge(origin, destination, metric);
	}
}

void generateRandomGraphs(Graph& graph1, Graph& graph2) {
	std::cout << STR_LANG_ENTER_NODE_CT << ": ";
	int nodeCount = 0;
	std::scanf("%d", &nodeCount);
	if(nodeCount > 0) {
		graph1.clear();
		graph2.clear();
		graph1.addNodes(nodeCount);
		graph2.addNodes(nodeCount);
		
		std::cout << STR_LANG_ENTER_DENSITY << ": ";
		int densityPercentage = 0;
		std::scanf("%d", &densityPercentage);
		
		if (densityPercentage > 0) {
			std::random_device randomDevice;
			std::mt19937 mt = std::mt19937(randomDevice());
			std::bernoulli_distribution boolDist = std::bernoulli_distribution((double) densityPercentage / 100.0);
			std::uniform_int_distribution<int> metricDist = std::uniform_int_distribution<int>(1, MAX_RANDOM_METRIC);
			
			for (int i = 0; i < nodeCount; i++) {
				for (int k = 0; k < nodeCount; k++) {
					if (k != i) {
						if (boolDist(mt)) {
							int metric = metricDist(mt);
							graph1.addEdge(i, k, metric);
							graph2.addEdge(i, k, metric);
						}
					}
				}
			}
		}
	}
	else
		std::cout << STR_LANG_GEN_RAND_ZERO_SIZE << "\n";
}

void printGraphs(Graph& graph1, Graph& graph2) {

	std::cout << graph1.toString() << "\n" << graph2.toString() << "\n";
}

void findMstPrim(Graph& graph1, Graph& graph2) {
	Graph* mst = graph1.findMstPrim();
	std::cout << mst->toString() << "\n";
	delete mst;
	mst = graph2.findMstPrim();
	std::cout << mst->toString() << "\n";
	delete mst;
}

void findMstKruskal(Graph& graph1, Graph& graph2) {

}

void findPathDijkstra(Graph& graph1, Graph& graph2) {
	std::cout << STR_LANG_ENTER_START_NODE << ": ";
	int startingNode = 0;
	std::scanf("%d", &startingNode);
	std::cout << STR_LANG_ENTER_DEST_NODE << ": ";
	int destinationNode = 0;
	std::scanf("%d", &destinationNode);
	
	int distance;
	LinkedList<int> path = LinkedList<int>();
	if (graph1.findPathDijkstra(startingNode, destinationNode, distance, path)) {
		std::cout << "graph1: " << STR_LANG_PATH_FOUND_PRE << distance << STR_LANG_PATH_FOUND_AFT;
		std::cout << "graph1: ";
		path.print();
	}
	else {
		std::cout << "graph1: " << STR_LANG_PATH_NOT_FOUND << "\n";
	}
	path = LinkedList<int>();
	if (graph2.findPathDijkstra(startingNode, destinationNode, distance, path)) {
		std::cout << "graph2: " << STR_LANG_PATH_FOUND_PRE << distance << STR_LANG_PATH_FOUND_AFT;
		std::cout << "graph2: ";
		path.print();
	}
	else {
		std::cout << "graph2: " << STR_LANG_PATH_NOT_FOUND << "\n";
	}
}

void findPathBellman(Graph& graph1, Graph& graph2) {
	std::cout << STR_LANG_ENTER_START_NODE << ": ";
	int startingNode = 0;
	std::scanf("%d", &startingNode);
	std::cout << STR_LANG_ENTER_DEST_NODE << ": ";
	int destinationNode = 0;
	std::scanf("%d", &destinationNode);
	
	int distance;
	LinkedList<int> path = LinkedList<int>();
	if (graph1.findPathBellman(startingNode, destinationNode, distance, path)) {
		std::cout << "graph1: " << STR_LANG_PATH_FOUND_PRE << distance << STR_LANG_PATH_FOUND_AFT;
		std::cout << "graph1: ";
		path.print();
	}
	else {
		std::cout << "graph1: " << STR_LANG_PATH_NOT_FOUND << "\n";
	}
	path = LinkedList<int>();
	if (graph2.findPathBellman(startingNode, destinationNode, distance, path)) {
		std::cout << "graph2: " << STR_LANG_PATH_FOUND_PRE << distance << STR_LANG_PATH_FOUND_AFT;
		std::cout << "graph2: ";
		path.print();
	}
	else {
		std::cout << "graph2: " << STR_LANG_PATH_NOT_FOUND << "\n";
	}
}

void benchmark() {
	std::ofstream* resultStream = openStreamForWriting();
	
	resultStream->close();
	delete resultStream;
}

void debugTest() {

}

std::ifstream* openStreamForReading() {
	std::cin.ignore();
	std::cout << STR_LANG_ENTER_FILENAME << ": ";
	std::string filename;
	std::getline(std::cin, filename);
	return new std::ifstream(filename);
}

std::ofstream* openStreamForWriting() {
	std::cin.ignore();
	std::cout << STR_LANG_ENTER_FILENAME_RESULTS << ": ";
	std::string filename;
	std::getline(std::cin, filename);
	return new std::ofstream(filename);
}
