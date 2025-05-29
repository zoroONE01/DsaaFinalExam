#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include "../data_structures/array_list.h"
#include "../data_structures/doubly_linked_list.h"

// Các thuật toán sắp xếp cho danh sách mảng

// Sắp xếp nổi bọt (Bubble Sort)
void bubbleSortArrayList(ArrayStudentList &list);

// Sắp xếp chèn (Insertion Sort)
void insertionSortArrayList(ArrayStudentList &list);

// Sắp xếp chọn (Selection Sort)
void selectionSortArrayList(ArrayStudentList &list);

// Sắp xếp nhanh (Quick Sort)
void quickSortArrayList(ArrayStudentList &list);
void quickSortArrayListHelper(ArrayStudentList &list, int low, int high);
int partitionArrayList(ArrayStudentList &list, int low, int high);

// Các thuật toán sắp xếp cho danh sách liên kết đôi

// Sắp xếp trộn (Merge Sort)
void mergeSortDLL(NodeDLL **headRef);
NodeDLL* sortedMergeDLL(NodeDLL* a, NodeDLL* b);
void splitDLL(NodeDLL* source, NodeDLL** frontRef, NodeDLL** backRef);

#endif // SORTING_ALGORITHMS_H