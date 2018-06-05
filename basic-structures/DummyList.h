#ifndef DATA_STRUCTURES_PROJECT_DUMMYLIST_H
#define DATA_STRUCTURES_PROJECT_DUMMYLIST_H


template<typename T>
class DummyList : public List<T> {

public:
	DummyList() = default;
	~DummyList() override = default;
	
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


#endif //DATA_STRUCTURES_PROJECT_DUMMYLIST_H
