#ifndef DATA_STRUCTURES_PROJECT_MAIN_H
#define DATA_STRUCTURES_PROJECT_MAIN_H

#define MAX_GENERATED_DATA 1 << 12
#define MEASUREMENT_PASSES 128

int main(int argc, char **argv);
inline long long int nanoseconds(std::chrono::time_point<std::chrono::high_resolution_clock> & since, std::chrono::time_point<std::chrono::high_resolution_clock> & until);
void readStructureMenuChoice(char * choice, const std::string & structureName);
std::ifstream * openStreamForReading();
std::ofstream * openStreamForWriting();

#endif //DATA_STRUCTURES_PROJECT_MAIN_H
