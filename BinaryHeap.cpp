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
	
	bool contains(int key) {
		return find(key) != nullptr;
	}
	
	void add(BinaryHeapElement<T> * element) {
		this->array[this->size++] = element;
		fixFromLeaf(this->size - 1);
		checkAllocation();
	}
	
	void removeAt(unsigned int index) {
		if (index < this->size) {
			swapElements(index, --this->size);
			fixFromRoot()
			
			checkAllocation();
		}
		else
			throw new std::out_of_range(STR_EX_INDEX_OUT_OF_BOUNDS);
	}
	
	void remove(int key) {
		BinaryHeapElement<T> * found = find(key);
		if (found != nullptr)
			removeAt(found->getIndex());
	}
	
protected:
	BinaryHeapElement<T> * find(int key, unsigned int startingIndex = 0u) {
		if (startingIndex < this->size) {
			BinaryHeapElement<T> * found = nullptr;
			if (this->array[startingIndex]->getKey() == key)
				found = this->array[startingIndex];
			else if (this->array[startingIndex]->getKey() > key && getLeftChildIndex(startingIndex) < this->size) {
				found = find(key, getLeftChildIndex(startingIndex));
				if (found == nullptr && getRightChildIndex(startingIndex) < this->size)
					found = find(key, getRightChildIndex(startingIndex));
			}
			return found;
		}
		else
			throw new std::out_of_range(STR_EX_INDEX_OUT_OF_BOUNDS);
	}
	
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
	
	void fixFromRoot(unsigned int index) {
		if (index < this->size) {
			while (getLeftChildIndex(index) < this->size
			       && (this->array[index]->getKey() < this->array[getLeftChildIndex(index)]
			           || (getRightChildIndex(index) < this->size
			               && this->array[index]->getKey() < this->array[getRightChildIndex(index)]))) {
				swapElements(index, )
			}
		}
		else
			throw new std::out_of_range(STR_EX_INDEX_OUT_OF_BOUNDS);
	}
	
	void swapElements(unsigned int index1, unsigned int index2) {
		BinaryHeapElement<T> * node = this->array[index1];
		this->array[index1] = this->array[index2];
		this->array[index2] = node;
		array[index1]->setIndex(index1);
		array[index2]->setIndex(index2);
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