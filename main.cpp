//
// Created by outfrost on 07/05/17.
//

#include <cstdio>
#include <iostream>
#include <fstream>
#include <random>
#include "string_consts.h"
#include "ArrayList.cpp"
#include "LinkedList.cpp"
#include "BinaryHeap.cpp"
#include "BinarySearchTree.cpp"
#include "getValueFromString.cpp"
#include "main.h"

int main(int argc, char **argv) {
	
	char choice = '\0';
	while (choice != '0') {
		
		std::printf("# %s #\n", STR_LANG_MAINMENU);
		std::printf("---\n");
		std::printf("1. %s\n", STR_LANG_ARRAYLIST);
		std::printf("2. %s\n", STR_LANG_LINKEDLIST);
		std::printf("3. %s\n", STR_LANG_BINARYHEAP);
		std::printf("4. %s\n", STR_LANG_BINARYSEARCHTREE);
		std::printf("---\n");
		std::printf("0. %s\n", STR_LANG_QUIT);
		std::printf("(main) ");
		std::scanf(" %c", &choice);
		
		if (choice == '1') {
			List<int> * arrayList = new ArrayList<int>();
			
			char choice = '\0';
			while (choice != '0') {
				readStructureMenuChoice(&choice, (char *)STR_LANG_ARRAYLIST);
				if (choice == '1') {
					unsigned int size = 0u;
					
					std::ifstream * file = openStreamForReading();
					std::string word;
					
					bool success = true;
					*file >> word;
					success = success && getValueFromString<unsigned int>(word, size);
					if (success) {
						arrayList = new ArrayList<int>();
						for (unsigned int i = 0u; i < size; i++) {
							int value = 0;
							*file >> word;
							success = success && getValueFromString<int>(word, value);
							if (success)
								arrayList->add(value);
							else
								std::printf("%s %u\n", STR_LANG_ERR_ADDING_ELEMENT, i);
						}
						arrayList->print();
					}
					else
						std::printf("%s\n", STR_LANG_ERR_BUILDING_FROM_FILE);
					
					file->close();
				}
				else if (choice == '2') {
					std::printf("%s: ", STR_LANG_ENTER_VALUE);
					int value = 0;
					std::scanf("%d", &value);
					arrayList->add(value);
					arrayList->print();
				}
				else if (choice == '3') {
					std::printf("%s: ", STR_LANG_ENTER_INDEX);
					unsigned int index = 0u;
					std::scanf("%u", &index);
					arrayList->removeAt(index);
					arrayList->print();
				}
				else if (choice == '4') {
					std::printf("%s: ", STR_LANG_ENTER_VALUE);
					int value = 0;
					std::scanf("%d", &value);
					if (arrayList->contains(value))
						std::printf("%s\n", STR_LANG_DOES_CONTAIN);
					else
						std::printf("%s\n", STR_LANG_DOES_NOT_CONTAIN);
				}
				else if (choice == '5') {
					std::printf("%s: ", STR_LANG_ENTER_SIZE);
					unsigned int size = 0u;
					std::scanf("%u", &size);
					if (size > 0u) {
						arrayList = new ArrayList<int>();
						std::random_device randomDevice;
						std::mt19937 mt(randomDevice());
						std::uniform_int_distribution<int> distribution(std::numeric_limits<int>::min());
						for (unsigned int i = 0u; i < size; i++)
							arrayList->add(distribution(mt));
						arrayList->print();
					}
					else
						std::printf("%s\n", STR_LANG_GEN_RAND_ZERO_SIZE);
				}
				else if (choice == '6') {
					arrayList->print();
				}
				else if (choice == '7') {
					std::printf("%s\n", STR_LANG_CANNOT_BALANCE);
				}
			}
		}
		else if (choice == '2') {
			List<int> * linkedList = new LinkedList<int>();
			
			char choice = '\0';
			while (choice != '0') {
				readStructureMenuChoice(&choice, (char *)STR_LANG_LINKEDLIST);
				if (choice == '1') {
					unsigned int size = 0u;
					
					std::ifstream * file = openStreamForReading();
					std::string word;
					
					bool success = true;
					*file >> word;
					success = success && getValueFromString<unsigned int>(word, size);
					if (success) {
						linkedList = new LinkedList<int>();
						for (unsigned int i = 0u; i < size; i++) {
							int value = 0;
							*file >> word;
							success = success && getValueFromString<int>(word, value);
							if (success)
								linkedList->add(value);
							else
								std::printf("%s %u\n", STR_LANG_ERR_ADDING_ELEMENT, i);
						}
						linkedList->print();
					}
					else
						std::printf("%s\n", STR_LANG_ERR_BUILDING_FROM_FILE);
					
					file->close();
				}
				else if (choice == '2') {
					std::printf("%s: ", STR_LANG_ENTER_VALUE);
					int value = 0;
					std::scanf("%d", &value);
					linkedList->add(value);
					linkedList->print();
				}
				else if (choice == '3') {
					std::printf("%s: ", STR_LANG_ENTER_VALUE);
					int value = 0;
					std::scanf("%u", &value);
					linkedList->remove(value);
					linkedList->print();
				}
				else if (choice == '4') {
					std::printf("%s: ", STR_LANG_ENTER_VALUE);
					int value = 0;
					std::scanf("%d", &value);
					if (linkedList->contains(value))
						std::printf("%s\n", STR_LANG_DOES_CONTAIN);
					else
						std::printf("%s\n", STR_LANG_DOES_NOT_CONTAIN);
				}
				else if (choice == '5') {
					std::printf("%s: ", STR_LANG_ENTER_SIZE);
					unsigned int size = 0u;
					std::scanf("%u", &size);
					if (size > 0u) {
						linkedList = new LinkedList<int>();
						std::random_device randomDevice;
						std::mt19937 mt(randomDevice());
						std::uniform_int_distribution<int> distribution(std::numeric_limits<int>::min());
						for (unsigned int i = 0u; i < size; i++)
							linkedList->add(distribution(mt));
						linkedList->print();
					}
					else
						std::printf("%s\n", STR_LANG_GEN_RAND_ZERO_SIZE);
				}
				else if (choice == '6') {
					linkedList->print();
				}
				else if (choice == '7') {
					std::printf("%s\n", STR_LANG_CANNOT_BALANCE);
				}
			}
		}
		else if (choice == '3') {
			BinaryHeap<void*> * binaryHeap = new BinaryHeap<void*>();
			
			char choice = '\0';
			while (choice != '0') {
				readStructureMenuChoice(&choice, (char *)STR_LANG_BINARYHEAP);
				if (choice == '1') {
					unsigned int size = 0u;
					
					std::ifstream * file = openStreamForReading();
					std::string word;
					
					bool success = true;
					*file >> word;
					success = success && getValueFromString<unsigned int>(word, size);
					if (success) {
						binaryHeap = new BinaryHeap<void*>();
						for (unsigned int i = 0u; i < size; i++) {
							int key = 0;
							*file >> word;
							success = success && getValueFromString<int>(word, key);
							if (success)
								binaryHeap->add(key, nullptr);
							else
								std::printf("%s %u\n", STR_LANG_ERR_ADDING_ELEMENT, i);
						}
						binaryHeap->print();
					}
					else
						std::printf("%s\n", STR_LANG_ERR_BUILDING_FROM_FILE);
					
					file->close();
				}
				else if (choice == '2') {
					std::printf("%s: ", STR_LANG_ENTER_KEY);
					int key = 0;
					std::scanf("%d", &key);
					binaryHeap->add(key, nullptr);
					binaryHeap->print();
				}
				else if (choice == '3') {
					std::printf("%s: ", STR_LANG_ENTER_KEY);
					int key = 0;
					std::scanf("%u", &key);
					binaryHeap->remove(key);
					binaryHeap->print();
				}
				else if (choice == '4') {
					std::printf("%s: ", STR_LANG_ENTER_KEY);
					int key = 0;
					std::scanf("%d", &key);
					if (binaryHeap->contains(key))
						std::printf("%s\n", STR_LANG_DOES_CONTAIN);
					else
						std::printf("%s\n", STR_LANG_DOES_NOT_CONTAIN);
				}
				else if (choice == '5') {
					std::printf("%s: ", STR_LANG_ENTER_SIZE);
					unsigned int size = 0u;
					std::scanf("%u", &size);
					if (size > 0u) {
						binaryHeap = new BinaryHeap<void*>();
						std::random_device randomDevice;
						std::mt19937 mt(randomDevice());
						std::uniform_int_distribution<int> distribution(std::numeric_limits<int>::min());
						for (unsigned int i = 0u; i < size; i++)
							binaryHeap->add(distribution(mt), nullptr);
						binaryHeap->print();
					}
					else
						std::printf("%s\n", STR_LANG_GEN_RAND_ZERO_SIZE);
				}
				else if (choice == '6') {
					binaryHeap->print();
				}
				else if (choice == '7') {
					std::printf("%s\n", STR_LANG_CANNOT_BALANCE);
				}
			}
		}
		else if (choice == '4') {
			BinarySearchTree<void*> * binarySearchTree = new BinarySearchTree<void*>();
			
			char choice = '\0';
			while (choice != '0') {
				readStructureMenuChoice(&choice, (char *)STR_LANG_BINARYSEARCHTREE);
				if (choice == '1') {
					unsigned int size = 0u;
					
					std::ifstream * file = openStreamForReading();
					std::string word;
					
					bool success = true;
					*file >> word;
					success = success && getValueFromString<unsigned int>(word, size);
					if (success) {
						binarySearchTree = new BinarySearchTree<void*>();
						for (unsigned int i = 0u; i < size; i++) {
							int key = 0;
							*file >> word;
							success = success && getValueFromString<int>(word, key);
							if (success)
								binarySearchTree->add(key, nullptr);
							else
								std::printf("%s %u\n", STR_LANG_ERR_ADDING_ELEMENT, i);
						}
						binarySearchTree->print();
					}
					else
						std::printf("%s\n", STR_LANG_ERR_BUILDING_FROM_FILE);
					
					file->close();
				}
				else if (choice == '2') {
					std::printf("%s: ", STR_LANG_ENTER_KEY);
					int key = 0;
					std::scanf("%d", &key);
					binarySearchTree->add(key, nullptr);
					binarySearchTree->print();
				}
				else if (choice == '3') {
					std::printf("%s: ", STR_LANG_ENTER_KEY);
					int key = 0;
					std::scanf("%u", &key);
					binarySearchTree->remove(key);
					binarySearchTree->print();
				}
				else if (choice == '4') {
					std::printf("%s: ", STR_LANG_ENTER_KEY);
					int key = 0;
					std::scanf("%d", &key);
					if (binarySearchTree->contains(key))
						std::printf("%s\n", STR_LANG_DOES_CONTAIN);
					else
						std::printf("%s\n", STR_LANG_DOES_NOT_CONTAIN);
				}
				else if (choice == '5') {
					std::printf("%s: ", STR_LANG_ENTER_SIZE);
					unsigned int size = 0u;
					std::scanf("%u", &size);
					if (size > 0u) {
						binarySearchTree = new BinarySearchTree<void*>();
						std::random_device randomDevice;
						std::mt19937 mt(randomDevice());
						std::uniform_int_distribution<int> distribution(std::numeric_limits<int>::min());
						for (unsigned int i = 0u; i < size; i++)
							binarySearchTree->add(distribution(mt), nullptr);
						binarySearchTree->print();
					}
					else
						std::printf("%s\n", STR_LANG_GEN_RAND_ZERO_SIZE);
				}
				else if (choice == '6') {
					binarySearchTree->print();
				}
				else if (choice == '7') {
					binarySearchTree->balance();
				}
			}
		}
		
	}
}

void readStructureMenuChoice(char * choice, char * structureName) {
	std::printf("# %s #\n", structureName);
	std::printf("---\n");
	std::printf("1. %s\n", STR_LANG_STRUCTURE_FROM_FILE);
	std::printf("2. %s\n", STR_LANG_ADD_ELEMENT);
	std::printf("3. %s\n", STR_LANG_REMOVE_ELEMENT);
	std::printf("4. %s\n", STR_LANG_FIND_ELEMENT);
	std::printf("5. %s\n", STR_LANG_GEN_RAND_STRUCTURE);
	std::printf("6. %s\n", STR_LANG_PRINT_STRUCTURE);
	std::printf("7. %s\n", STR_LANG_BALANCE_TREE);
	std::printf("---\n");
	std::printf("0. %s\n", STR_LANG_BACKTOMAIN);
	std::printf("(%s) ", structureName);
	std::scanf(" %c", choice);
}

std::ifstream * openStreamForReading() {
	std::cin.ignore();
	std::printf("%s: ", STR_LANG_ENTER_FILENAME);
	std::string filename = "";
	std::getline(std::cin, filename);
	return new std::ifstream(filename);
}