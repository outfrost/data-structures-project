//
// Created by outfrost on 02/04/17.
//

#include "ArrayList.h"

template<typename T>
class ArrayList : public List<T> {

private:
	T *array;
	unsigned int size;

public:
	ArrayList() {
		this->size = 0;
		this->array = new T[size];
	}
	
	/* ArrayList(unsigned int size) {
		this->size = size;
		this->array = new T[size];
	}
	*/
	
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
	
	void add(T const value, unsigned int index) {
		if (index <= this->size) {
			T *newArray = new T[++this->size];
			for (unsigned int i = 0; i < this->size; i++) {
				if (i < index)
					newArray[i] = this->array[i];
				else {
					if (i == index)
						newArray[i] = value;
					else
						newArray[i] = this->array[i - 1];
				}
			}
			delete[] this->array;
			this->array = newArray;
		}
		else
			throw new std::out_of_range(STR_EX_INDEX_OUT_OF_BOUNDS);
	}
	
	void add(T const value) {
		T *newArray = new T[++this->size];
		for (unsigned int i = 0; i < this->size; i++)
			newArray[i] = this->array[i];
		newArray[this->size - 1] = value;
		delete [] this->array;
		this->array = newArray;
	}
	
	void remove(unsigned int index) {
		if (index < this->size) {
			T *newArray = new T[--this->size];
			for (unsigned int i = 0; i < this->size; i++) {
				if (i < index)
					newArray[i] = this->array[i];
				else
					newArray[i] = this->array[i + 1];
			}
			delete[] this->array;
			this->array = newArray;
		}
		else
			throw new std::out_of_range(STR_EX_INDEX_OUT_OF_BOUNDS);
	}
};