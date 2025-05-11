#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

#include "student_struct.h"
#include <iostream>

using namespace std;

// ========== Cài đặt danh sách liên kết vòng ==========

// Sử dụng cùng cấu trúc NodeSLL từ danh sách liên kết đơn
#ifndef NODE_SLL_DEFINED
#define NODE_SLL_DEFINED
// Forward declaration - thực tế sẽ sử dụng định nghĩa từ singly_linked_list.h
struct NodeSLL;
#endif

// Khởi tạo danh sách liên kết vòng rỗng
void initCLL(NodeSLL *&head)
{
    head = NULL;
}

// Thêm sinh viên vào danh sách liên kết vòng
void addToCLL(NodeSLL *&head, const Student &student)
{
    NodeSLL *newNode = new NodeSLL;
    newNode->info = student;

    // Nếu danh sách rỗng
    if (head == NULL)
    {
        head = newNode;
        head->next = head; // Trỏ đến chính nó để tạo vòng
        return;
    }

    // Tìm node cuối cùng (node trỏ tới head)
    NodeSLL *current = head;
    while (current->next != head)
    {
        current = current->next;
    }

    // Thêm node mới vào cuối và tạo liên kết vòng
    current->next = newNode;
    newNode->next = head;
}

// Xóa sinh viên theo mã sinh viên trong danh sách liên kết vòng
bool deleteFromCLL(NodeSLL *&head, const char *studentID)
{
    // Nếu danh sách rỗng
    if (head == NULL)
    {
        return false;
    }

    // Nếu danh sách chỉ có 1 node
    if (head->next == head)
    {
        if (strcmp(head->info.studentID, studentID) == 0)
        {
            delete head;
            head = NULL;
            return true;
        }
        return false;
    }

    // Nếu sinh viên cần xóa là head
    if (strcmp(head->info.studentID, studentID) == 0)
    {
        // Tìm node cuối cùng
        NodeSLL *last = head;
        while (last->next != head)
        {
            last = last->next;
        }

        NodeSLL *temp = head;
        head = head->next;
        last->next = head; // Cập nhật liên kết vòng
        delete temp;
        return true;
    }

    // Tìm node trước node cần xóa
    NodeSLL *current = head;
    while (current->next != head && strcmp(current->next->info.studentID, studentID) != 0)
    {
        current = current->next;
    }

    // Nếu không tìm thấy sinh viên
    if (current->next == head)
    {
        return false;
    }

    // Xóa node
    NodeSLL *temp = current->next;
    current->next = temp->next;
    delete temp;
    return true;
}

// Cập nhật sinh viên theo mã sinh viên trong danh sách liên kết vòng
bool updateInCLL(NodeSLL *head, const Student &student)
{
    // Nếu danh sách rỗng
    if (head == NULL)
    {
        return false;
    }

    NodeSLL *current = head;
    do
    {
        if (strcmp(current->info.studentID, student.studentID) == 0)
        {
            current->info = student;
            return true;
        }
        current = current->next;
    } while (current != head);

    return false; // Không tìm thấy sinh viên
}

// Tìm kiếm sinh viên theo mã sinh viên trong danh sách liên kết vòng
NodeSLL *searchInCLL(NodeSLL *head, const char *studentID)
{
    if (head == NULL)
    {
        return NULL;
    }

    NodeSLL *current = head;
    do
    {
        if (strcmp(current->info.studentID, studentID) == 0)
        {
            return current;
        }
        current = current->next;
    } while (current != head);

    return NULL; // Không tìm thấy sinh viên
}

// Đếm số lượng sinh viên trong danh sách liên kết vòng
int countCLL(NodeSLL *head)
{
    if (head == NULL)
    {
        return 0;
    }

    int count = 1; // Bắt đầu với head
    NodeSLL *current = head->next;

    while (current != head)
    {
        count++;
        current = current->next;
    }

    return count;
}

// Hiển thị danh sách sinh viên từ danh sách liên kết vòng
void displayCLL(NodeSLL *head)
{
    if (head == NULL)
    {
        printWarning("Danh sách sinh viên rỗng!");
        return;
    }

    int count = countCLL(head);
    cout << BOLD << CYAN << "\n=== DANH SÁCH SINH VIÊN LIÊN KẾT VÒNG (" << count << " sinh viên) ===" << RESET << endl;

    displayStudentTableHeader();

    NodeSLL *current = head;
    int index = 1;

    do
    {
        displayStudentInTable(current->info, index);

        // Hiển thị dòng phân cách nếu không phải là node cuối cùng
        if (current->next != head)
        {
            displayStudentTableSeparator();
        }

        current = current->next;
        index++;
    } while (current != head);

    displayStudentTableFooter();

    // Hiển thị đặc trưng của danh sách liên kết vòng
    cout << MAGENTA << "\n→ Đặc điểm danh sách liên kết vòng: Node cuối trỏ về node đầu" << RESET << endl;
}

// Giải phóng bộ nhớ danh sách liên kết vòng
void freeCLL(NodeSLL *&head)
{
    if (head == NULL)
    {
        return;
    }

    NodeSLL *current = head;
    NodeSLL *next;

    do
    {
        next = current->next;
        delete current;
        current = next;
    } while (current != head);

    head = NULL;
}

#endif // CIRCULAR_LINKED_LIST_H