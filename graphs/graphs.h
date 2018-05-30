#ifndef DATA_STRUCTURES_PROJECT_GRAPHS_H
#define DATA_STRUCTURES_PROJECT_GRAPHS_H

#include "Graph.h"

#define MAX_RANDOM_METRIC 1<<9

void graphs();
void readMainMenuChoice(char* choice);
void readStructureMenuChoice(char* choice, const std::string& structureName);
void buildGraphsFromFile(Graph& graph1, Graph& graph2);
void generateRandomGraphs(Graph& graph1, Graph& graph2);
void printGraphs(Graph& graph1, Graph& graph2);
void findMstPrim(Graph& graph1, Graph& graph2);
void findMstKruskal(Graph& graph1, Graph& graph2);
void findPathDijkstra(Graph& graph1, Graph& graph2);
void findPathBellman(Graph& graph1, Graph& graph2);
void benchmark();
void debugTest();
std::ifstream* openStreamForReading();
std::ofstream* openStreamForWriting();

#endif //DATA_STRUCTURES_PROJECT_GRAPHS_H
