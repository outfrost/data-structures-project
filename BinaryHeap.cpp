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
		this->size = 0u;
		this->allocatedSize = BINARYHEAP_TARGET_OVERHEADu;
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
	
	}
	
	void add(T const value) {
		this->array[this->size++] = value;
		fixFromLeaf(this->size - 1);
		checkAllocation();
	}
	
protected:
	void checkAllocation() {
		if (this->allocatedSize - this->size < BINARYHEAP_MIN_OVERHEADu || this->allocatedSize - this->size > BINARYHEAP_MAX_OVERHEADu) {
			this->allocatedSize = this->size + BINARYHEAP_TARGET_OVERHEADu;
			T *newArray = new T[allocatedSize];
			for (unsigned int i = 0; i < this->size; i++)
				newArray[i] = this->array[i];
			delete [] this->array;
			this->array = newArray;
		}
	}
	
	void fixFromLeaf(unsigned int index) {
		if (index < this->size) {
			while (this->array[index] > this->array[getParentIndex(index)]) {
				swapValues(index, getParentIndex(index));
				index = getParentIndex(index);
			}
		}
		else
			throw new std::out_of_range(STR_EX_INDEX_OUT_OF_BOUNDS);
	}
	
	void swapValues(unsigned int index1, unsigned int index2) {
		T nodeValue = this->array[index1];
		this->array[index1] = this->array[index2];
		this->array[index2] = nodeValue;
	}
	
	unsigned int * getIndex(T const value) {
		unsigned int index =
		
	}
	
	static inline unsigned int getParentIndex(unsigned int index) {
		return index > 0u ? (index - 1) >> 1 : 0u;
	}
	
	static inline unsigned int getLeftChildIndex(unsigned int index) {
		return (index << 1) + 1;
	}
	
	static inline unsigned int getRightChildIndex(unsigned int index) {
		return (index << 1) + 2;
	}
	
	static inline bool isLeftChild(unsigned int index) {
		return index & 1u;
	}
};