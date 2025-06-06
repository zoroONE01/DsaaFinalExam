#ifndef COMMON_OPERATIONS_H
#define COMMON_OPERATIONS_H

#include "student.h"
#include "../data_structures/array_list.h"
#include "../data_structures/singly_linked_list.h"
#include "../data_structures/circular_linked_list.h"
#include "../data_structures/doubly_linked_list.h"
#include "../data_structures/binary_search_tree.h"
#include "../algorithms/sorting.h"
#include "../ui/common_ui.h"
#include <iostream>

using namespace std;

// Function declarations
bool isDataStructureEmpty(int dataStructureType,
                          const ArrayStudentList &arrayList,
                          NodeSLL *singlyLinkedList,
                          NodeSLL *circularLinkedList,
                          NodeDLL *doublyLinkedListHead,
                          NodeBST *binarySearchTree);

bool isStudentExists(const char *studentID, int dataStructureType,
                     const ArrayStudentList &arrayList,
                     NodeSLL *singlyLinkedList,
                     NodeSLL *circularLinkedList,
                     NodeDLL *doublyLinkedListHead);

bool validateAndShowDuplicateStudentID(const string &studentID, int dataStructureType,
                                       const ArrayStudentList &arrayList,
                                       NodeSLL *singlyLinkedList,
                                       NodeSLL *circularLinkedList,
                                       NodeDLL *doublyLinkedListHead);

void exitProgram(NodeSLL *&singlyLinkedList,
                 NodeSLL *&circularLinkedList,
                 NodeDLL *&doublyLinkedListHead,
                 NodeDLL *&doublyLinkedListTail,
                 NodeBST *&binarySearchTree);

bool confirmCancel();

bool addStudentToDataStructure(const Student &student, int dataStructureType,
                               ArrayStudentList &arrayList,
                               NodeSLL *&singlyLinkedList,
                               NodeSLL *&circularLinkedList,
                               NodeDLL *&doublyLinkedListHead,
                               NodeDLL *&doublyLinkedListTail,
                               NodeBST *&binarySearchTree);

bool deleteStudentFromDataStructure(const char *studentID, int dataStructureType,
                                    ArrayStudentList &arrayList,
                                    NodeSLL *&singlyLinkedList,
                                    NodeSLL *&circularLinkedList,
                                    NodeDLL *&doublyLinkedListHead,
                                    NodeDLL *&doublyLinkedListTail);

bool updateStudentInDataStructure(const Student &student, int dataStructureType,
                                  ArrayStudentList &arrayList,
                                  NodeSLL *&singlyLinkedList,
                                  NodeSLL *&circularLinkedList,
                                  NodeDLL *&doublyLinkedListHead);

void enhancedSearchStudentInDataStructure(int dataStructureType,
                                        const ArrayStudentList &arrayList,
                                        NodeSLL *singlyLinkedList,
                                        NodeSLL *circularLinkedList,
                                        NodeDLL *doublyLinkedListHead,
                                        int currentSortCriteria);

void displayCurrentList(int dataStructureType,
                        const ArrayStudentList &arrayList,
                        NodeSLL *singlyLinkedList,
                        NodeSLL *circularLinkedList,
                        NodeDLL *doublyLinkedListHead,
                        NodeBST *binarySearchTree);

void performStatistics(int dataStructureType, 
                      const ArrayStudentList &arrayList,
                      NodeSLL *singlyLinkedList,
                      NodeSLL *circularLinkedList,
                      NodeDLL *doublyLinkedListHead);

bool sortStudentList(int dataStructureType, int sortAlgorithm, int sortCriteria,
                     ArrayStudentList &arrayList,
                     NodeSLL *&singlyLinkedList,
                     NodeSLL *&circularLinkedList,
                     NodeDLL *&doublyLinkedListHead,
                     NodeDLL *&doublyLinkedListTail);

bool handleInputFromCSV(const char* filePath,
                        int dataStructureType,
                        ArrayStudentList &arrayList,
                        NodeSLL *&singlyLinkedList,
                        NodeSLL *&circularLinkedList,
                        NodeDLL *&doublyLinkedListHead,
                        NodeDLL *&doublyLinkedListTail,
                        NodeBST *&binarySearchTree);

bool inputStudentID(char *studentID);

bool inputStudent(Student &student);

bool getStudentFromDataStructure(const char *studentID, int dataStructureType,
                                const ArrayStudentList &arrayList,
                                NodeSLL *singlyLinkedList,
                                NodeSLL *circularLinkedList,
                                NodeDLL *doublyLinkedListHead,
                                Student &foundStudent);

bool inputStudentForUpdate(Student &student);

void initAllDataStructures(ArrayStudentList &arrayList,
                           NodeSLL *&singlyLinkedList,
                           NodeSLL *&circularLinkedList,
                           NodeDLL *&doublyLinkedListHead,
                           NodeDLL *&doublyLinkedListTail,
                           NodeBST *&binarySearchTree);

#endif // COMMON_OPERATIONS_H