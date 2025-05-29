#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "../utils/student.h"

// Định nghĩa cấu trúc node cho danh sách liên kết đôi
struct NodeDLL
{
    Student info;
    NodeDLL *prev;
    NodeDLL *next;
};

// Khởi tạo danh sách liên kết đôi rỗng
void initDLL(NodeDLL *&head, NodeDLL *&tail);

// Tạo mới một node cho danh sách liên kết đôi
NodeDLL *createNodeDLL(const Student &student);

// Thêm sinh viên vào đầu danh sách liên kết đôi
void addToHeadDLL(NodeDLL *&head, NodeDLL *&tail, const Student &student);

// Thêm sinh viên vào cuối danh sách liên kết đôi
void addToTailDLL(NodeDLL *&head, NodeDLL *&tail, const Student &student);

// Xóa sinh viên theo mã sinh viên từ danh sách liên kết đôi
bool deleteFromDLL(NodeDLL *&head, NodeDLL *&tail, const char *studentID);

// Cập nhật thông tin sinh viên trong danh sách liên kết đôi
bool updateInDLL(NodeDLL *head, const Student &student);

// Tìm sinh viên theo mã sinh viên trong danh sách liên kết đôi
NodeDLL *findInDLL(NodeDLL *head, const char *studentID);

// Hiển thị danh sách sinh viên trong danh sách liên kết đôi
void displayDLL(NodeDLL *head);

// Giải phóng bộ nhớ cho danh sách liên kết đôi
void freeDLL(NodeDLL *&head, NodeDLL *&tail);

#endif // DOUBLY_LINKED_LIST_H
