//
// Created by outfrost on 03/04/17.
//

#include "List.h"

template<typename T>
class List {

public:
	virtual unsigned int getSize();
	virtual T get(unsigned int index);
	virtual bool contains(T const value);
	virtual void add(T const value, unsigned int index);
	virtual void add(T const value);
	virtual void remove(T const value);
	
	unsigned int toStringLines(std::string ** out) {
		delete [] out;
		out = new std::string * [this->getSize() + 1];
		out[0] = new std::string("size: " + this->getSize());
		for (unsigned int i = 0u; i < this->getSize(); i++) {
			out[i+1] = new std::string("[");
			*(out[i+1]) += i;
			*(out[i+1]) += "]: \t";
			*(out[i+1]) += this->get(i);
		}
		return this->getSize() + 1;
	}
};