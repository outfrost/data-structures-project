#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include "../common/string_consts.h"
#include "../common/getValueFromString.h"
#include "../common/time_measurement.h"
#include "IncidenceMatrixGraph.h"
#include "LinkedGraph.h"
#include "../basic-structures/DummyList.cpp"
#include "graphs.h"

namespace graphs {
	
	void program() {
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
					} else if (choice == '2') {
						promptGraphGenerationParams(incidenceMatrixGraph, linkedGraph);
					} else if (choice == '3') {
						printGraphs(incidenceMatrixGraph, linkedGraph);
					} else if (choice == '4') {
						findMstPrim(incidenceMatrixGraph, linkedGraph);
					} else if (choice == '5') {
						findMstKruskal(incidenceMatrixGraph, linkedGraph);
					} else if (choice == '6') {
						findPathDijkstra(incidenceMatrixGraph, linkedGraph);
					} else if (choice == '7') {
						findPathBellman(incidenceMatrixGraph, linkedGraph);
					}
				}
			} else if (choice == 'F' || choice == 'f') {
				benchmark();
			} else if (choice == 'Z' || choice == 'z') {
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
			*choice = (char) std::cin.get();
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
			*choice = (char) std::cin.get();
		} while (*choice == '\n');
	}
	
	void buildGraphsFromFile(Graph& graph1, Graph& graph2) {
		graph1.clear();
		graph2.clear();
		
		int nodeCount = 0;
		int edgeCount = 0;
		std::ifstream* file = openStreamForReading();
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
	
	void promptGraphGenerationParams(Graph& graph1, Graph& graph2) {
		std::cout << STR_LANG_ENTER_NODE_CT << ": ";
		int nodeCount = 0;
		std::scanf("%d", &nodeCount);
		if (nodeCount > 0) {
			std::cout << STR_LANG_ENTER_DENSITY << ": ";
			int densityPercentage = 0;
			std::scanf("%d", &densityPercentage);
			if (densityPercentage >= 0 && densityPercentage <= 100) {
				generateRandomGraphs(graph1, graph2, nodeCount, densityPercentage);
			}
			else {
				std::cerr << STR_EX_INVALID_PERCENTAGE << "\n";
			}
		} else
			std::cout << STR_LANG_GEN_RAND_ZERO_SIZE << "\n";
	}
	
	void generateRandomGraphs(Graph& graph1, Graph& graph2, int nodeCount, int densityPercentage) {
		if (nodeCount > 0 && densityPercentage >= 0 && densityPercentage <= 100) {
			graph1.clear();
			graph2.clear();
			graph1.addNodes(nodeCount);
			graph2.addNodes(nodeCount);
			
			std::random_device randomDevice;
			std::mt19937 mt = std::mt19937(randomDevice());
			std::uniform_int_distribution<int> nodeDist = std::uniform_int_distribution<int>(0, nodeCount - 1);
			std::bernoulli_distribution directionDist = std::bernoulli_distribution();
			std::uniform_int_distribution<int> metricDist = std::uniform_int_distribution<int>(1, MAX_RANDOM_METRIC);
			/*
			 * This part guarantees that we generate a connected graph
			 */
			ArrayList<bool> nodeIncluded(nodeCount, false);
			nodeIncluded.set(nodeDist(mt), true);
			
			for (int i = 1; i < nodeCount; i++) {
				int node = nodeDist(mt);
				while (nodeIncluded.get(node)) {
					node = nodeDist(mt);
				}
				int connectionNode = nodeDist(mt);
				while (!nodeIncluded.get(connectionNode)) {
					connectionNode = nodeDist(mt);
				}
				nodeIncluded.set(node, true);
				if (directionDist(mt)) {
					std::swap(node, connectionNode);
				}
				int metric = metricDist(mt);
				graph1.addEdge(node, connectionNode, metric);
				graph2.addEdge(node, connectionNode, metric);
			}
			/***/
			double initialDensity = ((double)nodeCount - 1.0) / (((double)nodeCount - 1.0) * (double)nodeCount);
			double probability = (((double) densityPercentage / 100.0) - initialDensity) / (1.0 - initialDensity);
			if (densityPercentage > 0) {
				std::bernoulli_distribution boolDist = std::bernoulli_distribution(probability);
				
				for (int i = 0; i < nodeCount; i++) {
					for (int k = 0; k < nodeCount; k++) {
						if (k != i
								&& !graph2.containsEdge(i, k)
								&& boolDist(mt)) {
							int metric = metricDist(mt);
							graph1.addEdge(i, k, metric);
							graph2.addEdge(i, k, metric);
						}
					}
				}
			}
		}
	}
	
	void printGraphs(Graph& graph1, Graph& graph2) {
		std::cout << graph1.toString() << "\n" << graph2.toString() << "\n";
	}
	
	void findMstPrim(Graph& graph1, Graph& graph2) {
		Graph* mst = graph1.findMstPrim();
		std::cout << mst->toString();
		std::cout << "Total edge metric: " << mst->totalEdgeMetric() << "\n\n";
		delete mst;
		mst = graph2.findMstPrim();
		std::cout << mst->toString();
		std::cout << "Total edge metric: " << mst->totalEdgeMetric() << "\n\n";
		delete mst;
	}
	
	void findMstKruskal(Graph& graph1, Graph& graph2) {
		Graph* mst = graph1.findMstKruskal();
		std::cout << mst->toString();
		std::cout << "Total edge metric: " << mst->totalEdgeMetric() << "\n\n";
		delete mst;
		mst = graph2.findMstKruskal();
		std::cout << mst->toString();
		std::cout << "Total edge metric: " << mst->totalEdgeMetric() << "\n\n";
		delete mst;
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
		} else {
			std::cout << "graph1: " << STR_LANG_PATH_NOT_FOUND << "\n";
		}
		path = LinkedList<int>();
		if (graph2.findPathDijkstra(startingNode, destinationNode, distance, path)) {
			std::cout << "graph2: " << STR_LANG_PATH_FOUND_PRE << distance << STR_LANG_PATH_FOUND_AFT;
			std::cout << "graph2: ";
			path.print();
		} else {
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
		} else {
			std::cout << "graph1: " << STR_LANG_PATH_NOT_FOUND << "\n";
		}
		path = LinkedList<int>();
		if (graph2.findPathBellman(startingNode, destinationNode, distance, path)) {
			std::cout << "graph2: " << STR_LANG_PATH_FOUND_PRE << distance << STR_LANG_PATH_FOUND_AFT;
			std::cout << "graph2: ";
			path.print();
		} else {
			std::cout << "graph2: " << STR_LANG_PATH_NOT_FOUND << "\n";
		}
	}
	
	void benchmark() {
		std::ofstream* resultStream = openStreamForWriting();
		*resultStream << "node_count,"
				<< "density,"
				<< "im_prim,"
				<< "im_kruskal,"
				<< "im_dijkstra,"
				<< "im_bellman,"
				<< "al_prim,"
				<< "al_kruskal,"
				<< "al_dijkstra,"
				<< "al_bellman"
				<< "\n";
		resultStream->flush();
		
		int count = MAX_GENERATED_NODES;
		
		for (int i = 0; i < 5 && count > 0; i++, count >>= 1) {
			for (int i = 0; i < MEASUREMENT_PASSES; i++) {
				IncidenceMatrixGraph incidenceMatrixGraph = IncidenceMatrixGraph();
				LinkedGraph linkedGraph = LinkedGraph();
				
				std::random_device randomDevice;
				std::mt19937 mt(randomDevice());
				std::uniform_int_distribution<int> nodeDist(0, count - 1);
				
				std::chrono::time_point<std::chrono::high_resolution_clock> timeBefore;
				std::chrono::time_point<std::chrono::high_resolution_clock> timeAfter;
				
				int density[4] = {25, 50, 75, 99};
				for (int k = 0; k < 4; k++) {
					std::cout << STR_LANG_GEN_GRAPH_PRE << count << STR_LANG_GEN_GRAPH_AFT;
					std::cout << STR_LANG_GRAPH_DENSITY_PRE << density[k] << STR_LANG_GRAPH_DENSITY_AFT;
					generateRandomGraphs(incidenceMatrixGraph, linkedGraph, count, density[k]);
					
					std::cout << STR_LANG_MEASURING_PRE << i + 1 << STR_LANG_MEASUGING_AFT;
					
					int pathStartingNode = nodeDist(mt);
					int pathDestinationNode = pathStartingNode;
					while (pathDestinationNode == pathStartingNode) {
						pathDestinationNode = nodeDist(mt);
					}
					int pathDistance;
					DummyList<int> path = DummyList<int>();
					
					*resultStream << count << "," << density[k] << ",";
					
					timeBefore = std::chrono::high_resolution_clock::now();
					incidenceMatrixGraph.findMstPrim();
					timeAfter = std::chrono::high_resolution_clock::now();
					*resultStream << nanoseconds(timeBefore, timeAfter) << ",";
					
					timeBefore = std::chrono::high_resolution_clock::now();
					incidenceMatrixGraph.findMstKruskal();
					timeAfter = std::chrono::high_resolution_clock::now();
					*resultStream << nanoseconds(timeBefore, timeAfter) << ",";
					
					timeBefore = std::chrono::high_resolution_clock::now();
					incidenceMatrixGraph.findPathDijkstra(pathStartingNode, pathDestinationNode, pathDistance, path);
					timeAfter = std::chrono::high_resolution_clock::now();
					*resultStream << nanoseconds(timeBefore, timeAfter) << ",";
					
					timeBefore = std::chrono::high_resolution_clock::now();
					incidenceMatrixGraph.findPathBellman(pathStartingNode, pathDestinationNode, pathDistance, path);
					timeAfter = std::chrono::high_resolution_clock::now();
					*resultStream << nanoseconds(timeBefore, timeAfter) << ",";
					
					timeBefore = std::chrono::high_resolution_clock::now();
					linkedGraph.findMstPrim();
					timeAfter = std::chrono::high_resolution_clock::now();
					*resultStream << nanoseconds(timeBefore, timeAfter) << ",";
					
					timeBefore = std::chrono::high_resolution_clock::now();
					linkedGraph.findMstKruskal();
					timeAfter = std::chrono::high_resolution_clock::now();
					*resultStream << nanoseconds(timeBefore, timeAfter) << ",";
					
					timeBefore = std::chrono::high_resolution_clock::now();
					linkedGraph.findPathDijkstra(pathStartingNode, pathDestinationNode, pathDistance, path);
					timeAfter = std::chrono::high_resolution_clock::now();
					*resultStream << nanoseconds(timeBefore, timeAfter) << ",";
					
					timeBefore = std::chrono::high_resolution_clock::now();
					linkedGraph.findPathBellman(pathStartingNode, pathDestinationNode, pathDistance, path);
					timeAfter = std::chrono::high_resolution_clock::now();
					*resultStream << nanoseconds(timeBefore, timeAfter) << "\n";
					
					resultStream->flush();
				}
			}
		}
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
	
}
