//
// Created by outfrost on 02/04/17.
//

#include "Array.h"

template<typename T>
class Array {

private:
	T *array;
	unsigned int size;

public:
	Array() {
		this->size = 0;
		this->array = new T[size];
	}
	
	Array(unsigned int size) {
		this->size = size;
		this->array = new T[size];
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
		T * newArray = new T[++this->size];
		for (unsigned int i = 0; i < this->size; i++) {
			if (i < index)
				newArray[i] = this->array[i];
			else {
				if (i == index)
					newArray[i] = value;
				else
					newArray[i] = this->array[i-1];
			}
		}
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
	
	unsigned int toStringLines(std::string ** out) {
		delete [] out;
		out = new std::string * [this->size+1];
		out[0] = new std::string("size: " + this->size);
		for (unsigned int i = 0; i < this->size; i++) {
			out[i+1] = new std::string("[");
			*(out[i+1]) += i;
			*(out[i+1]) += "]: \t";
			*(out[i+1]) += this->array[i];
		}
		return this->size + 1;
	}
};