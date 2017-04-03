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
	LinkedListElement(T value) {
		this->value = value;
		this->previous = nullptr;
		this->next = nullptr;
	}
	
	LinkedListElement(T value, LinkedListElement * previous, LinkedListElement * next) {
		this->value = value;
		this->previous = previous;
		this->next = next;
	}
	
	
};