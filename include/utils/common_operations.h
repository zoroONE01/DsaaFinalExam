#ifndef COMMON_OPERATIONS_H
#define COMMON_OPERATIONS_H

#include "../utils/student.h"
#include "../utils/constants.h"
#include "../data_structures/array_list.h"
#include "../data_structures/singly_linked_list.h"
#include "../data_structures/circular_linked_list.h"
#include "../data_structures/doubly_linked_list.h"
#include "../data_structures/binary_search_tree.h"

// Hàm kiểm tra xem một cấu trúc dữ liệu có rỗng hay không
bool isDataStructureEmpty(int dataStructureType,
                        const ArrayStudentList &arrayList,
                        NodeSLL *singlyLinkedList,
                        NodeSLL *circularLinkedList,
                        NodeDLL *doublyLinkedListHead,
                        NodeBST *binarySearchTree);

// Hàm kiểm tra sinh viên tồn tại trong cấu trúc dữ liệu
bool isStudentExists(const char *studentID, int dataStructureType,
                   const ArrayStudentList &arrayList,
                   NodeSLL *singlyLinkedList,
                   NodeSLL *circularLinkedList,
                   NodeDLL *doublyLinkedListHead);

// Hàm thêm sinh viên vào cấu trúc dữ liệu đã chọn
bool addStudentToDataStructure(const Student &student, int dataStructureType,
                           ArrayStudentList &arrayList,
                           NodeSLL *&singlyLinkedList,
                           NodeSLL *&circularLinkedList,
                           NodeDLL *&doublyLinkedListHead,
                           NodeDLL *&doublyLinkedListTail,
                           NodeBST *&binarySearchTree);

// Hàm xóa sinh viên khỏi cấu trúc dữ liệu đã chọn
bool deleteStudentFromDataStructure(const char *studentID, int dataStructureType,
                                ArrayStudentList &arrayList,
                                NodeSLL *&singlyLinkedList,
                                NodeSLL *&circularLinkedList,
                                NodeDLL *&doublyLinkedListHead,
                                NodeDLL *&doublyLinkedListTail);

// Hàm cập nhật sinh viên trong cấu trúc dữ liệu đã chọn
bool updateStudentInDataStructure(const Student &student, int dataStructureType,
                              ArrayStudentList &arrayList,
                              NodeSLL *&singlyLinkedList,
                              NodeSLL *&circularLinkedList,
                              NodeDLL *&doublyLinkedListHead);

// Hàm tìm kiếm sinh viên trong cấu trúc dữ liệu đã chọn
void searchStudentInDataStructure(const char *studentID, int dataStructureType,
                               const ArrayStudentList &arrayList,
                               NodeSLL *singlyLinkedList,
                               NodeSLL *circularLinkedList,
                               NodeDLL *doublyLinkedListHead);

// Hàm hiển thị danh sách sinh viên dựa trên cấu trúc dữ liệu đã chọn
void displayCurrentList(int dataStructureType,
                     const ArrayStudentList &arrayList,
                     NodeSLL *singlyLinkedList,
                     NodeSLL *circularLinkedList,
                     NodeDLL *doublyLinkedListHead,
                     NodeBST *binarySearchTree);

// Hàm thực hiện thống kê sinh viên
void performStatistics(int dataStructureType, const ArrayStudentList &arrayList);

// Hàm sắp xếp danh sách sinh viên theo điểm số
bool sortStudentList(int dataStructureType, int sortAlgorithm,
                  ArrayStudentList &arrayList,
                  NodeDLL *&doublyLinkedListHead);

// Hàm xử lý nhập dữ liệu từ file CSV
bool handleInputFromCSV(int dataStructureType,
                     ArrayStudentList &arrayList,
                     NodeSLL *&singlyLinkedList,
                     NodeSLL *&circularLinkedList,
                     NodeDLL *&doublyLinkedListHead,
                     NodeDLL *&doublyLinkedListTail,
                     NodeBST *&binarySearchTree);

// Hàm để khởi tạo tất cả các cấu trúc dữ liệu
void initAllDataStructures(ArrayStudentList &arrayList,
                        NodeSLL *&singlyLinkedList,
                        NodeSLL *&circularLinkedList,
                        NodeDLL *&doublyLinkedListHead,
                        NodeDLL *&doublyLinkedListTail,
                        NodeBST *&binarySearchTree);

// Hàm thoát chương trình, giải phóng bộ nhớ
void exitProgram(NodeSLL *&singlyLinkedList,
               NodeSLL *&circularLinkedList,
               NodeDLL *&doublyLinkedListHead,
               NodeDLL *&doublyLinkedListTail,
               NodeBST *&binarySearchTree);

// Xác nhận hủy bỏ thao tác
bool confirmCancel();

#endif // COMMON_OPERATIONS_H