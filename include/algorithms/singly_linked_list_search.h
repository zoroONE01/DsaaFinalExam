#ifndef SINGLY_LINKED_LIST_SEARCH_H
#define SINGLY_LINKED_LIST_SEARCH_H

#include "../data_structures/singly_linked_list.h"

using namespace std;

// ========== Thuật toán tìm kiếm cho Singly Linked List ==========

// --- Tìm kiếm tuần tự ---
// Returns new linked list containing matching nodes
NodeSLL* searchSLL(NodeSLL* head, const char* keyword, int searchCriteria, int &count);

// --- Hiển thị kết quả tìm kiếm ---
void displaySearchResultsSLL(NodeSLL* results, int count, const char* keyword);

#endif // SINGLY_LINKED_LIST_SEARCH_H
