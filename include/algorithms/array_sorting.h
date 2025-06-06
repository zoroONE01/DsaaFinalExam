#ifndef ARRAY_SORTING_H
#define ARRAY_SORTING_H

#include "../data_structures/array_list.h"

using namespace std;

// ========== Thuật toán sắp xếp cho Array List ==========

// --- Các thuật toán sắp xếp chính ---
void bubbleSortArrayList(ArrayStudentList &list);
void insertionSortArrayList(ArrayStudentList &list);
void selectionSortArrayList(ArrayStudentList &list);
void quickSortArrayList(ArrayStudentList &list);
void heapSortArrayList(ArrayStudentList &list);
void mergeSortArrayList(ArrayStudentList &list);

// --- Hàm hỗ trợ cho các thuật toán sắp xếp ---
int partitionArrayList(ArrayStudentList &list, int low, int high);
void quickSortArrayListHelper(ArrayStudentList &list, int low, int high);
void heapifyArrayList(ArrayStudentList &list, int n, int i);
void mergeArrayList(ArrayStudentList &list, int left, int mid, int right);
void mergeSortArrayListHelper(ArrayStudentList &list, int left, int right);

#endif // ARRAY_SORTING_H
