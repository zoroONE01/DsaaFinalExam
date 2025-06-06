#ifndef SEARCH_ALGORITHMS_H
#define SEARCH_ALGORITHMS_H

#include "../data_structures/array_list.h"

using namespace std;

// ========== Thuật toán tìm kiếm ==========

// --- Tìm kiếm trong Array List ---
int binarySearchArrayList(const ArrayStudentList &list, float scoreToFind);

// Có thể thêm các thuật toán tìm kiếm khác trong tương lai:
// int linearSearchArrayList(const ArrayStudentList &list, const char* studentID);
// int interpolationSearchArrayList(const ArrayStudentList &list, float scoreToFind);

#endif // SEARCH_ALGORITHMS_H
