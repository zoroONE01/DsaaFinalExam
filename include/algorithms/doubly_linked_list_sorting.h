#ifndef DOUBLY_LINKED_LIST_SORTING_H
#define DOUBLY_LINKED_LIST_SORTING_H

#include "../data_structures/doubly_linked_list.h"

using namespace std;

// ========== Thuật toán sắp xếp cho Doubly Linked List ==========

// --- Các thuật toán sắp xếp chính ---
void bubbleSortDLL(NodeDLL *&head, NodeDLL *&tail);
void insertionSortDLL(NodeDLL *&head, NodeDLL *&tail);
void selectionSortDLL(NodeDLL *&head, NodeDLL *&tail);
void quickSortDLL(NodeDLL *&head, NodeDLL *&tail);
void heapSortDLL(NodeDLL *&head, NodeDLL *&tail);
void mergeSortDLL(NodeDLL **headRef);

// --- Hàm hỗ trợ cho quick sort ---
NodeDLL* partitionDLL(NodeDLL* low, NodeDLL* high);
void quickSortDLLHelper(NodeDLL* low, NodeDLL* high);

// --- Hàm hỗ trợ cho merge sort ---
NodeDLL *mergeDLL(NodeDLL *firstHalf, NodeDLL *secondHalf);
NodeDLL *splitDLL(NodeDLL *head);

#endif // DOUBLY_LINKED_LIST_SORTING_H
