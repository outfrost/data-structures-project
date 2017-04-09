//
// Created by outfrost on 03/04/17.
//

#include "LinkedListElement.h"

template <typename T>
class LinkedListElement {

private:
	T value;
	LinkedListElement * previous;
	LinkedListElement * next;
	
public:
	LinkedListElement(T const value) {
		this->value = value;
		this->previous = nullptr;
		this->next = nullptr;
	}
	
	LinkedListElement(T const value, LinkedListElement * previous, LinkedListElement * next) {
		this->value = value;
		this->previous = previous;
		this->next = next;
	}
	
	T getValue() {
		return this->value;
	}
	
	LinkedListElement * getPreviousElement() {
		return this->previous;
	}
	
	LinkedListElement * getNextElement() {
		return this->next;
	}
	
	void setPreviousElement(LinkedListElement * element) {
		this->previous = element;
	}
	
	void setNextElement(LinkedListElement * element) {
		this->next = element;
	}
};