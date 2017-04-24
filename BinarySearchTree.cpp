//
// Created by outfrost on 09/04/17.
//

#include "BinarySearchTree.h"

template<typename T>
class BinarySearchTree {

private:
	BinarySearchTreeNode<T> * root;
	
public:
	BinarySearchTree() {
		this->root = nullptr;
	}
	
	bool get(int key, T * const dest) {
		BinarySearchTreeNode<T> * found = find(key);
		if (found != nullptr) {
			*dest = found->getValue();
			return true;
		}
		else
			return false;
	}
	
	bool contains(int key) {
		return find(key) != nullptr;
	}
	
	void add(int key, T const value) {
		BinarySearchTreeNode<T> * newNode = new BinarySearchTreeNode<T>(key, value);
		if (this->root == nullptr)
			this->root = newNode;
		else {
			BinarySearchTreeNode<T> * parent = this->root;
			BinarySearchTreeNode<T> * oldParent = nullptr;
			while (parent != oldParent) {
				oldParent = parent;
				if (parent->getKey() >= key) {
					if (parent->getLeftChild() == nullptr)
						parent->setLeftChild(newNode);
					else
						parent = parent->getLeftChild();
				}
				else {
					if (parent->getRightChild() == nullptr)
						parent->setRightChild(newNode);
					else
						parent = parent->getRightChild();
				}
			}
		}
	}
	
	void remove(int key) {
	
	}
	
protected:
	BinarySearchTreeNode<T> * find(int key) {
		BinarySearchTreeNode<T> * node = root;
		while (node != nullptr && node->getKey() != key) {
			if (node->getKey() > key)
				node = node->getLeftChild();
			else
				node = node->getRightChild();
		}
		return node;
	}
	
	void balance() {
	
	}
};