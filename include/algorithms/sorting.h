#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include "../data_structures/array_list.h"
#include "../data_structures/singly_linked_list.h"
#include "../data_structures/circular_linked_list.h"
#include "../data_structures/doubly_linked_list.h"

using namespace std;

// ========== Các thuật toán sắp xếp ==========

// --- Sorting algorithms for Array List ---
void bubbleSortArrayList(ArrayStudentList &list);
void insertionSortArrayList(ArrayStudentList &list);
void selectionSortArrayList(ArrayStudentList &list);
void quickSortArrayList(ArrayStudentList &list, int low, int high);
void quickSortArrayList(ArrayStudentList &list); // Wrapper function
void heapSortArrayList(ArrayStudentList &list);
void mergeSortArrayList(ArrayStudentList &list);

// --- Sorting algorithms for Singly Linked List ---
void bubbleSortSLL(NodeSLL *&head);
void insertionSortSLL(NodeSLL *&head);
void selectionSortSLL(NodeSLL *&head);
void mergeSortSLL(NodeSLL *&head);

// --- Sorting algorithms for Circular Linked List ---
void bubbleSortCLL(NodeSLL *&head);
void insertionSortCLL(NodeSLL *&head);
void selectionSortCLL(NodeSLL *&head);
void mergeSortCLL(NodeSLL *&head);

// --- Sorting algorithms for Doubly Linked List ---
void bubbleSortDLL(NodeDLL *&head, NodeDLL *&tail);
void insertionSortDLL(NodeDLL *&head, NodeDLL *&tail);
void selectionSortDLL(NodeDLL *&head, NodeDLL *&tail);
void quickSortDLL(NodeDLL *&head, NodeDLL *&tail);
void heapSortDLL(NodeDLL *&head, NodeDLL *&tail); // Special implementation for DLL
void mergeSortDLL(NodeDLL **headRef); // Already implemented

// --- Helper functions ---
int partitionArrayList(ArrayStudentList &list, int low, int high);
void heapifyArrayList(ArrayStudentList &list, int n, int i);
void mergeArrayList(ArrayStudentList &list, int left, int mid, int right);
void mergeSortArrayListHelper(ArrayStudentList &list, int left, int right);

// Search function
int binarySearchArrayList(const ArrayStudentList &list, float scoreToFind);

#endif // SORTING_ALGORITHMS_H