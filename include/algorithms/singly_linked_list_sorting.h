#ifndef SINGLY_LINKED_LIST_SORTING_H
#define SINGLY_LINKED_LIST_SORTING_H

#include "../data_structures/singly_linked_list.h"

using namespace std;

// ========== Thuật toán sắp xếp cho Singly Linked List ==========

// --- Các thuật toán sắp xếp chính ---
void bubbleSortSLL(NodeSLL *&head);
void insertionSortSLL(NodeSLL *&head);
void selectionSortSLL(NodeSLL *&head);
void mergeSortSLL(NodeSLL *&head);

// --- Hàm hỗ trợ cho merge sort ---
NodeSLL* mergeSortedSLL(NodeSLL* a, NodeSLL* b);
void splitSLL(NodeSLL* source, NodeSLL** frontRef, NodeSLL** backRef);

#endif // SINGLY_LINKED_LIST_SORTING_H
