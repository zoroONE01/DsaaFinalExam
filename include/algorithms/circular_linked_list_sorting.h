#ifndef CIRCULAR_LINKED_LIST_SORTING_H
#define CIRCULAR_LINKED_LIST_SORTING_H

#include "../data_structures/circular_linked_list.h"

using namespace std;

// ========== Thuật toán sắp xếp cho Circular Linked List ==========

// --- Các thuật toán sắp xếp chính ---
void bubbleSortCLL(NodeSLL *&head);
void insertionSortCLL(NodeSLL *&head);
void selectionSortCLL(NodeSLL *&head);
void mergeSortCLL(NodeSLL *&head);

#endif // CIRCULAR_LINKED_LIST_SORTING_H
