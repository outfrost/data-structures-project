//
// Created by outfrost on 04/04/17.
//

#include "BinaryHeapElement.h"

template<typename T>
class BinaryHeapElement {

private:
	int key;
	T value;
	
public:
	BinaryHeapElement(int const key) {
		this->key = key;
		this->value = nullptr;
	}
	
	BinaryHeapElement(int const key, T const value) {
		this->key = key;
		this->value = value;
	}
	
	int getKey() {
		return this->key;
	}
	
	T getValue() {
		return this->value;
	}
	
	T setValue(T const value) {
		this->value = value;
	}
};