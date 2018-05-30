#ifndef DATA_STRUCTURES_PROJECT_PADSTRING_H
#define DATA_STRUCTURES_PROJECT_PADSTRING_H

#include <string>

std::string padString(const std::string& str, int length, char padCharacter) {
	std::string result = str;
	if (result.length() < length) {
		result.resize(length, padCharacter);
	}
	return result;
}

#endif //DATA_STRUCTURES_PROJECT_PADSTRING_H
