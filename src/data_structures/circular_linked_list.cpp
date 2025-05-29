#include "../../include/data_structures/circular_linked_list.h"
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

// Khởi tạo danh sách liên kết vòng rỗng
void initCLL(NodeSLL *&head)
{
    head = NULL;
}

// Tạo mới một node cho danh sách liên kết vòng
NodeSLL *createNodeCLL(const Student &student)
{
    NodeSLL *newNode = new NodeSLL;
    newNode->info = student;
    newNode->next = newNode; // Trong danh sách liên kết vòng, node cuối cùng trỏ về chính nó
    return newNode;
}

// Thêm sinh viên vào đầu danh sách liên kết vòng
void addToHeadCLL(NodeSLL *&head, const Student &student)
{
    NodeSLL *newNode = createNodeCLL(student);

    if (head == NULL)
    {
        // Nếu danh sách rỗng, node mới trỏ đến chính nó
        head = newNode;
    }
    else
    {
        // Tìm node cuối cùng (node mà next trỏ đến head)
        NodeSLL *lastNode = head;
        while (lastNode->next != head)
        {
            lastNode = lastNode->next;
        }

        // Cập nhật liên kết
        newNode->next = head;
        lastNode->next = newNode;
        head = newNode;
    }
}

// Thêm sinh viên vào cuối danh sách liên kết vòng
void addToTailCLL(NodeSLL *&head, const Student &student)
{
    NodeSLL *newNode = createNodeCLL(student);

    if (head == NULL)
    {
        // Nếu danh sách rỗng, node mới trỏ đến chính nó
        head = newNode;
    }
    else
    {
        // Tìm node cuối cùng (node mà next trỏ đến head)
        NodeSLL *lastNode = head;
        while (lastNode->next != head)
        {
            lastNode = lastNode->next;
        }

        // Cập nhật liên kết
        lastNode->next = newNode;
        newNode->next = head;
    }
}

// Xóa sinh viên theo mã sinh viên từ danh sách liên kết vòng
bool deleteFromCLL(NodeSLL *&head, const char *studentID)
{
    if (head == NULL)
    {
        return false; // Danh sách rỗng
    }

    // Kiểm tra nếu node đầu tiên là node cần xóa
    if (strcmp(head->info.studentID, studentID) == 0)
    {
        NodeSLL *temp = head;

        // Nếu chỉ có một node trong danh sách
        if (head->next == head)
        {
            delete temp;
            head = NULL;
        }
        else
        {
            // Tìm node cuối cùng
            NodeSLL *lastNode = head;
            while (lastNode->next != head)
            {
                lastNode = lastNode->next;
            }

            // Cập nhật liên kết và xóa node
            head = head->next;
            lastNode->next = head;
            delete temp;
        }

        return true;
    }

    // Tìm node cần xóa và node trước nó
    NodeSLL *current = head->next;
    NodeSLL *prev = head;

    while (current != head && strcmp(current->info.studentID, studentID) != 0)
    {
        prev = current;
        current = current->next;
    }

    // Nếu tìm thấy node cần xóa
    if (current != head)
    {
        prev->next = current->next;
        delete current;
        return true;
    }

    return false; // Không tìm thấy sinh viên cần xóa
}

// Cập nhật thông tin sinh viên trong danh sách liên kết vòng
bool updateInCLL(NodeSLL *&head, const Student &student)
{
    if (head == NULL)
    {
        return false; // Danh sách rỗng
    }

    // Kiểm tra node đầu tiên
    if (strcmp(head->info.studentID, student.studentID) == 0)
    {
        head->info = student;
        return true;
    }

    // Kiểm tra các node còn lại
    NodeSLL *current = head->next;

    while (current != head)
    {
        if (strcmp(current->info.studentID, student.studentID) == 0)
        {
            current->info = student;
            return true;
        }
        current = current->next;
    }

    return false; // Không tìm thấy sinh viên cần cập nhật
}

// Tìm sinh viên theo mã sinh viên trong danh sách liên kết vòng
NodeSLL *findInCLL(NodeSLL *head, const char *studentID)
{
    if (head == NULL)
    {
        return NULL; // Danh sách rỗng
    }

    // Kiểm tra node đầu tiên
    if (strcmp(head->info.studentID, studentID) == 0)
    {
        return head;
    }

    // Kiểm tra các node còn lại
    NodeSLL *current = head->next;

    while (current != head)
    {
        if (strcmp(current->info.studentID, studentID) == 0)
        {
            return current;
        }
        current = current->next;
    }

    return NULL; // Không tìm thấy sinh viên
}

// Hiển thị danh sách sinh viên trong danh sách liên kết vòng
void displayCLL(NodeSLL *head)
{
    if (head == NULL)
    {
        cout << "Danh sách liên kết vòng rỗng!" << endl;
        return;
    }

    // Hiển thị tiêu đề
    cout << left << setw(10) << "Mã SV"
         << setw(20) << "Họ"
         << setw(20) << "Tên"
         << setw(15) << "Lớp"
         << setw(5) << "Điểm" << endl;
    cout << string(70, '-') << endl;

    // Hiển thị node đầu tiên
    NodeSLL *current = head;
    do
    {
        cout << left << setw(10) << current->info.studentID
             << setw(20) << current->info.firstName
             << setw(20) << current->info.lastName
             << setw(15) << current->info.studentClass
             << setw(5) << current->info.score << endl;
        current = current->next;
    } while (current != head);
}

// Giải phóng bộ nhớ cho danh sách liên kết vòng
void freeCLL(NodeSLL *&head)
{
    if (head == NULL)
    {
        return; // Danh sách đã rỗng
    }

    NodeSLL *current = head->next;
    NodeSLL *temp;

    // Xóa tất cả các node trừ node head
    while (current != head)
    {
        temp = current;
        current = current->next;
        delete temp;
    }

    // Xóa node head
    delete head;
    head = NULL;
}