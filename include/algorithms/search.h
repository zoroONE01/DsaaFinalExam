#ifndef SEARCH_ALGORITHMS_H
#define SEARCH_ALGORITHMS_H

// ========== Thư viện tìm kiếm tổng hợp ==========
// File này gộp tất cả các thuật toán tìm kiếm cho tiện sử dụng
// Mỗi thư viện con có thể được include riêng lẻ nếu cần

#include "search_utils.h"
#include "array_search.h"
#include "singly_linked_list_search.h"
#include "circular_linked_list_search.h"
#include "doubly_linked_list_search.h"
#include "../ui/common_ui.h"

// Forward declarations
struct ArrayStudentList;
struct NodeSLL;
struct NodeDLL;
struct NodeCLL;

// ========== Tất cả các hàm tìm kiếm đã được định nghĩa trong các thư viện con ==========

// ========== INTERFACE TÌM KIẾM TỔNG HỢP ==========

// Sử dụng SearchCriteria đã định nghĩa trong common_ui.h
// SEARCH_BY_STUDENT_ID = 1, SEARCH_BY_FIRST_NAME = 2, SEARCH_BY_LAST_NAME = 3, 
// SEARCH_BY_CLASS = 4, SEARCH_BY_SCORE = 5

/**
 * @brief Cấu trúc lưu trữ tùy chọn tìm kiếm
 */
struct SearchOptions {
    bool showReversedName;    // Hiển thị họ tên đảo ngược
    bool useSmartSearch;      // Tự động chọn binary/linear search
    bool highlightResults;    // Tô đỏ kết quả tìm thấy
    bool showSearchTime;      // Hiển thị thời gian tìm kiếm
};

/**
 * @brief Cấu trúc lưu trữ kết quả tìm kiếm
 */
struct SearchResults {
    int* indices;             // Mảng chỉ số kết quả
    int count;                // Số lượng kết quả
    double searchTimeMs;      // Thời gian tìm kiếm (ms)
    SearchCriteria criteria;  // Tiêu chí đã tìm
    char keyword[100];        // Từ khóa đã tìm
};

// ========== CÁC HÀM TÌM KIẾM TỔNG HỢP ==========

/**
 * @brief Hàm tìm kiếm tổng hợp cho tất cả các cấu trúc dữ liệu
 * Tự động chọn thuật toán phù hợp và hiển thị kết quả theo tùy chọn
 */

// Tìm kiếm cho Array List
SearchResults searchWithOptions(const ArrayStudentList &list, const char* keyword, 
                               SearchCriteria criteria, const SearchOptions& options, bool isSorted = false);

// Tìm kiếm cho Singly Linked List
SearchResults searchSLLWithOptions(NodeSLL* head, const char* keyword, 
                                  SearchCriteria criteria, const SearchOptions& options);

// Tìm kiếm cho Doubly Linked List  
SearchResults searchDLLWithOptions(NodeDLL* head, const char* keyword,
                                  SearchCriteria criteria, const SearchOptions& options);

// Tìm kiếm cho Circular Linked List
SearchResults searchCLLWithOptions(NodeCLL* head, const char* keyword,
                                  SearchCriteria criteria, const SearchOptions& options);

// Menu tìm kiếm tương tác
void interactiveSearchMenu();
const char* getCriteriaName(SearchCriteria criteria);
void displaySearchMenu();
SearchOptions getSearchOptions();
void cleanupSearchResults(SearchResults& results);

/*
 * CÁC THƯ VIỆN CON:
 * - search_utils.h: Các hàm tiện ích cho tìm kiếm
 * - array_search.h: Thuật toán tìm kiếm cho Array List
 * - singly_linked_list_search.h: Thuật toán tìm kiếm cho Singly Linked List
 * - circular_linked_list_search.h: Thuật toán tìm kiếm cho Circular Linked List
 * - doubly_linked_list_search.h: Thuật toán tìm kiếm cho Doubly Linked List
 */

#endif // SEARCH_ALGORITHMS_H
