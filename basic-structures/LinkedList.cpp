#include <cstdio>
#include <stdexcept>
#include <string>
#include "List.cpp"
#include "LinkedListElement.cpp"
#include "../common/string_consts.h"
#include "LinkedList.h"

template<typename T>
class LinkedList : public List<T> {

private:
	LinkedListElement<T> * firstElement;
	LinkedListElement<T> * lastElement;
	unsigned int size;
	
public:
	LinkedList() {
		this->size = 0u;
		this->firstElement = nullptr;
		this->lastElement = nullptr;
	}
	
	unsigned int getSize() override {
		return this->size;
	}
	
	T get(unsigned int index) override {
		if (index < this->size) {
			if (index <= this->size >> 1) {
				LinkedListElement<T> *elementPointer = this->firstElement;
				for (unsigned int i = 0u; i < index; i++)
					elementPointer = elementPointer->getNextElement();
				return elementPointer->getValue();
			}
			else {
				LinkedListElement<T> *elementPointer = this->lastElement;
				for (unsigned int i = this->size - 1; i > index; i--)
					elementPointer = elementPointer->getPreviousElement();
				return elementPointer->getValue();
			}
		}
		else
			throw std::out_of_range(STR_EX_INDEX_OUT_OF_BOUNDS);
	}
	
	bool contains(T const value) override {
		LinkedListElement<T> *elementPointer = firstElement;
		for (unsigned int i = 0u; i < this->size; i++) {
			if (elementPointer->getValue() == value)
				return true;
			elementPointer = elementPointer->getNextElement();
		}
		return false;
	}
	
	void add(T const value, unsigned int index) override {
		if (index <= this->size) {
			LinkedListElement<T> *newElement = new LinkedListElement<T>(value);
			if (index == 0u) {
				newElement->setNextElement(this->firstElement);
				if (this->firstElement != nullptr)
					this->firstElement->setPreviousElement(newElement);
				else
					this->lastElement = newElement;
				this->firstElement = newElement;
			}
			else {
				LinkedListElement<T> *elementBefore;
				if (index <= this->size >> 1) {
					elementBefore = this->firstElement;
					for (unsigned int i = 1u; i < index; i++)
						elementBefore = elementBefore->getNextElement();
				}
				else {
					elementBefore = this->lastElement;
					for (unsigned int i = this->size; i > index; i--)
						elementBefore = elementBefore->getPreviousElement();
				}
				LinkedListElement<T> *elementAfter = elementBefore->getNextElement();
				newElement->setPreviousElement(elementBefore);
				newElement->setNextElement(elementAfter);
				elementBefore->setNextElement(newElement);
				if (elementAfter != nullptr)
					elementAfter->setPreviousElement(newElement);
				else
					this->lastElement = newElement;
			}
			this->size++;
		}
		else
			throw std::out_of_range(STR_EX_INDEX_OUT_OF_BOUNDS);
	}
	
	void add(T const value) override {
		LinkedListElement<T> *newElement = new LinkedListElement<T>(value, this->lastElement, nullptr);
		if (this->lastElement != nullptr)
			this->lastElement->setNextElement(newElement);
		else
			this->firstElement = newElement;
		this->lastElement = newElement;
		this->size++;
	}
	
	void addStart(T const value) override {
		add(value, 0u);
	}
	
	void addEnd(T const value) override {
		add(value);
	}
	
	void removeAt(unsigned int index) override {
		if (index < this->size) {
			LinkedListElement<T> *elementPointer;
			if (index <= this->size >> 1) {
				elementPointer = this->firstElement;
				for (unsigned int i = 0u; i < index; i++)
					elementPointer = elementPointer->getNextElement();
			}
			else {
				elementPointer = this->lastElement;
				for (unsigned int i = this->size - 1; i > index; i--)
					elementPointer = elementPointer->getPreviousElement();
			}
			remove(elementPointer);
		}
		else
			throw std::out_of_range(STR_EX_INDEX_OUT_OF_BOUNDS);
	}
	
	void removeFirst() override {
		if (getSize() > 0)
			remove(this->firstElement);
		else
			throw std::out_of_range(STR_EX_LINKEDLIST_EMPTY);
	}
	
	void removeLast() override {
		if (getSize() > 0)
			remove(this->lastElement);
		else
			throw std::out_of_range(STR_EX_LINKEDLIST_EMPTY);
	}
	
	void remove(T const value) override {
		LinkedListElement<T> *elementPointer = this->firstElement;
		for (unsigned int i = 0u; i < this->size; i++) {
			if (elementPointer->getValue() == value) {
				remove(elementPointer);
				return;
			}
			elementPointer = elementPointer->getNextElement();
		}
	}
	
	void print() override {
		LinkedListElement<T> *element = this->firstElement;
		for (unsigned int i = 0u; i < this->size; i++) {
			std::printf("%s ", std::to_string(element->getValue()).c_str());
			element = element->getNextElement();
		}
		std::printf("\n");
		element = this->lastElement;
		for (unsigned int i = 0u; i < this->size; i++) {
			std::printf("%s ", std::to_string(element->getValue()).c_str());
			element = element->getPreviousElement();
		}
		std::printf("\n");
	}

protected:
	void remove(LinkedListElement<T> * element) {
		LinkedListElement<T> *elementBefore = element->getPreviousElement();
		LinkedListElement<T> *elementAfter = element->getNextElement();
		if (elementBefore != nullptr)
			elementBefore->setNextElement(elementAfter);
		else
			this->firstElement = elementAfter;
		if (elementAfter != nullptr)
			elementAfter->setPreviousElement(elementBefore);
		else
			this->lastElement = elementBefore;
		delete element;
		this->size--;
	}
};
/*
void LinkedList<LinkedGraphEdge>::print() {
	LinkedListElement<LinkedGraphEdge> *element = this->firstElement;
	for (unsigned int i = 0u; i < this->size; i++) {
		std::cout << element->toString() << " ";
		element = element->getNextElement();
	}
	std::cout << "\n";
}
*/
