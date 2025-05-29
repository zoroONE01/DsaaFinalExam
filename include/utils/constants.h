#ifndef CONSTANTS_H
#define CONSTANTS_H

// Các hằng số cho cấu trúc dữ liệu
enum DataStructureType
{
    ARRAY_LIST = 1,
    SINGLY_LINKED_LIST = 2,
    CIRCULAR_LINKED_LIST = 3,
    DOUBLY_LINKED_LIST = 4,
    BINARY_SEARCH_TREE = 5
};

// Hằng số cho thuật toán sắp xếp
enum SortAlgorithm
{
    BUBBLE_SORT = 1,
    INSERTION_SORT = 2,
    SELECTION_SORT = 3,
    QUICK_SORT = 4,
    MERGE_SORT = 5,
    HEAP_SORT = 6
};

// Các hằng số khác
const int MAX_STUDENTS = 100; // Kích thước tối đa của mảng sinh viên
const int MAX_STUDENTS_PER_SCORE = 20; // Số lượng tối đa sinh viên có thể có cùng điểm số

#endif // CONSTANTS_H
