#ifndef DATA_STRUCTURES_PROJECT_BASIC_STRUCTURES_H
#define DATA_STRUCTURES_PROJECT_BASIC_STRUCTURES_H

#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

#define MAX_GENERATED_DATA 1 << 8
#define MEASUREMENT_PASSES 128

namespace basic_structures {
	
	int program();
	void readStructureMenuChoice(char* choice, const std::string& structureName);
	std::ifstream* openStreamForReading();
	std::ofstream* openStreamForWriting();
	
}

#endif //DATA_STRUCTURES_PROJECT_BASIC_STRUCTURES_H
