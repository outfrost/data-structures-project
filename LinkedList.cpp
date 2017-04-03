//
// Created by outfrost on 03/04/17.
//

#include "LinkedList.h"

template<typename T>
class LinkedList : public List<T> {

private:
	LinkedListElement<T> * firstElement;
	LinkedListElement<T> * lastElement;
	unsigned int size;
	
public:
	LinkedList() {
		this->size = 0;
		this->firstElement = nullptr;
		this->lastElement = nullptr;
	}
	
	unsigned int getSize() {
		return this->size;
	}
	
	T get(unsigned int index) {
		if (index < this->size) {
			if (index <= size / 2) {
				LinkedListElement<T> *elementPointer = this->firstElement;
				for (unsigned int i = 0; i < index; i++)
					elementPointer = elementPointer->getNextElement();
				return elementPointer->getValue();
			}
			else {
				LinkedListElement<T> *elementPointer = this->lastElement;
				for (unsigned int i = this->size - 1; i > index; i++)
					elementPointer = elementPointer->getPreviousElement();
				return elementPointer->getValue();
			}
		}
		else
			throw new std::out_of_range(STR_EX_INDEX_OUT_OF_BOUNDS);
	}
	
	bool contains(T const value) {
		LinkedListElement<T> *elementPointer = firstElement;
		for (unsigned int i = 0; i < this->size; i++) {
			if (elementPointer->getValue() == value)
				return true;
		}
		return false;
	}
	
	void add(T const value, unsigned int index) {
		if (index <= this->size) {
			LinkedListElement<T> *newElement = new LinkedListElement<>(value);
			if (index == 0) {
				newElement->setNextElement(this->firstElement);
				if (this->firstElement != nullptr)
					this->firstElement->setPreviousElement(newElement);
				else
					this->lastElement = newElement;
				this->firstElement = newElement;
			}
			else {
				LinkedListElement<T> *elementBefore;
				if (index <= size / 2) {
					elementBefore = this->firstElement;
					for (unsigned int i = 1; i < index; i++)
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
			throw new std::out_of_range(STR_EX_INDEX_OUT_OF_BOUNDS);
	}
	
	void add(T const value) {
		LinkedListElement<T> *newElement = new LinkedListElement<>(value, this->lastElement, nullptr);
		if (this->lastElement != nullptr)
			this->lastElement->setNextElement(newElement);
		else
			this->firstElement = newElement;
		this->lastElement = newElement;
		this->size++;
	}
	
	void remove(T const value) {
		LinkedListElement<T> *elementPointer = this->firstElement;
		for (unsigned int i = 0; i < this->size; i++) {
			if (elementPointer->getValue() == value) {
				LinkedListElement<T> *elementBefore = elementPointer->getPreviousElement();
				LinkedListElement<T> *elementAfter = elementPointer->getNextElement();
				if (elementBefore != nullptr)
					elementBefore->setNextElement(elementAfter);
				else
					this->firstElement = elementAfter;
				if (elementAfter != nullptr)
					elementAfter->setPreviousElement(elementBefore);
				else
					this->lastElement = elementBefore;
				delete elementPointer;
				return;
			}
			elementPointer = elementPointer->getNextElement();
		}
	}
};