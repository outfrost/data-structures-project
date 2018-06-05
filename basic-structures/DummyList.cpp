#include "List.h"
#include "DummyList.h"

template<typename T>
unsigned int DummyList<T>::getSize() {
	return 0u;
}

template<typename T>
T DummyList<T>::get(unsigned int index) {
	return T{};
}

template<typename T>
bool DummyList<T>::contains(const T value) {
	return false;
}

template<typename T>
void DummyList<T>::add(const T value, unsigned int index) {

}

template<typename T>
void DummyList<T>::add(const T value) {

}

template<typename T>
void DummyList<T>::addStart(const T value) {

}

template<typename T>
void DummyList<T>::addEnd(const T value) {

}

template<typename T>
void DummyList<T>::removeAt(unsigned int index) {

}

template<typename T>
void DummyList<T>::removeFirst() {

}

template<typename T>
void DummyList<T>::removeLast() {

}

template<typename T>
void DummyList<T>::remove(const T value) {

}

template<typename T>
void DummyList<T>::print() {

}
