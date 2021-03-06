#include "../common/string_consts.h"
#include "ArrayList.cpp"
#include "LinkedList.cpp"
#include "BinaryHeap.cpp"
#include "../common/getValueFromString.h"
#include "../common/time_measurement.h"
#include "basic_structures.h"

namespace basic_structures {
	
	int program() {
		
		char choice = '\0';
		while (choice != '0') {
			
			std::cout << "# " << STR_LANG_MAINMENU << " #\n";
			std::cout << "---\n";
			std::cout << "1. " << STR_LANG_ARRAYLIST << "\n";
			std::cout << "2. " << STR_LANG_LINKEDLIST << "\n";
			std::cout << "3. " << STR_LANG_BINARYHEAP << "\n";
			std::cout << "---\n";
			std::cout << "F. " << STR_LANG_TIME_MEASUREMENT << "\n";
			std::cout << "---\n";
			std::cout << "0. " << STR_LANG_QUIT << "\n";
			std::cout << "(basic_structures) ";
			/*std::printf("# %s #\n", STR_LANG_MAINMENU);
			std::printf("---\n");
			std::printf("1. %s\n", STR_LANG_ARRAYLIST);
			std::printf("2. %s\n", STR_LANG_LINKEDLIST);
			std::printf("3. %s\n", STR_LANG_BINARYHEAP);
			std::printf("4. %s\n", STR_LANG_BINARYSEARCHTREE);
			std::printf("---\n");
			std::printf("F. %s\n", STR_LANG_TIME_MEASUREMENT);
			std::printf("---\n");
			std::printf("0. %s\n", STR_LANG_QUIT);
			std::printf("(main) ");*/
			//std::cin.ignore(1, '\n');
			choice = (char) std::cin.get();
			//std::scanf(" %c", &choice);
			
			if (choice == '1') {
				List<int>* arrayList = new ArrayList<int>();
				
				char choice = '\0';
				while (choice != '0') {
					readStructureMenuChoice(&choice, STR_LANG_ARRAYLIST);
					if (choice == '1') {
						unsigned int size = 0u;
						
						std::ifstream* file = openStreamForReading();
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
									std::cerr << STR_LANG_ERR_ADDING_ELEMENT << " " << i << "\n";
							}
							arrayList->print();
						} else
							std::cerr << STR_LANG_ERR_BUILDING_FROM_FILE << "\n";
						
						file->close();
					} else if (choice == '2') {
						std::cout << STR_LANG_ENTER_VALUE << ": ";
						int value = 0;
						std::scanf("%d", &value);
						std::cout << STR_LANG_ENTER_INDEX << ": ";
						unsigned int index = 0u;
						std::scanf("%u", &index);
						if (index <= arrayList->getSize()) {
							arrayList->add(value, index);
							arrayList->print();
						} else
							std::cerr << STR_EX_INDEX_OUT_OF_BOUNDS << "\n";
					} else if (choice == '3') {
						std::cout << STR_LANG_ENTER_INDEX << ": ";
						unsigned int index = 0u;
						std::scanf("%u", &index);
						if (index < arrayList->getSize()) {
							arrayList->removeAt(index);
							arrayList->print();
						} else
							std::cerr << STR_EX_INDEX_OUT_OF_BOUNDS << "\n";
					} else if (choice == '4' || choice == '6') {
						std::cout << STR_LANG_ENTER_VALUE << ": ";
						int value = 0;
						std::scanf("%d", &value);
						if (choice == '4') {
							arrayList->addStart(value);
						} else {
							arrayList->addEnd(value);
						}
						arrayList->print();
					} else if (choice == '5' || choice == '7') {
						if (arrayList->getSize() > 0) {
							if (choice == '5') {
								arrayList->removeFirst();
							} else {
								arrayList->removeLast();
							}
							arrayList->print();
						} else
							std::cerr << STR_EX_ARRAYLIST_EMPTY << "\n";
					} else if (choice == '8') {
						std::cout << STR_LANG_ENTER_VALUE << ": ";
						int value = 0;
						std::scanf("%d", &value);
						if (arrayList->contains(value))
							std::cout << STR_LANG_DOES_CONTAIN << "\n";
						else
							std::cout << STR_LANG_DOES_NOT_CONTAIN << "\n";
					} else if (choice == '9') {
						std::cout << STR_LANG_ENTER_SIZE << ": ";
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
						} else
							std::cout << STR_LANG_GEN_RAND_ZERO_SIZE << "\n";
					} else if (choice == 'A' || choice == 'a') {
						arrayList->print();
					}
					/*else if (choice == '7') {
						std::cout << STR_LANG_CANNOT_BALANCE << "\n";
					}*/
				}
			} else if (choice == '2') {
				List<int>* linkedList = new LinkedList<int>();
				
				char choice = '\0';
				while (choice != '0') {
					readStructureMenuChoice(&choice, STR_LANG_LINKEDLIST);
					if (choice == '1') {
						unsigned int size = 0u;
						
						std::ifstream* file = openStreamForReading();
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
									std::cerr << STR_LANG_ERR_ADDING_ELEMENT << " " << i << "\n";
							}
							((LinkedList<int>*) linkedList)->print(true);
						} else
							std::cerr << STR_LANG_ERR_BUILDING_FROM_FILE << "\n";
						
						file->close();
					} else if (choice == '2') {
						std::cout << STR_LANG_ENTER_VALUE << ": ";
						int value = 0;
						std::scanf("%d", &value);
						std::cout << STR_LANG_ENTER_INDEX << ": ";
						unsigned int index = 0u;
						std::scanf("%u", &index);
						if (index <= linkedList->getSize()) {
							linkedList->add(value, index);
							((LinkedList<int>*) linkedList)->print(true);
						} else
							std::cerr << STR_EX_INDEX_OUT_OF_BOUNDS << "\n";
					} else if (choice == '3') {
						std::cout << STR_LANG_ENTER_INDEX << ": ";
						unsigned int index = 0u;
						std::scanf("%u", &index);
						if (index < linkedList->getSize()) {
							linkedList->removeAt(index);
							((LinkedList<int>*) linkedList)->print(true);
						} else
							std::cerr << STR_EX_INDEX_OUT_OF_BOUNDS << "\n";
					} else if (choice == '4' || choice == '6') {
						std::cout << STR_LANG_ENTER_VALUE << ": ";
						int value = 0;
						std::scanf("%d", &value);
						if (choice == '4') {
							linkedList->addStart(value);
						} else {
							linkedList->addEnd(value);
						}
						((LinkedList<int>*) linkedList)->print(true);
					} else if (choice == '5' || choice == '7') {
						if (linkedList->getSize() > 0) {
							if (choice == '5') {
								linkedList->removeFirst();
							} else {
								linkedList->removeLast();
							}
							((LinkedList<int>*) linkedList)->print(true);
						} else
							std::cerr << STR_EX_LINKEDLIST_EMPTY << "\n";
					} else if (choice == '8') {
						std::cout << STR_LANG_ENTER_VALUE << ": ";
						int value = 0;
						std::scanf("%d", &value);
						if (linkedList->contains(value))
							std::cout << STR_LANG_DOES_CONTAIN << "\n";
						else
							std::cout << STR_LANG_DOES_NOT_CONTAIN << "\n";
					} else if (choice == '9') {
						std::cout << STR_LANG_ENTER_SIZE << ": ";
						unsigned int size = 0u;
						std::scanf("%u", &size);
						if (size > 0u) {
							linkedList = new LinkedList<int>();
							std::random_device randomDevice;
							std::mt19937 mt(randomDevice());
							std::uniform_int_distribution<int> distribution(std::numeric_limits<int>::min());
							for (unsigned int i = 0u; i < size; i++)
								linkedList->add(distribution(mt));
							((LinkedList<int>*) linkedList)->print(true);
						} else
							std::cout << STR_LANG_GEN_RAND_ZERO_SIZE << "\n";
					} else if (choice == 'A' || choice == 'a') {
						((LinkedList<int>*) linkedList)->print(true);
					}
					/*else if (choice == '7') {
						std::cout << STR_LANG_CANNOT_BALANCE << "\n";
					}*/
				}
			} else if (choice == '3') {
				BinaryHeap<void*>* binaryHeap = new BinaryHeap<void*>();
				
				char choice = '\0';
				while (choice != '0') {
					readStructureMenuChoice(&choice, STR_LANG_BINARYHEAP);
					if (choice == '1') {
						unsigned int size = 0u;
						
						std::ifstream* file = openStreamForReading();
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
									std::cerr << STR_LANG_ERR_ADDING_ELEMENT << " " << i << "\n";
							}
							binaryHeap->print();
						} else
							std::cerr << STR_LANG_ERR_BUILDING_FROM_FILE << "\n";
						
						file->close();
					} else if (choice == '2') {
						std::cout << STR_LANG_ENTER_KEY << ": ";
						int key = 0;
						std::scanf("%d", &key);
						binaryHeap->add(key, nullptr);
						binaryHeap->print();
					} else if (choice == '3') {
						std::cout << STR_LANG_ENTER_KEY << ": ";
						int key = 0;
						std::scanf("%u", &key);
						try {
							binaryHeap->remove(key);
						} catch (std::out_of_range& e) {
							std::cerr << e.what() << "\n";
						}
						binaryHeap->print();
					} else if (choice == '4' || choice == '5' || choice == '6' || choice == '7') {
						std::cout << STR_LANG_NOT_APPLICABLE << "\n";
					} else if (choice == '8') {
						std::cout << STR_LANG_ENTER_KEY << ": ";
						int key = 0;
						std::scanf("%d", &key);
						if (binaryHeap->contains(key))
							std::cout << STR_LANG_DOES_CONTAIN << "\n";
						else
							std::cout << STR_LANG_DOES_NOT_CONTAIN << "\n";
					} else if (choice == '9') {
						std::cout << STR_LANG_ENTER_SIZE << ": ";
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
						} else
							std::cout << STR_LANG_GEN_RAND_ZERO_SIZE << "\n";
					} else if (choice == 'A' || choice == 'a') {
						binaryHeap->print();
					}
					/*else if (choice == '7') {
						std::cout << STR_LANG_CANNOT_BALANCE << "\n";
					}*/
				}
			} else if (choice == 'F' || choice == 'f') {
				std::ofstream* resultStream = openStreamForWriting();
				*resultStream
						<< "structure_size,arraylist_add,arraylist_remove,arraylist_add_start,arraylist_remove_start,arraylist_add_end,arraylist_remove_end,arraylist_find,linkedlist_add,linkedlist_remove,linkedlist_add_start,linkedlist_remove_start,linkedlist_add_end,linkedlist_remove_end,linkedlist_find,binaryheap_add,binaryheap_remove,binaryheap_find\n";
				int count = MAX_GENERATED_DATA;
				for (int i = 0; i < 5 && count > 0; i++) {
					for (int i = 0; i < MEASUREMENT_PASSES; i++) {
						List<int>* arrayList = new ArrayList<int>();
						List<int>* linkedList = new LinkedList<int>();
						BinaryHeap<void*>* binaryHeap = new BinaryHeap<void*>();
						
						std::cout << STR_LANG_GENERATING_PRE << count << STR_LANG_GENERATING_AFT;
						std::random_device randomDevice;
						std::mt19937 mt(randomDevice());
						std::uniform_int_distribution<int> dataDistribution(std::numeric_limits<int>::min());
						std::uniform_int_distribution<unsigned int> indexDistribution(0u, (unsigned int) (count - 1));
						for (int i = 0; i < count; i++) {
							int number = dataDistribution(mt);
							arrayList->add(number);
							linkedList->add(number);
							binaryHeap->add(number, nullptr);
						}
						
						std::cout << STR_LANG_MEASURING_PRE << i + 1 << STR_LANG_MEASUGING_AFT;
						
						std::chrono::time_point<std::chrono::high_resolution_clock> timeBefore;
						std::chrono::time_point<std::chrono::high_resolution_clock> timeAfter;
						
						int numberToAdd = dataDistribution(mt);
						unsigned int randomIndex = indexDistribution(mt);
						int numberToRemove = arrayList->get(randomIndex);
						int numberToFind = arrayList->get(indexDistribution(mt));
						
						// structure_size
						*resultStream << count << ",";
						
						// arraylist_add
						timeBefore = std::chrono::high_resolution_clock::now();
						arrayList->add(numberToAdd, randomIndex);
						timeAfter = std::chrono::high_resolution_clock::now();
						*resultStream << nanoseconds(timeBefore, timeAfter) << ",";
						// arraylist_remove
						timeBefore = std::chrono::high_resolution_clock::now();
						arrayList->removeAt(randomIndex);
						timeAfter = std::chrono::high_resolution_clock::now();
						*resultStream << nanoseconds(timeBefore, timeAfter) << ",";
						// arraylist_add_start
						timeBefore = std::chrono::high_resolution_clock::now();
						arrayList->add(numberToAdd, 0u);
						timeAfter = std::chrono::high_resolution_clock::now();
						*resultStream << nanoseconds(timeBefore, timeAfter) << ",";
						// arraylist_remove_start
						timeBefore = std::chrono::high_resolution_clock::now();
						arrayList->removeAt(0u);
						timeAfter = std::chrono::high_resolution_clock::now();
						*resultStream << nanoseconds(timeBefore, timeAfter) << ",";
						// arraylist_add_end
						timeBefore = std::chrono::high_resolution_clock::now();
						arrayList->add(numberToAdd, arrayList->getSize() - 1);
						timeAfter = std::chrono::high_resolution_clock::now();
						*resultStream << nanoseconds(timeBefore, timeAfter) << ",";
						// arraylist_remove_end
						timeBefore = std::chrono::high_resolution_clock::now();
						arrayList->removeAt(arrayList->getSize() - 1);
						timeAfter = std::chrono::high_resolution_clock::now();
						*resultStream << nanoseconds(timeBefore, timeAfter) << ",";
						// arraylist_find
						timeBefore = std::chrono::high_resolution_clock::now();
						arrayList->contains(numberToFind);
						timeAfter = std::chrono::high_resolution_clock::now();
						*resultStream << nanoseconds(timeBefore, timeAfter) << ",";
						
						// linkedlist_add
						timeBefore = std::chrono::high_resolution_clock::now();
						linkedList->add(numberToAdd, randomIndex);
						timeAfter = std::chrono::high_resolution_clock::now();
						*resultStream << nanoseconds(timeBefore, timeAfter) << ",";
						// linkedlist_remove
						timeBefore = std::chrono::high_resolution_clock::now();
						linkedList->removeAt(randomIndex);
						timeAfter = std::chrono::high_resolution_clock::now();
						*resultStream << nanoseconds(timeBefore, timeAfter) << ",";
						// linkedlist_add_start
						timeBefore = std::chrono::high_resolution_clock::now();
						linkedList->add(numberToAdd, 0u);
						timeAfter = std::chrono::high_resolution_clock::now();
						*resultStream << nanoseconds(timeBefore, timeAfter) << ",";
						// linkedlist_remove_start
						timeBefore = std::chrono::high_resolution_clock::now();
						linkedList->removeAt(0u);
						timeAfter = std::chrono::high_resolution_clock::now();
						*resultStream << nanoseconds(timeBefore, timeAfter) << ",";
						// linkedlist_add_end
						timeBefore = std::chrono::high_resolution_clock::now();
						linkedList->add(numberToAdd, linkedList->getSize() - 1);
						timeAfter = std::chrono::high_resolution_clock::now();
						*resultStream << nanoseconds(timeBefore, timeAfter) << ",";
						// linkedlist_remove_end
						timeBefore = std::chrono::high_resolution_clock::now();
						linkedList->removeAt(linkedList->getSize() - 1);
						timeAfter = std::chrono::high_resolution_clock::now();
						*resultStream << nanoseconds(timeBefore, timeAfter) << ",";
						// linkedlist_find
						timeBefore = std::chrono::high_resolution_clock::now();
						linkedList->contains(numberToFind);
						timeAfter = std::chrono::high_resolution_clock::now();
						*resultStream << nanoseconds(timeBefore, timeAfter) << ",";
						
						// binaryheap_add
						timeBefore = std::chrono::high_resolution_clock::now();
						binaryHeap->add(numberToAdd, nullptr);
						timeAfter = std::chrono::high_resolution_clock::now();
						*resultStream << nanoseconds(timeBefore, timeAfter) << ",";
						// binaryheap_remove
						timeBefore = std::chrono::high_resolution_clock::now();
						binaryHeap->remove(numberToRemove);
						timeAfter = std::chrono::high_resolution_clock::now();
						*resultStream << nanoseconds(timeBefore, timeAfter) << ",";
						// binaryheap_find
						timeBefore = std::chrono::high_resolution_clock::now();
						binaryHeap->contains(numberToFind);
						timeAfter = std::chrono::high_resolution_clock::now();
						*resultStream << nanoseconds(timeBefore, timeAfter) << "\n";
						
						delete arrayList;
						delete linkedList;
						delete binaryHeap;
					}
					count >>= 1;
				}
				resultStream->close();
				delete resultStream;
			}
		}
		
		return 0;
	}
	
	void readStructureMenuChoice(char* choice, const std::string& structureName) {
		std::cout << "# " << structureName << " #\n";
		std::cout << "---\n";
		std::cout << "1. " << STR_LANG_STRUCTURE_FROM_FILE << "\n";
		std::cout << "2. " << STR_LANG_ADD_ELEMENT << "\n";
		std::cout << "3. " << STR_LANG_REMOVE_ELEMENT << "\n";
		std::cout << "4. " << STR_LANG_ADD_ELEMENT_START << "\n";
		std::cout << "5. " << STR_LANG_REMOVE_FIRST_ELEMENT << "\n";
		std::cout << "6. " << STR_LANG_ADD_ELEMENT_END << "\n";
		std::cout << "7. " << STR_LANG_REMOVE_LAST_ELEMENT << "\n";
		std::cout << "8. " << STR_LANG_FIND_ELEMENT << "\n";
		std::cout << "9. " << STR_LANG_GEN_RAND_STRUCTURE << "\n";
		std::cout << "A. " << STR_LANG_PRINT_STRUCTURE << "\n";
		std::cout << "---\n";
		std::cout << "0. " << STR_LANG_BACKTOMAIN << "\n";
		std::cout << "(" << structureName << ") ";
		do {
			*choice = (char) std::cin.get();
		} while (*choice == '\n');
		
		/*std::printf("# %s #\n", structureName);
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
		std::scanf(" %c", choice);*/
	}
	
	std::ifstream* openStreamForReading() {
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.ignore();
		std::cout << STR_LANG_ENTER_FILENAME << ": ";
		std::string filename = "";
		std::getline(std::cin, filename);
		return new std::ifstream(filename);
	}
	
	std::ofstream* openStreamForWriting() {
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.ignore();
		std::cout << STR_LANG_ENTER_FILENAME_RESULTS << ": ";
		std::string filename = "";
		std::getline(std::cin, filename);
		return new std::ofstream(filename);
	}
	
}
