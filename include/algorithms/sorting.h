#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include "../data_structures/array_list.h"

using namespace std;

// ========== Các thuật toán sắp xếp ==========

// Sorting algorithms for Array List
void bubbleSortArrayList(ArrayStudentList &list);
void insertionSortArrayList(ArrayStudentList &list);
void selectionSortArrayList(ArrayStudentList &list);
void quickSortArrayList(ArrayStudentList &list, int low, int high);

#endif // SORTING_ALGORITHMS_H