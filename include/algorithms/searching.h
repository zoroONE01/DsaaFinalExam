#ifndef SEARCHING_H
#define SEARCHING_H

#include "../core/student.h"
#include "../data_structures/array_list.h"
#include "../data_structures/singly_linked_list.h"
#include "../data_structures/circular_linked_list.h"
#include "../data_structures/doubly_linked_list.h"
#include "../utils/constants.h"
#include "../ui/common_ui.h"

using namespace std;

// ========== Cấu trúc kết quả tìm kiếm ==========

struct SearchResult
{
    Student *students;   // Mảng sinh viên tìm được
    int count;           // Số lượng sinh viên tìm được
    double searchTimeMs; // Thời gian tìm kiếm (milliseconds)
    bool isBinarySearch; // Có sử dụng tìm kiếm nhị phân không
};

struct SearchTimer
{
    long long startTime; // Thời gian bắt đầu (microseconds)
    long long endTime;   // Thời gian kết thúc (microseconds)
};

// ========== Hàm tiện ích tìm kiếm ==========

// Hàm so sánh chuỗi không phân biệt hoa thường
bool compareIgnoreCase(const char *str1, const char *str2);

// Hàm kiểm tra chuỗi con
bool containsIgnoreCase(const char *str, const char *substring);

// Hàm kiểm tra sinh viên khớp tiêu chí
bool checkStudentMatch(const Student &student, const char *keyword, int searchCriteria);

// Hàm đảo ngược chuỗi họ tên
char *reverseFullName(const char *firstName, const char *lastName);

// Hàm đo thời gian
SearchTimer startTimer();
void stopTimer(SearchTimer &timer);
double getElapsedTimeMs(const SearchTimer &timer);

// ========== Hàm tìm kiếm chính ==========

// Tìm kiếm tuần tự
SearchResult sequentialSearch(Student *students, int totalCount, const char *keyword, int searchCriteria);

// Tìm kiếm nhị phân (chỉ áp dụng cho mảng và danh sách liên kết đôi đã sắp xếp)
SearchResult binarySearchArray(const ArrayStudentList &list, const char *keyword, int searchCriteria, int sortCriteria);
SearchResult binarySearchDLL(NodeDLL *head, const char *keyword, int searchCriteria, int sortCriteria);

// Tìm kiếm cho các cấu trúc dữ liệu cụ thể
SearchResult sequentialSearchArray(const ArrayStudentList &list, const char *keyword, int searchCriteria);
SearchResult binarySearchArrayByScore(const ArrayStudentList &list, float targetScore);
SearchResult sequentialSearchSLL(NodeSLL *head, const char *keyword, int searchCriteria);
SearchResult sequentialSearchCLL(NodeSLL *head, const char *keyword, int searchCriteria);
SearchResult searchDoublyLinkedList(NodeDLL *head, const char *keyword, int searchCriteria, bool isSorted, int sortCriteria);

// ========== Hàm hiển thị kết quả ==========

// Hiển thị kết quả tìm kiếm với tùy chọn
void displaySearchResults(const SearchResult &result, const char *keyword, int searchCriteria, bool showReversedName);

// Hiển thị kết quả tìm kiếm với tên cấu trúc dữ liệu
void displaySearchResultsWithDataStructure(const SearchResult &result, const char *keyword, int searchCriteria, bool showReversedName, const char *dataStructureName);

// Hiển thị một sinh viên với highlight
void displayStudentWithHighlight(const Student &student, const char *keyword, int searchCriteria, bool showReversedName);

// In văn bản với phần khớp được tô đỏ và in đậm
void printHighlighted(const char *text, const char *keyword);

// ========== Hàm giải phóng bộ nhớ ==========

void freeSearchResult(SearchResult &result);



#endif // SEARCHING_H
