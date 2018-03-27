#ifndef DATA_STRUCTURES_PROJECT_REDBLACKTREE_H
#define DATA_STRUCTURES_PROJECT_REDBLACKTREE_H

#include "RedBlackTreeNode.h"


template<typename T>
class RedBlackTree {

private:
	RedBlackTreeNode<T>* root;
	
public:
	RedBlackTree() {
		this->root = nullptr;
	}
	
	bool get(int key, T* const dest);
	bool contains(int key);
	void add(int key, T const value);
	void remove(int key);
	void print();
	
protected:
	RedBlackTreeNode<T>* find(int key);
	RedBlackTreeNode<T>* findSuccessor(RedBlackTreeNode<T>* node);
	RedBlackTreeNode<T>* findUncle(RedBlackTreeNode<T>* node);
	void printSubtree(RedBlackTreeNode<T>* node, unsigned int level = 0u);
	
};


#endif //DATA_STRUCTURES_PROJECT_REDBLACKTREE_H
