//
// Created by outfrost on 03/04/17.
//

#include "BinaryHeap.h"

template<typename T>
class BinaryHeap {

private:
	T *array;
	unsigned int size;
	unsigned int allocatedSize;
	
public:
	BinaryHeap() {
		this->size = 0;
		this->allocatedSize = BINARYHEAP_MAX_OVERHEAD;
		this->array = new T[allocatedSize];
	}
	
	unsigned int getSize() {
		return this->size;
	}
	
	T get(unsigned int index) {
		if (index < this->size)
			return this->array[index];
		else
			throw new std::out_of_range(STR_EX_INDEX_OUT_OF_BOUNDS);
	}
	
	bool contains(T const value) {
		for (unsigned int i = 0; i < this->size; i++) {
			if (this->array[i] == value)
				return true;
		}
		return false;
	}
};