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
			bool added = false;
			while (!added) {
				if (parent->getKey() >= key) {
					if (parent->getLeftChild() == nullptr) {
						parent->setLeftChild(newNode);
						newNode->setParent(parent);
						added = true;
					}
					else
						parent = parent->getLeftChild();
				}
				else {
					if (parent->getRightChild() == nullptr) {
						parent->setRightChild(newNode);
						newNode->setParent(parent);
						added = true;
					}
					else
						parent = parent->getRightChild();
				}
			}
		}
	}
	
	void remove(int key) {
		BinarySearchTreeNode<T> * nodeToRemove = find(key);
		if (nodeToRemove != nullptr) {
			BinarySearchTreeNode<T> * nodeToSubstitute = nullptr;
			
			if (nodeToRemove->getLeftChild() == nullptr)
				nodeToSubstitute = nodeToRemove->getRightChild();
			else if (nodeToRemove->getRightChild() == nullptr)
				nodeToSubstitute = nodeToRemove->getLeftChild();
			else {
				nodeToSubstitute = findSuccessor(nodeToRemove);
				if (nodeToSubstitute->getParent() != nullptr) {
					if (nodeToSubstitute->getParent()->getLeftChild() == nodeToSubstitute)
						nodeToSubstitute->getParent()->setLeftChild(nodeToSubstitute->getRightChild());
					else
						nodeToSubstitute->getParent()->setRightChild(nodeToSubstitute->getRightChild());
					
					if (nodeToSubstitute->getRightChild() != nullptr)
						nodeToSubstitute->getRightChild()->setParent(nodeToSubstitute->getParent());
				}
			}
			
			if (nodeToSubstitute != nullptr)
				nodeToSubstitute->setParent(nodeToRemove->getParent());
			if (nodeToRemove->getParent() != nullptr) {
				if (nodeToRemove->getParent()->getLeftChild() == nodeToRemove)
					nodeToRemove->getParent()->setLeftChild(nodeToSubstitute);
				else
					nodeToRemove->getParent()->setRightChild(nodeToSubstitute);
			}
		}
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