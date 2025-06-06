#ifndef SEARCH_H
#define SEARCH_H

#include "../core/student.h"
#include "../data_structures/array_list.h"
#include "../data_structures/singly_linked_list.h"
#include "../data_structures/doubly_linked_list.h"
#include "../utils/constants.h"
#include "student_search.h"  // Include for SearchResult definition

using namespace std;

// ========== HÀM TIỆN ÍCH ==========

// So sánh chuỗi không phân biệt hoa thường
bool compareIgnoreCase(const char* str1, const char* str2);

// Kiểm tra chuỗi con không phân biệt hoa thường
bool containsIgnoreCase(const char* str, const char* substring);

// Kiểm tra sinh viên có khớp với tiêu chí tìm kiếm không
bool checkStudentMatch(const Student& student, const char* keyword, int searchCriteria);

// In văn bản với phần khớp được tô đỏ và in đậm
void printWithHighlight(const char* text, const char* keyword, int searchCriteria, int currentCriteria);

// ========== HÀM TÌM KIẾM CHÍNH ==========

// Tìm kiếm tuần tự trong mảng
SearchResult sequentialSearchArray(const ArrayStudentList& list, const char* keyword, int searchCriteria);

// Tìm kiếm nhị phân trong mảng đã sắp xếp theo điểm
SearchResult binarySearchArrayByScore(const ArrayStudentList& list, float targetScore);

// Tìm kiếm trong danh sách liên kết đơn (luôn dùng tìm kiếm tuần tự)
SearchResult sequentialSearchSLL(NodeSLL* head, const char* keyword, int searchCriteria);

// Tìm kiếm trong danh sách liên kết vòng (luôn dùng tìm kiếm tuần tự)
SearchResult sequentialSearchCLL(NodeSLL* head, const char* keyword, int searchCriteria);

// Tìm kiếm trong danh sách liên kết kép
SearchResult searchDoublyLinkedList(NodeDLL* head, const char* keyword, int searchCriteria, bool isSorted, int sortCriteria);

// ========== HÀM HIỂN THỊ VÀ QUẢN LÝ BỘ NHỚ ==========

// Hiển thị kết quả tìm kiếm
void displaySearchResults(const SearchResult& result, const char* keyword, int searchCriteria, bool showReversedName, const char* dataStructureName);

#endif // SEARCH_H
