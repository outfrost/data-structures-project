#include <iostream>
#include <sstream>
#include <cstdio>
#include "BinarySearchTreeNode.cpp"
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
		// balance();
	}
	
	void remove(int key) {
		BinarySearchTreeNode<T> * nodeToRemove = find(key);         // Find node with the requested key
		if (nodeToRemove != nullptr) {                              // if we found something (it's not null):
			BinarySearchTreeNode<T> * nodeToSubstitute = nullptr;
			
			if (nodeToRemove->getLeftChild() == nullptr)            // if nodeToRemove doesn't have a left child:
				nodeToSubstitute = nodeToRemove->getRightChild();      // use the right child as nodeToSubstitute
			else if (nodeToRemove->getRightChild() == nullptr)      // if nodeToRemove doesn't have a right child:
				nodeToSubstitute = nodeToRemove->getLeftChild();        // use the left child as nodeToSubstitute
			else {                                                  // Otherwise (nodeToRemove has both children):
				nodeToSubstitute = findSuccessor(nodeToRemove);         // Find nodeToRemove's successor in the tree and use it as nodeToSubstitute
				// nullcheck not necessary, because a successor is guaranteed to be present and guaranteed to be in nodeToRemove's right child's subtree
				if (nodeToSubstitute == nodeToRemove->getRightChild()) {
					nodeToSubstitute->setLeftChild(nodeToRemove->getLeftChild());
					// nullcheck not necessary, because we've determined that nodeToRemove has a left child
					nodeToRemove->getLeftChild()->setParent(nodeToSubstitute);
				}
				else {
					if (nodeToSubstitute->getParent()->getLeftChild() == nodeToSubstitute)              // if the successor is the left child of its parent:
						nodeToSubstitute->getParent()->setLeftChild(nodeToSubstitute->getRightChild());     // Replace the successor with the successor's right child in parent node (as left child)
					else                                                                                // Otherwise (the successor is the right child of its parent):
						nodeToSubstitute->getParent()->setRightChild(nodeToSubstitute->getRightChild());    // Replace the successor with the successor's right child in parent node (as right child)
					
					if (nodeToSubstitute->getRightChild() != nullptr)                                   // if the successor has a right child:
						nodeToSubstitute->getRightChild()->setParent(nodeToSubstitute->getParent());        // Replace the successor with the successor's parent in that right child
					
					nodeToSubstitute->setLeftChild(nodeToRemove->getLeftChild());   // Replace its left child with nodeToRemove's left child
					nodeToSubstitute->setRightChild(nodeToRemove->getRightChild()); // Replace its right child with nodeToRemove's right child
					
					if (nodeToRemove->getLeftChild() != nullptr)                    // if nodeToRemove has a left child (it's not null):
						nodeToRemove->getLeftChild()->setParent(nodeToSubstitute);      // Replace nodeToRemove with nodeToSubstitute in left child (as parent node)
					if (nodeToRemove->getRightChild() != nullptr)                   // if nodeToRemove has a right child (it's not null):
						nodeToRemove->getRightChild()->setParent(nodeToSubstitute);     // Replace nodeToRemove with nodeToSubstitute in right child (as parent node)
				}
			}
			
			if (nodeToSubstitute != nullptr)
				nodeToSubstitute->setParent(nodeToRemove->getParent());
			
			if (nodeToRemove->getParent() != nullptr) {                     // if nodeToRemove has a parent (it's not null):
				if (nodeToRemove->getParent()->getLeftChild() == nodeToRemove)  // if nodeToRemove is the left child of its parent:
					nodeToRemove->getParent()->setLeftChild(nodeToSubstitute);      // Replace nodeToRemove with nodeToSubstitute in parent node (as left child)
				else                                                            // Otherwise (nodeToRemove is the right child of its parent):
					nodeToRemove->getParent()->setRightChild(nodeToSubstitute);     // Replace nodeToRemove with nodeToSubstitute in parent node (as right child)
			}
			else {                                                          // Otherwise (nodeToRemove is the root of the tree):
				this->root = nodeToSubstitute;                                  // Replace nodeToRemove with nodeToSubstitute as root of the tree
			}
			
			delete nodeToRemove;
		}
		// balance();
	}
	
	void balance() {
		std::printf("Not implemented.\n");
	}
	
	void print() {
		printSubtree(this->root);
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
	
	BinarySearchTreeNode<T> * findSuccessor(BinarySearchTreeNode<T> * node) {
		BinarySearchTreeNode<T> * successor = nullptr;
		if (node->getRightChild() != nullptr) {
			successor = node->getRightChild();
			while (successor->getLeftChild() != nullptr)
				successor = successor->getLeftChild();
		}
		else {
			while (successor == nullptr && node->getParent() != nullptr) {
				if (node->getParent()->getLeftChild() == node)
					successor = node->getParent();
				else
					node = node->getParent();
			}
		}
		return successor;
	}
	
	void printSubtree(BinarySearchTreeNode<T> * node, unsigned int level = 0u) {
		if (node != nullptr) {
			printSubtree(node->getLeftChild(), level+1);
			std::stringstream lineStream/*(std::ios_base::in | std::ios_base::out | std::ios_base::app)*/;
			if (level) {
				for (unsigned int i = level - 1; i > 0u; i--)
					lineStream << "|       ";
				lineStream << "|-----o ";
			}
			lineStream << node->getKey() << "\n";
			std::cout << lineStream.rdbuf();
			printSubtree(node->getRightChild(), level+1);
		}
	}
};