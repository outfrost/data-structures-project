//
// Created by outfrost on 04/04/17.
//

#include "BinaryHeapElement.h"

template<typename T>
class BinaryHeapElement {

private:
	int key;
	T value;
	unsigned int index;
	
public:
	BinaryHeapElement(int key, T const value, unsigned int index = 0u) {
		this->key = key;
		this->value = value;
		this->index = index;
	}
	
	int getKey() {
		return this->key;
	}
	
	T getValue() {
		return this->value;
	}
	
	unsigned int getIndex() {
		return this->index;
	}
	
	void setIndex(unsigned int index) {
		this->index = index;
	}
};