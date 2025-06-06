#ifndef DOUBLY_LINKED_LIST_SEARCH_H
#define DOUBLY_LINKED_LIST_SEARCH_H

#include "../data_structures/doubly_linked_list.h"

using namespace std;

// ========== Thuật toán tìm kiếm cho Doubly Linked List ==========

// --- Tìm kiếm tuần tự ---
// Returns new linked list containing matching nodes
NodeDLL* searchDLL(NodeDLL* head, const char* keyword, int searchCriteria, int &count);

// --- Hiển thị kết quả tìm kiếm ---
void displaySearchResultsDLL(NodeDLL* results, int count, const char* keyword);
void displaySearchResultsDLLWithOptions(NodeDLL* results, int count, const char* keyword, 
                                        int searchCriteria, bool showReversed, double searchTimeMs);

// --- Tìm kiếm với tùy chọn ---
NodeDLL* searchDLLWithOptions(NodeDLL* head, const char* keyword, int searchCriteria, 
                             int &count, double &searchTimeMs);

#endif // DOUBLY_LINKED_LIST_SEARCH_H
