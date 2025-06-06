#ifndef CIRCULAR_LINKED_LIST_SEARCH_H
#define CIRCULAR_LINKED_LIST_SEARCH_H

#include "../data_structures/circular_linked_list.h"

using namespace std;

// ========== Thuật toán tìm kiếm cho Circular Linked List ==========

// --- Tìm kiếm tuần tự ---
// Returns new linked list containing matching nodes
NodeSLL *searchCLL(NodeSLL *head, const char *keyword, int searchCriteria, int &count);

// --- Hiển thị kết quả tìm kiếm ---
void displaySearchResultsCLL(NodeSLL* results, int count, const char* keyword);
void displaySearchResultsCLLWithOptions(NodeSLL* results, int count, const char* keyword, 
                                        int searchCriteria, bool showReversed, double searchTimeMs);

// --- Tìm kiếm với tùy chọn ---
NodeSLL* searchCLLWithOptions(NodeSLL* head, const char* keyword, int searchCriteria, 
                             int &count, double &searchTimeMs);

#endif // CIRCULAR_LINKED_LIST_SEARCH_H
