#ifndef DATA_STRUCTURES_PROJECT_GRAPHS_H
#define DATA_STRUCTURES_PROJECT_GRAPHS_H

#include "Graph.h"

void graphs();
void readMainMenuChoice(char* choice);
void readStructureMenuChoice(char* choice, const std::string& structureName);
void buildGraphsFromFile(Graph& graph1, Graph& graph2);
std::ifstream* openStreamForReading();
std::ofstream* openStreamForWriting();

#endif //DATA_STRUCTURES_PROJECT_GRAPHS_H
