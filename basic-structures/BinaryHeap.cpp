#include <iostream>
#include <stdexcept>
#include "../common/string_consts.h"
#include "BinaryHeapElement.cpp"
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
		this->allocatedSize = BINARYHEAP_TARGET_OVERHEAD;
		this->array = new BinaryHeapElement<T> * [allocatedSize];
	}
	
	unsigned int getSize() {
		return this->size;
	}
	
	bool get(int key, T * const dest) {
		BinaryHeapElement<T> * found = find(key);
		if (found != nullptr) {
			*dest = found->getValue();
			return true;
		}
		else
			return false;
	}
	
	bool contains(int key) {
		return find(key) != nullptr;
	}
	
	void add(int key, T const value) {
		BinaryHeapElement<T> * newElement = new BinaryHeapElement<T>(key, value, this->size);
		this->array[this->size] = newElement;
		this->size++;
		fixFromLeaf(this->size - 1);
		checkAllocation();
	}
	
	void remove(int key) {
		BinaryHeapElement<T> * found = find(key);
		if (found != nullptr)
			removeAt(found->getIndex());
	}
	
	void remove() {
		if (getSize() > 0u)
			removeAt(0u);
		else
			throw new std::out_of_range(STR_EX_BINARYHEAP_EMPTY);
	}
	
	T pop() {
		if (this->size > 0u) {
			T rootValue = this->array[0u]->getValue();
			remove();
			return rootValue;
		}
		else
			throw new std::out_of_range(STR_EX_BINARYHEAP_EMPTY);
	}
	
	void print() {
		printSubtree();
		for (unsigned int i = 0u; i < this->size; i++)
			std::cout << this->array[i]->getKey() << " ";
		std::cout << "\n";
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
	
	void removeAt(unsigned int index) {
		if (index < this->size) {
			this->size--;
			swapElements(index, this->size);
			if (index < this->size)
				fixFromRoot(index);
			checkAllocation();
		}
		else
			throw new std::out_of_range(STR_EX_INDEX_OUT_OF_BOUNDS);
	}
	
	void checkAllocation() {
		if (this->allocatedSize - this->size < BINARYHEAP_MIN_OVERHEAD || this->allocatedSize - this->size > BINARYHEAP_MAX_OVERHEAD) {
			this->allocatedSize = this->size + BINARYHEAP_TARGET_OVERHEAD;
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
			bool fixed = false;
			while (!fixed) {
				if (getLeftChildIndex(index) < this->size) {
					if (getRightChildIndex(index) < this->size) {
						if (this->array[index]->getKey() < this->array[getLeftChildIndex(index)]->getKey()
						    || this->array[index]->getKey() < this->array[getRightChildIndex(index)]->getKey()) {
							unsigned int swapIndex = this->array[getLeftChildIndex(index)]->getKey() > this->array[getRightChildIndex(index)]->getKey() ? getLeftChildIndex(index) : getRightChildIndex(index);
							swapElements(index, swapIndex);
							index = swapIndex;
						}
						else
							fixed = true;
					}
					else if (this->array[index]->getKey() < this->array[getLeftChildIndex(index)]->getKey()) {
						swapElements(index, getLeftChildIndex(index));
						index = getLeftChildIndex(index);
					}
					else
						fixed = true;
				}
				else
					fixed = true;
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
	
	void printSubtree(unsigned int index = 0u, unsigned int level = 0u) {
		if (index < this->size) {
			printSubtree(getLeftChildIndex(index), level+1);
			if (level) {
				for (unsigned int i = level - 1; i > 0u; i--)
					std::printf("|       ");
				std::printf("|-----• ");
			}
			std::printf("%d\n", this->array[index]->getKey());
			printSubtree(getRightChildIndex(index), level+1);
		}
	}
};