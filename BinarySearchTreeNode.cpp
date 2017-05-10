#include "BinarySearchTreeNode.h"

template<typename T>
class BinarySearchTreeNode {

private:
	int key;
	T value;
	BinarySearchTreeNode<T> * leftChild;
	BinarySearchTreeNode<T> * rightChild;
	BinarySearchTreeNode<T> * parent;
	
public:
	BinarySearchTreeNode(int key, T value) {
		this->key = key;
		this->value = value;
		this->leftChild = nullptr;
		this->rightChild = nullptr;
		this->parent = nullptr;
	}
	
	BinarySearchTreeNode(int key, T value, BinarySearchTreeNode<T> * leftChild, BinarySearchTreeNode<T> * rightChild, BinarySearchTreeNode<T> * parent) {
		this->key = key;
		this->value = value;
		this->leftChild = leftChild;
		this->rightChild = rightChild;
		this->parent = parent;
	}
	
	int getKey() {
		return this->key;
	}
	
	T getValue() {
		return this->value;
	}
	
	BinarySearchTreeNode<T> * getLeftChild() {
		return this->leftChild;
	}
	
	BinarySearchTreeNode<T> * getRightChild() {
		return this->rightChild;
	}
	
	BinarySearchTreeNode<T> * getParent() {
		return this->parent;
	}
	
	void setLeftChild(BinarySearchTreeNode<T> * leftChild) {
		this->leftChild = leftChild;
	}
	
	void setRightChild(BinarySearchTreeNode<T> * rightChild) {
		this->rightChild = rightChild;
	}
	
	void setParent(BinarySearchTreeNode<T> * parent) {
		this->parent = parent;
	}
};