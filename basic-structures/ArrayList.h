#ifndef DATA_STRUCTURES_PROJECT_ARRAY_H
#define DATA_STRUCTURES_PROJECT_ARRAY_H


template<typename T>
class ArrayList : public List<T> {

private:
	T *array;
	unsigned int size;

public:
	ArrayList();
	
	unsigned int getSize() override;
	T get(unsigned int index) override;
	bool contains(T const value) override;
	void add(T const value, unsigned int index) override;
	void add(T const value) override;
	void addStart(T const value) override;
	void addEnd(T const value) override;
	void removeAt(unsigned int index) override;
	void removeFirst() override;
	void removeLast() override;
	void remove(T const value) override;
	void print() override;

};

#endif //DATA_STRUCTURES_PROJECT_ARRAY_H
