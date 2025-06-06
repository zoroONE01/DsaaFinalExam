#include "../../include/data_structures/doubly_linked_list.h"
#include "../../include/ui/common_ui.h"
#include <iostream>
#include <cstring>

using namespace std;

// Khởi tạo danh sách liên kết đôi rỗng
void initDLL(NodeDLL *&head, NodeDLL *&tail)
{
    head = NULL;
    tail = NULL;
}

// Tạo mới một node sinh viên cho danh sách liên kết đôi
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

    // Nếu danh sách rỗng
    if (head == NULL)
    {
        head = newNode;
        tail = newNode;
        return;
    }

    // Thêm vào đầu danh sách
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
}

// Thêm sinh viên vào cuối danh sách liên kết đôi
void addToTailDLL(NodeDLL *&head, NodeDLL *&tail, const Student &student)
{
    NodeDLL *newNode = createNodeDLL(student);

    // Nếu danh sách rỗng
    if (head == NULL)
    {
        head = newNode;
        tail = newNode;
        return;
    }

    // Thêm vào cuối danh sách
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
}

// Xóa sinh viên theo mã sinh viên trong danh sách liên kết đôi
bool deleteFromDLL(NodeDLL *&head, NodeDLL *&tail, const char *studentID)
{
    // Nếu danh sách rỗng
    if (head == NULL)
    {
        return false;
    }

    // Nếu sinh viên cần xóa là head
    if (strcmp(head->info.studentID, studentID) == 0)
    {
        NodeDLL *temp = head;

        // Nếu chỉ có một node
        if (head == tail)
        {
            head = NULL;
            tail = NULL;
        }
        else
        {
            head = head->next;
            head->prev = NULL;
        }

        delete temp;
        return true;
    }

    // Nếu sinh viên cần xóa là tail
    if (strcmp(tail->info.studentID, studentID) == 0)
    {
        NodeDLL *temp = tail;
        tail = tail->prev;
        tail->next = NULL;
        delete temp;
        return true;
    }

    // Tìm node cần xóa
    NodeDLL *current = head->next;
    while (current != NULL && strcmp(current->info.studentID, studentID) != 0)
    {
        current = current->next;
    }

    // Nếu không tìm thấy sinh viên
    if (current == NULL)
    {
        return false;
    }

    // Xóa node
    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    return true;
}

// Cập nhật sinh viên theo mã sinh viên trong danh sách liên kết đôi
bool updateInDLL(NodeDLL *head, const Student &student)
{
    NodeDLL *current = head;
    while (current != NULL)
    {
        if (strcmp(current->info.studentID, student.studentID) == 0)
        {
            current->info = student;
            return true;
        }
        current = current->next;
    }

    return false; // Không tìm thấy sinh viên
}

// Tìm kiếm sinh viên theo mã sinh viên trong danh sách liên kết đôi
NodeDLL *searchInDLL(NodeDLL *head, const char *studentID)
{
    NodeDLL *current = head;
    while (current != NULL)
    {
        if (strcmp(current->info.studentID, studentID) == 0)
        {
            return current; // Trả về node tìm thấy
        }
        current = current->next;
    }

    return NULL; // Không tìm thấy sinh viên
}

// Đếm số lượng sinh viên trong danh sách liên kết đôi
int countDLL(NodeDLL *head)
{
    int count = 0;
    NodeDLL *current = head;

    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    return count;
}

// Hiển thị danh sách sinh viên từ danh sách liên kết đôi
void displayDLL(NodeDLL *head)
{
    if (head == NULL)
    {
        printWarning("Danh sách sinh viên rỗng!");
        return;
    }

    int count = countDLL(head);
    cout << BOLD << CYAN << "\n=== DANH SÁCH SINH VIÊN LIÊN KẾT ĐÔI (" << count << " sinh viên) ===" << RESET << endl;

    displayStudentTableHeader();

    NodeDLL *current = head;
    int index = 1;

    while (current != NULL)
    {
        displayStudentInTable(current->info, index);

        // Hiển thị dòng phân cách nếu không phải là node cuối cùng
        if (current->next != NULL)
        {
            displayStudentTableSeparator();
        }

        current = current->next;
        index++;
    }

    displayStudentTableFooter();

    // Hiển thị đặc trưng của danh sách liên kết đôi
    cout << MAGENTA << "\n→ Đặc điểm danh sách liên kết đôi: Mỗi node có liên kết tới node trước và node sau" << RESET << endl;
}

// Giải phóng bộ nhớ danh sách liên kết đôi
void freeDLL(NodeDLL *&head, NodeDLL *&tail)
{
    while (head != NULL)
    {
        NodeDLL *temp = head;
        head = head->next;
        delete temp;
    }
    tail = NULL;
}
