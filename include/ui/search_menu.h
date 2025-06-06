#ifndef SEARCH_MENU_H
#define SEARCH_MENU_H

#include "../core/student.h"
#include "../data_structures/array_list.h"
#include "../data_structures/singly_linked_list.h"
#include "../data_structures/doubly_linked_list.h"
#include "common_ui.h"

using namespace std;

// ========== HÀM NHẬP LIỆU ==========

// Nhập tiêu chí tìm kiếm
int inputSearchCriteria();

// Hỏi người dùng có muốn hiển thị họ tên đảo ngược không
bool askForReversedName();

// Nhập thuật toán tìm kiếm (chỉ dành cho Array và Doubly Linked List)
int inputSearchAlgorithm();

// ========== HÀM TIỆN ÍCH ==========
// Note: inputSearchKeyword, getDataStructureName được định nghĩa trong common_ui.h

// ========== HÀM THỰC HIỆN TÌM KIẾM ==========

// Thực hiện tìm kiếm sinh viên cho mảng
void performSearchArray(const ArrayStudentList &list, bool isSorted, int sortCriteria);

// Thực hiện tìm kiếm sinh viên cho danh sách liên kết đơn
void performSearchSLL(NodeSLL *head);

// Thực hiện tìm kiếm sinh viên cho danh sách liên kết vòng
void performSearchCLL(NodeSLL *head);

// Thực hiện tìm kiếm sinh viên cho danh sách liên kết kép
void performSearchDLL(NodeDLL *head, bool isSorted, int sortCriteria);

#endif // SEARCH_MENU_H
