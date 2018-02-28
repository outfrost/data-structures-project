#ifndef DATA_STRUCTURES_PROJECT_GETVALUEFROMSTRING_H
#define DATA_STRUCTURES_PROJECT_GETVALUEFROMSTRING_H

//
// Sdra @ Stack Overflow
//

#include <sstream>
// Convert string values into type T results.
// Returns false in case the conversion fails.
template <typename T>
bool getValueFromString( const std::string & value, T & result )
{
	std::istringstream iss( value );
	return !( iss >> result ).fail();
}

#endif //DATA_STRUCTURES_PROJECT_GETVALUEFROMSTRING_H
