#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include "../utils/student.h"

// Định nghĩa cấu trúc node cho danh sách liên kết đơn
struct NodeSLL
{
    Student info;
    NodeSLL *next;
};

// Khởi tạo danh sách liên kết đơn rỗng
void initSLL(NodeSLL *&head);

// Tạo mới một node sinh viên
NodeSLL *createNodeSLL(const Student &student);

// Thêm sinh viên vào đầu danh sách liên kết đơn
void addToHeadSLL(NodeSLL *&head, const Student &student);

// Thêm sinh viên vào cuối danh sách liên kết đơn
void addToTailSLL(NodeSLL *&head, const Student &student);

// Xóa sinh viên theo mã sinh viên từ danh sách liên kết đơn
bool deleteFromSLL(NodeSLL *&head, const char *studentID);

// Cập nhật thông tin sinh viên trong danh sách liên kết đơn
bool updateInSLL(NodeSLL *&head, const Student &student);

// Tìm sinh viên theo mã sinh viên trong danh sách liên kết đơn
NodeSLL *findInSLL(NodeSLL *head, const char *studentID);

// Hiển thị danh sách sinh viên trong danh sách liên kết đơn
void displaySLL(NodeSLL *head);

// Giải phóng bộ nhớ cho danh sách liên kết đơn
void freeSLL(NodeSLL *&head);

#endif // SINGLY_LINKED_LIST_H
