#ifndef ARRAY_SORTING_H
#define ARRAY_SORTING_H

#include "../data_structures/array_list.h"

using namespace std;

// ========== Thuật toán sắp xếp cho Array List ==========

// --- Hàm tiện ích so sánh sinh viên ---
bool compareStudents(const Student &a, const Student &b, int sortCriteria);

// --- Các thuật toán sắp xếp chính ---
void bubbleSortArrayList(ArrayStudentList &list, int sortCriteria);
void insertionSortArrayList(ArrayStudentList &list, int sortCriteria);
void selectionSortArrayList(ArrayStudentList &list, int sortCriteria);
void quickSortArrayList(ArrayStudentList &list, int sortCriteria);
void heapSortArrayList(ArrayStudentList &list, int sortCriteria);
void mergeSortArrayList(ArrayStudentList &list, int sortCriteria);

// --- Hàm hỗ trợ cho các thuật toán sắp xếp ---
int partitionArrayList(ArrayStudentList &list, int low, int high, int sortCriteria);
void quickSortArrayListHelper(ArrayStudentList &list, int low, int high, int sortCriteria);
void heapifyArrayList(ArrayStudentList &list, int n, int i, int sortCriteria);
void mergeArrayList(ArrayStudentList &list, int left, int mid, int right, int sortCriteria);
void mergeSortArrayListHelper(ArrayStudentList &list, int left, int right, int sortCriteria);

#endif // ARRAY_SORTING_H
