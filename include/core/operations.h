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

// ========== Struct cho thống kê theo lớp ==========
struct ClassStatistics {
    char className[MAX_CLASS_LENGTH];     // Tên lớp
    int totalStudents;                    // Tổng số sinh viên
    float highestScore;                   // Điểm cao nhất
    float lowestScore;                    // Điểm thấp nhất
    float averageScore;                   // Điểm trung bình
};

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
                     NodeDLL *doublyLinkedListHead,
                     NodeBST *binarySearchTree);

bool validateAndShowDuplicateStudentID(const string &studentID, int dataStructureType,
                                       const ArrayStudentList &arrayList,
                                       NodeSLL *singlyLinkedList,
                                       NodeSLL *circularLinkedList,
                                       NodeDLL *doublyLinkedListHead,
                                       NodeBST *binarySearchTree);

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

bool deleteNodeFromBSTByKey(NodeBST *&binarySearchTree);

bool updateStudentInDataStructure(const Student &student, int dataStructureType,
                                  ArrayStudentList &arrayList,
                                  NodeSLL *&singlyLinkedList,
                                  NodeSLL *&circularLinkedList,
                                  NodeDLL *&doublyLinkedListHead);

void searchStudentInDataStructure(int dataStructureType,
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

void performGeneralStatistics(int dataStructureType,
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

// ========== Các hàm helper cho BST ==========
void addStudentToBST(const Student &student, NodeBST *&binarySearchTree);
void deleteStudentFromBST(const char *studentID, NodeBST *&binarySearchTree);
bool getStudentFromBST(const char *studentID, NodeBST *binarySearchTree, Student &foundStudent);
void updateStudentInBST(const Student &student, NodeBST *&binarySearchTree);
void displayBST(NodeBST *binarySearchTree);

// ========== Các hàm chuyển đổi dữ liệu giữa các cấu trúc ==========
void convertDataStructureToBST(int sourceDataStructureType,
                               const ArrayStudentList &arrayList,
                               NodeSLL *singlyLinkedList,
                               NodeSLL *circularLinkedList,
                               NodeDLL *doublyLinkedListHead,
                               NodeBST *&binarySearchTree);

void convertBSTToArrayList(NodeBST *binarySearchTree, ArrayStudentList &arrayList);

// Hàm helper cho chuyển đổi BST sang Array List
void traverseBSTAndAddToArray(NodeBST* node, ArrayStudentList &arrayList);

// ========== Các hàm chọn cấu trúc dữ liệu với xử lý chuyển đổi BST ==========
int selectDataStructureWithBSTHandling(int currentDataStructureType,
                                       ArrayStudentList &arrayList,
                                       NodeSLL *singlyLinkedList,
                                       NodeSLL *circularLinkedList,
                                       NodeDLL *doublyLinkedListHead,
                                       NodeBST *&binarySearchTree);

// ========== Các hàm mới: Xóa toàn bộ và lưu file ==========
bool clearAllData(int dataStructureType,
                  ArrayStudentList &arrayList,
                  NodeSLL *&singlyLinkedList,
                  NodeSLL *&circularLinkedList,
                  NodeDLL *&doublyLinkedListHead,
                  NodeDLL *&doublyLinkedListTail,
                  NodeBST *&binarySearchTree);

bool saveToCSVFile(const char *filename, int dataStructureType,
                   const ArrayStudentList &arrayList,
                   NodeSLL *singlyLinkedList,
                   NodeSLL *circularLinkedList,
                   NodeDLL *doublyLinkedListHead,
                   NodeBST *binarySearchTree);

// ========== Các hàm helper cho thống kê theo lớp ==========
int getUniqueClassesArray(const ArrayStudentList &arrayList, char classes[][MAX_CLASS_LENGTH]);
int getUniqueClassesSLL(NodeSLL *singlyLinkedList, char classes[][MAX_CLASS_LENGTH]);
int getUniqueClassesCLL(NodeSLL *circularLinkedList, char classes[][MAX_CLASS_LENGTH]);
int getUniqueClassesDLL(NodeDLL *doublyLinkedListHead, char classes[][MAX_CLASS_LENGTH]);

void calculateClassStatisticsArray(const ArrayStudentList &arrayList, const char *className, ClassStatistics &stats);
void calculateClassStatisticsSLL(NodeSLL *singlyLinkedList, const char *className, ClassStatistics &stats);
void calculateClassStatisticsCLL(NodeSLL *circularLinkedList, const char *className, ClassStatistics &stats);
void calculateClassStatisticsDLL(NodeDLL *doublyLinkedListHead, const char *className, ClassStatistics &stats);

void displayClassStatistics(const ClassStatistics &stats);
void displayAllClassStatistics(int dataStructureType,
                               const ArrayStudentList &arrayList,
                               NodeSLL *singlyLinkedList,
                               NodeSLL *circularLinkedList,
                               NodeDLL *doublyLinkedListHead);

#endif // COMMON_OPERATIONS_H