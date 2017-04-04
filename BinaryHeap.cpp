//
// Created by outfrost on 03/04/17.
//

#include "BinaryHeap.h"

template<typename T>
class BinaryHeap {

private:
	BinaryHeapElement<T> **array;
	unsigned int size;
	unsigned int allocatedSize;
	
public:
	BinaryHeap() {
		this->size = 0u;
		this->allocatedSize = BINARYHEAP_TARGET_OVERHEADu;
		this->array = new BinaryHeapElement<T> * [allocatedSize];
	}
	
	unsigned int getSize() {
		return this->size;
	}
	
	BinaryHeapElement<T> * get(unsigned int index) {
		if (index < this->size)
			return this->array[index];
		else
			throw new std::out_of_range(STR_EX_INDEX_OUT_OF_BOUNDS);
	}
	
	bool contains(int key, unsigned int startingIndex = 0u) {
		if (startingIndex < this->size) {
			if (this->array[startingIndex]->getKey() == key)
				return true;
			else if (this->array[startingIndex]->getKey() > key) {
				if (getLeftChildIndex(startingIndex) < this->size) {
					if (contains(key, getLeftChildIndex(startingIndex)))
						return true;
					else if (getRightChildIndex(startingIndex) < this->size)
						return contains(key, getRightChildIndex(startingIndex));
					else
						return false;
				}
				else
					return false;
			}
			else
				return false;
		}
		else
			throw new std::out_of_range(STR_EX_INDEX_OUT_OF_BOUNDS);
	}
	
	void add(BinaryHeapElement<T> * element) {
		this->array[this->size++] = element;
		fixFromLeaf(this->size - 1);
		checkAllocation();
	}
	
protected:
	void checkAllocation() {
		if (this->allocatedSize - this->size < BINARYHEAP_MIN_OVERHEADu || this->allocatedSize - this->size > BINARYHEAP_MAX_OVERHEADu) {
			this->allocatedSize = this->size + BINARYHEAP_TARGET_OVERHEADu;
			BinaryHeapElement<T> **newArray = new BinaryHeapElement<T> * [allocatedSize];
			for (unsigned int i = 0; i < this->size; i++)
				newArray[i] = this->array[i];
			delete [] this->array;
			this->array = newArray;
		}
	}
	
	void fixFromLeaf(unsigned int index) {
		if (index < this->size) {
			while (this->array[index]->getKey() > this->array[getParentIndex(index)]->getKey()) {
				swapElements(index, getParentIndex(index));
				index = getParentIndex(index);
			}
		}
		else
			throw new std::out_of_range(STR_EX_INDEX_OUT_OF_BOUNDS);
	}
	
	void swapElements(unsigned int index1, unsigned int index2) {
		BinaryHeapElement<T> * node = this->array[index1];
		this->array[index1] = this->array[index2];
		this->array[index2] = node;
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