#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include "../common/string_consts.h"
#include "../common/getValueFromString.h"
#include "../common/time_measurement.h"
#include "graphs.h"
#include "IncidenceMatrixGraph.h"

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
				
				}
				else if (choice == '3') {
				
				}
				else if (choice == '4') {
				
				}
				else if (choice == '5') {
				
				}
				else if (choice == '6') {
				
				}
				else if (choice == '7') {
				
				}
			}
		}
		else if (choice == 'F' || choice == 'f') {
			std::ofstream* resultStream = openStreamForWriting();
			
			resultStream->close();
			delete resultStream;
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
	std::cout << "7. " << STR_LANG_PATH_SBFM << "\n";
	std::cout << "---\n";
	std::cout << "0. " << STR_LANG_BACKTOMAIN << "\n";
	std::cout << "(" << structureName << ") ";
	do {
		*choice = (char)std::cin.get();
	} while (*choice == '\n');
}

void buildGraphsFromFile(Graph& graph1, Graph& graph2) {

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
