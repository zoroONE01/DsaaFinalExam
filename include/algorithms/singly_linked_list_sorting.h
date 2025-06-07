#ifndef SINGLY_LINKED_LIST_SORTING_H
#define SINGLY_LINKED_LIST_SORTING_H

#include "../data_structures/singly_linked_list.h"

using namespace std;

// ========== Thuật toán sắp xếp cho Singly Linked List ==========

// --- Hàm tiện ích so sánh sinh viên ---
bool compareStudentsSLL(const Student &a, const Student &b, int sortCriteria);

// --- Các thuật toán sắp xếp chính ---
void bubbleSortSLL(NodeSLL *&head, int sortCriteria);
void insertionSortSLL(NodeSLL *&head, int sortCriteria);
void selectionSortSLL(NodeSLL *&head, int sortCriteria);
void mergeSortSLL(NodeSLL *&head, int sortCriteria);

// --- Hàm hỗ trợ cho merge sort ---
NodeSLL* mergeSortedSLL(NodeSLL* a, NodeSLL* b, int sortCriteria);
void splitSLL(NodeSLL* source, NodeSLL** frontRef, NodeSLL** backRef);

#endif // SINGLY_LINKED_LIST_SORTING_H
