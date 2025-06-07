#ifndef CIRCULAR_LINKED_LIST_SORTING_H
#define CIRCULAR_LINKED_LIST_SORTING_H

#include "../data_structures/circular_linked_list.h"

using namespace std;

// ========== Thuật toán sắp xếp cho Circular Linked List ==========

// --- Hàm so sánh sinh viên ---
bool compareStudentsCLL(const Student &a, const Student &b, int sortCriteria);

// --- Các thuật toán sắp xếp chính ---
void bubbleSortCLL(NodeSLL *&head, int sortCriteria);
void insertionSortCLL(NodeSLL *&head, int sortCriteria);
void selectionSortCLL(NodeSLL *&head, int sortCriteria);
void mergeSortCLL(NodeSLL *&head, int sortCriteria);

#endif // CIRCULAR_LINKED_LIST_SORTING_H
