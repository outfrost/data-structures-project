#ifndef DATA_STRUCTURES_PROJECT_TIME_MEASUREMENT_H
#define DATA_STRUCTURES_PROJECT_TIME_MEASUREMENT_H

#include <chrono>
inline long long int nanoseconds(std::chrono::time_point<std::chrono::high_resolution_clock> & since, std::chrono::time_point<std::chrono::high_resolution_clock> & until);

#endif //DATA_STRUCTURES_PROJECT_TIME_MEASUREMENT_H
