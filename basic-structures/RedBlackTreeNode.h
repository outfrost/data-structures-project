#ifndef DATA_STRUCTURES_PROJECT_REDBLACKTREENODE_H
#define DATA_STRUCTURES_PROJECT_REDBLACKTREENODE_H

#include "BinarySearchTreeNode.cpp"

template<typename T>
class RedBlackTreeNode {

private:
	int key;
	T value;
	bool red;
	RedBlackTreeNode<T>* leftChild;
	RedBlackTreeNode<T>* rightChild;
	RedBlackTreeNode<T>* parent;
	
public:
	RedBlackTreeNode(int key, T value) {
		this->key = key;
		this->value = value;
		this->red = false;
		this->leftChild = nullptr;
		this->rightChild = nullptr;
		this->parent = nullptr;
	}
	
	RedBlackTreeNode(int key, T value, bool red) {
		this->key = key;
		this->value = value;
		this->red = red;
		this->leftChild = nullptr;
		this->rightChild = nullptr;
		this->parent = nullptr;
	}
	
	RedBlackTreeNode(int key, T value, bool red, RedBlackTreeNode<T>* leftChild, RedBlackTreeNode<T>* rightChild, RedBlackTreeNode<T>* parent) {
		this->key = key;
		this->value = value;
		this->red = red;
		this->leftChild = leftChild;
		this->rightChild = rightChild;
		this->parent = parent;
	}
	
	int getKey() {
		return key;
	}
	
	T getValue() {
		return value;
	}
	
	bool isRed() {
		return red;
	}
	
	RedBlackTreeNode<T>* getLeftChild() {
		return leftChild;
	}
	
	RedBlackTreeNode<T>* getRightChild() {
		return rightChild;
	}
	
	RedBlackTreeNode<T>* getParent() {
		return parent;
	}
	
	void setRed(bool red) {
		this->red = red;
	}
	
	void setLeftChild(RedBlackTreeNode<T>* leftChild) {
		this->leftChild = leftChild;
	}
	
	void setRightChild(RedBlackTreeNode<T>* rightChild) {
		this->rightChild = rightChild;
	}
	
	void setParent(RedBlackTreeNode<T>* parent) {
		this->parent = parent;
	}
	
};


#endif //DATA_STRUCTURES_PROJECT_REDBLACKTREENODE_H
