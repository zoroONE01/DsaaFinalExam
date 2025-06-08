#ifndef DOUBLY_LINKED_LIST_SORTING_H
#define DOUBLY_LINKED_LIST_SORTING_H

#include "../data_structures/doubly_linked_list.h"

using namespace std;

// ========== Thuật toán sắp xếp cho Doubly Linked List ==========

// --- Các thuật toán sắp xếp chính ---
void bubbleSortDLL(NodeDLL *&head, NodeDLL *&tail, int sortCriteria);
void insertionSortDLL(NodeDLL *&head, NodeDLL *&tail, int sortCriteria);
void selectionSortDLL(NodeDLL *&head, NodeDLL *&tail, int sortCriteria);
void quickSortDLL(NodeDLL *&head, NodeDLL *&tail, int sortCriteria);
void heapSortDLL(NodeDLL *&head, NodeDLL *&tail, int sortCriteria);
void mergeSortDLL(NodeDLL **headRef, int sortCriteria);

// --- Hàm hỗ trợ cho quick sort ---
NodeDLL* partitionDLL(NodeDLL* low, NodeDLL* high, int sortCriteria);
void quickSortDLLHelper(NodeDLL* low, NodeDLL* high, int sortCriteria);

// --- Hàm hỗ trợ cho merge sort ---
NodeDLL *mergeDLL(NodeDLL *firstHalf, NodeDLL *secondHalf, int sortCriteria);
NodeDLL *splitDLL(NodeDLL *head);

#endif // DOUBLY_LINKED_LIST_SORTING_H
