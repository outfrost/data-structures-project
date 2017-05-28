#ifndef DATA_STRUCTURES_PROJECT_LIST_H
#define DATA_STRUCTURES_PROJECT_LIST_H

template<typename T>
class List {

public:
	
	virtual unsigned int getSize() = 0;
	virtual T get(unsigned int index) = 0;
	virtual bool contains(T const value) = 0;
	virtual void add(T const value, unsigned int index) = 0;
	virtual void add(T const value) = 0;
	virtual void removeAt(unsigned int index) = 0;
	virtual void remove(T const value) = 0;
	virtual void print() = 0;
	
};

#endif //DATA_STRUCTURES_PROJECT_LIST_H
