#ifndef ARRAY_SEARCH_H
#define ARRAY_SEARCH_H

#include "../data_structures/array_list.h"

using namespace std;

// ========== Thuật toán tìm kiếm cho Array List ==========

// --- Tìm kiếm tuần tự ---
// Returns array of indices where matches are found, count stores number of results
int *searchArrayList(const ArrayStudentList &list, const char *keyword, int searchCriteria, int &count);

// --- Tìm kiếm nhị phân (yêu cầu dữ liệu đã sắp xếp) ---
// Binary search for specific criteria (requires sorted data)
int binarySearchArrayList(const ArrayStudentList &list, float scoreToFind);
int binarySearchArrayListByID(const ArrayStudentList &list, const char *studentID);

// --- Hiển thị kết quả tìm kiếm ---
void displaySearchResultsArray(const ArrayStudentList &list, int *indices, int count, const char *keyword);
void displaySearchResultsArrayWithOptions(const ArrayStudentList &list, int *indices, int count, 
                                         const char *keyword, int searchCriteria, 
                                         bool showReversed, double searchTimeMs);

// --- Tìm kiếm với tùy chọn nâng cao ---
int* searchArrayListWithOptions(const ArrayStudentList &list, const char *keyword, int searchCriteria, 
                               int &count, double &searchTimeMs, bool isSorted, int sortCriteria);

#endif // ARRAY_SEARCH_H
