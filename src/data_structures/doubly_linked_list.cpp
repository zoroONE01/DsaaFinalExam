#include "../../include/data_structures/doubly_linked_list.h"
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

// Khởi tạo danh sách liên kết đôi rỗng
void initDLL(NodeDLL *&head, NodeDLL *&tail)
{
    head = NULL;
    tail = NULL;
}

// Tạo mới một node cho danh sách liên kết đôi
NodeDLL *createNodeDLL(const Student &student)
{
    NodeDLL *newNode = new NodeDLL;
    newNode->info = student;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Thêm sinh viên vào đầu danh sách liên kết đôi
void addToHeadDLL(NodeDLL *&head, NodeDLL *&tail, const Student &student)
{
    NodeDLL *newNode = createNodeDLL(student);

    if (head == NULL)
    {
        // Danh sách rỗng
        head = newNode;
        tail = newNode;
    }
    else
    {
        // Danh sách không rỗng
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

// Thêm sinh viên vào cuối danh sách liên kết đôi
void addToTailDLL(NodeDLL *&head, NodeDLL *&tail, const Student &student)
{
    NodeDLL *newNode = createNodeDLL(student);

    if (head == NULL)
    {
        // Danh sách rỗng
        head = newNode;
        tail = newNode;
    }
    else
    {
        // Danh sách không rỗng
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

// Xóa sinh viên theo mã sinh viên từ danh sách liên kết đôi
bool deleteFromDLL(NodeDLL *&head, NodeDLL *&tail, const char *studentID)
{
    // Kiểm tra danh sách rỗng
    if (head == NULL)
    {
        return false;
    }

    // Tìm node cần xóa
    NodeDLL *current = head;

    while (current != NULL)
    {
        if (strcmp(current->info.studentID, studentID) == 0)
        {
            // Tìm thấy node cần xóa

            // Trường hợp 1: Nút đầu tiên
            if (current == head)
            {
                head = head->next;
                if (head != NULL)
                {
                    head->prev = NULL;
                }
                else
                {
                    // Danh sách chỉ có 1 node
                    tail = NULL;
                }
                delete current;
                return true;
            }

            // Trường hợp 2: Nút cuối cùng
            else if (current == tail)
            {
                tail = tail->prev;
                tail->next = NULL;
                delete current;
                return true;
            }

            // Trường hợp 3: Nút ở giữa
            else
            {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
                return true;
            }
        }

        current = current->next;
    }

    return false; // Không tìm thấy sinh viên cần xóa
}

// Cập nhật thông tin sinh viên trong danh sách liên kết đôi
bool updateInDLL(NodeDLL *head, const Student &student)
{
    NodeDLL *current = head;

    while (current != NULL)
    {
        if (strcmp(current->info.studentID, student.studentID) == 0)
        {
            // Tìm thấy sinh viên cần cập nhật
            current->info = student;
            return true;
        }
        current = current->next;
    }

    return false; // Không tìm thấy sinh viên cần cập nhật
}

// Tìm sinh viên theo mã sinh viên trong danh sách liên kết đôi
NodeDLL *findInDLL(NodeDLL *head, const char *studentID)
{
    NodeDLL *current = head;

    while (current != NULL)
    {
        if (strcmp(current->info.studentID, studentID) == 0)
        {
            return current; // Tìm thấy sinh viên
        }
        current = current->next;
    }

    return NULL; // Không tìm thấy sinh viên
}

// Hiển thị danh sách sinh viên trong danh sách liên kết đôi
void displayDLL(NodeDLL *head)
{
    if (head == NULL)
    {
        cout << "Danh sách liên kết đôi rỗng!" << endl;
        return;
    }

    // Hiển thị tiêu đề
    cout << left << setw(10) << "Mã SV"
         << setw(20) << "Họ"
         << setw(20) << "Tên"
         << setw(15) << "Lớp"
         << setw(5) << "Điểm" << endl;
    cout << string(70, '-') << endl;

    // Duyệt qua danh sách và hiển thị thông tin sinh viên
    NodeDLL *current = head;

    while (current != NULL)
    {
        cout << left << setw(10) << current->info.studentID
             << setw(20) << current->info.firstName
             << setw(20) << current->info.lastName
             << setw(15) << current->info.studentClass
             << setw(5) << current->info.score << endl;
        current = current->next;
    }
}

// Giải phóng bộ nhớ cho danh sách liên kết đôi
void freeDLL(NodeDLL *&head, NodeDLL *&tail)
{
    NodeDLL *current = head;
    NodeDLL *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        delete current;
        current = next;
    }

    head = NULL;
    tail = NULL;
}