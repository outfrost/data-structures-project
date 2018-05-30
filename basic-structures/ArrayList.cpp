#include <cstdio>
#include <stdexcept>
#include <string>
#include "../common/string_consts.h"
#include "List.cpp"
#include "ArrayList.h"

template<typename T>
class ArrayList : public List<T> {

private:
	T *array;
	unsigned int size;

public:
	ArrayList() {
		this->size = 0u;
		this->array = new T[size];
	}
	
	/* ArrayList(unsigned int size) {
		this->size = size;
		this->array = new T[size];
	}
	*/
	
	unsigned int getSize() override {
		return this->size;
	}
	
	T get(unsigned int index) override {
		if (index < this->size)
			return this->array[index];
		else
			throw std::out_of_range(STR_EX_INDEX_OUT_OF_BOUNDS);
	}
	
	bool contains(T const value) override {
		for (unsigned int i = 0u; i < this->size; i++) {
			if (this->array[i] == value)
				return true;
		}
		return false;
	}
	
	void add(T const value, unsigned int index) override {
		if (index <= this->size) {
			T *newArray = new T[++this->size];
			for (unsigned int i = 0u; i < this->size; i++) {
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
			throw std::out_of_range(STR_EX_INDEX_OUT_OF_BOUNDS);
	}
	
	void add(T const value) override {
		T *newArray = new T[++this->size];
		for (unsigned int i = 0u; i < this->size; i++)
			newArray[i] = this->array[i];
		newArray[this->size - 1] = value;
		delete [] this->array;
		this->array = newArray;
	}
	
	void addStart(T const value) override {
		add(value, 0u);
	}
	
	void addEnd(T const value) override {
		add(value);
	}
	
	void removeAt(unsigned int index) override {
		if (index < this->size) {
			T *newArray = new T[--this->size];
			for (unsigned int i = 0u; i < this->size; i++) {
				if (i < index)
					newArray[i] = this->array[i];
				else
					newArray[i] = this->array[i + 1];
			}
			delete[] this->array;
			this->array = newArray;
		}
		else
			throw std::out_of_range(STR_EX_INDEX_OUT_OF_BOUNDS);
	}
	
	void removeFirst() override {
		removeAt(0u);
	}
	
	void removeLast() override {
		removeAt(getSize() - 1);
	}
	
	void remove(T const value) override {
		for (unsigned int i = 0u; i < this->size; i++) {
			if (this->array[i] == value) {
				removeAt(i);
				return;
			}
		}
	}
	
	void print() override {
/*		for (unsigned int i = 0u; i < this->size; i++)
			std::printf("%s ", std::to_string(this->array[i]).c_str());
		std::printf("\n");
*/	}
};
