#include <chrono>

inline long long int nanoseconds(std::chrono::time_point<std::chrono::high_resolution_clock> & since, std::chrono::time_point<std::chrono::high_resolution_clock> & until) {
	return std::chrono::duration_cast<std::chrono::nanoseconds>(until - since).count();
}

