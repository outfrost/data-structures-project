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
