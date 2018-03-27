#include <iostream>
#include <sstream>
#include "RedBlackTree.h"

template<typename T>
bool RedBlackTree::get(int key, T *const dest) {
	RedBlackTreeNode<T>* found = find(key);
	if (found != nullptr) {
		*dest = found->getValue();
		return true;
	}
	else
		return false;
}

bool RedBlackTree::contains(int key) {
	return find(key) != nullptr;
}

template<typename T>
void RedBlackTree::add(int key, const T value) {
	RedBlackTreeNode<T>* newNode = new RedBlackTreeNode<T>(key, value);
	if (this->root == nullptr)
		this->root = newNode;
	else {
		RedBlackTreeNode<T>* parent = this->root;
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
	if (newNode->getParent() == nullptr) {
		newNode->setRed(false);
	} else if (findUncle(newNode) != nullptr) {
		insert_case3(n);
	} else {
		insert_case4(n);
	}
}

void RedBlackTree::remove(int key) {

}

void RedBlackTree::print() {
	printSubtree(this->root);
}

template<typename T>
RedBlackTreeNode<T> *RedBlackTree::find(int key) {
	RedBlackTreeNode<T>* node = root;
	while (node != nullptr && node->getKey() != key) {
		if (node->getKey() > key)
			node = node->getLeftChild();
		else
			node = node->getRightChild();
	}
	return node;
}

template<typename T>
RedBlackTreeNode<T> *RedBlackTree::findSuccessor(RedBlackTreeNode<T> *node) {
	RedBlackTreeNode<T>* successor = nullptr;
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

template <typename T>
RedBlackTreeNode<T> *RedBlackTree::findUncle(RedBlackTreeNode<T> *node) {
	if (node->getParent() != nullptr && node->getParent()->getParent() != nullptr) {
		if (node->getParent() == node->getParent()->getParent()->getLeftChild()) {
			return node->getParent()->getParent()->getRightChild();
		}
		else {
			return node->getParent()->getParent()->getLeftChild();
		}
	}
	else {
		return nullptr;
	}
}

template<typename T>
void RedBlackTree::printSubtree(RedBlackTreeNode<T> *node, unsigned int level) {
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
