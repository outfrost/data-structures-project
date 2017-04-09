//
// Created by outfrost on 09/04/17.
//

#include "BinarySearchTreeNode.h"

template<typename T>
class BinarySearchTreeNode {

private:
	int key;
	T value;
	BinarySearchTreeNode<T> * leftChild;
	BinarySearchTreeNode<T> * rightChild;
	
public:
	BinarySearchTreeNode(int key, T value) {
		this->key = key;
		this->value = value;
		this->leftChild = nullptr;
		this->rightChild = nullptr;
	}
	
	BinarySearchTreeNode(int key, T value, BinarySearchTreeNode<T> * leftChild, BinarySearchTreeNode<T> * rightChild) {
		this->key = key;
		this->value = value;
		this->leftChild = leftChild;
		this->rightChild = rightChild;
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
	
	void setLeftChild(BinarySearchTreeNode<T> * leftChild) {
		this->leftChild = leftChild;
	}
	
	void setRightChild(BinarySearchTreeNode<T> * rightChild) {
		this->rightChild = rightChild;
	}
};