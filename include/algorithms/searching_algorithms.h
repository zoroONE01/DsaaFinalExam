#ifndef SEARCHING_ALGORITHMS_H
#define SEARCHING_ALGORITHMS_H

#include "../data_structures/array_list.h"
#include "../data_structures/singly_linked_list.h"
#include "../data_structures/circular_linked_list.h"
#include "../data_structures/doubly_linked_list.h"

// Tìm kiếm tuần tự (Sequential Search) trong mảng
int sequentialSearch(const ArrayStudentList &list, const char *studentID);

// Tìm kiếm nhị phân (Binary Search) trong mảng đã sắp xếp
int binarySearch(const ArrayStudentList &list, const char *studentID, int left, int right);

// Tìm kiếm tuần tự trong danh sách liên kết đơn
NodeSLL* sequentialSearchSLL(NodeSLL *head, const char *studentID);

// Tìm kiếm tuần tự trong danh sách liên kết vòng
NodeSLL* sequentialSearchCLL(NodeSLL *head, const char *studentID);

// Tìm kiếm tuần tự trong danh sách liên kết đôi
NodeDLL* sequentialSearchDLL(NodeDLL *head, const char *studentID);

#endif // SEARCHING_ALGORITHMS_H