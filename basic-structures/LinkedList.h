#ifndef DATA_STRUCTURES_PROJECT_LINKEDLIST_H
#define DATA_STRUCTURES_PROJECT_LINKEDLIST_H


template<typename T>
class LinkedList : public List<T> {

private:
	LinkedListElement<T> * firstElement;
	LinkedListElement<T> * lastElement;
	unsigned int size;

public:
	LinkedList();
	
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
	void print(bool biDirectional);

protected:
	void remove(LinkedListElement<T>* element);
	
};

#endif //DATA_STRUCTURES_PROJECT_LINKEDLIST_H
