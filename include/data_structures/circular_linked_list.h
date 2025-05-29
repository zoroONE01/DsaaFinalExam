#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

#include "../utils/student.h"
#include "singly_linked_list.h" // Tái sử dụng NodeSLL

// Khởi tạo danh sách liên kết vòng rỗng
void initCLL(NodeSLL *&head);

// Tạo mới một node cho danh sách liên kết vòng
NodeSLL *createNodeCLL(const Student &student);

// Thêm sinh viên vào đầu danh sách liên kết vòng
void addToHeadCLL(NodeSLL *&head, const Student &student);

// Thêm sinh viên vào cuối danh sách liên kết vòng
void addToTailCLL(NodeSLL *&head, const Student &student);

// Xóa sinh viên theo mã sinh viên từ danh sách liên kết vòng
bool deleteFromCLL(NodeSLL *&head, const char *studentID);

// Cập nhật thông tin sinh viên trong danh sách liên kết vòng
bool updateInCLL(NodeSLL *&head, const Student &student);

// Tìm sinh viên theo mã sinh viên trong danh sách liên kết vòng
NodeSLL *findInCLL(NodeSLL *head, const char *studentID);

// Hiển thị danh sách sinh viên trong danh sách liên kết vòng
void displayCLL(NodeSLL *head);

// Giải phóng bộ nhớ cho danh sách liên kết vòng
void freeCLL(NodeSLL *&head);

#endif // CIRCULAR_LINKED_LIST_H
