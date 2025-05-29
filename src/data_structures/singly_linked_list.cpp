#include "../../include/data_structures/singly_linked_list.h"
#include "../../include/ui/ui_common.h"
#include "../../include/ui/ui_constants.h"
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

// Khởi tạo danh sách liên kết đơn rỗng
void initSLL(NodeSLL *&head)
{
    head = NULL;
}

// Tạo mới một node sinh viên
NodeSLL *createNodeSLL(const Student &student)
{
    NodeSLL *newNode = new NodeSLL;
    newNode->info = student;
    newNode->next = NULL;
    return newNode;
}

// Thêm sinh viên vào đầu danh sách liên kết đơn
void addToHeadSLL(NodeSLL *&head, const Student &student)
{
    NodeSLL *newNode = createNodeSLL(student);
    newNode->next = head;
    head = newNode;
}

// Thêm sinh viên vào cuối danh sách liên kết đơn
void addToTailSLL(NodeSLL *&head, const Student &student)
{
    NodeSLL *newNode = createNodeSLL(student);

    // Nếu danh sách rỗng, node mới sẽ là head
    if (head == NULL)
    {
        head = newNode;
        return;
    }

    // Tìm node cuối cùng
    NodeSLL *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }

    // Thêm node mới vào cuối danh sách
    current->next = newNode;
}

// Xóa sinh viên theo mã sinh viên từ danh sách liên kết đơn
bool deleteFromSLL(NodeSLL *&head, const char *studentID)
{
    // Nếu danh sách rỗng
    if (head == NULL)
    {
        return false;
    }

    // Nếu sinh viên cần xóa là head
    if (strcmp(head->info.studentID, studentID) == 0)
    {
        NodeSLL *temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    // Tìm node trước node cần xóa
    NodeSLL *current = head;
    while (current->next != NULL && strcmp(current->next->info.studentID, studentID) != 0)
    {
        current = current->next;
    }

    // Nếu không tìm thấy sinh viên
    if (current->next == NULL)
    {
        return false;
    }

    // Xóa node
    NodeSLL *temp = current->next;
    current->next = current->next->next;
    delete temp;
    return true;
}

// Cập nhật thông tin sinh viên trong danh sách liên kết đơn
bool updateInSLL(NodeSLL *&head, const Student &student)
{
    NodeSLL *current = head;
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

// Tìm sinh viên theo mã sinh viên trong danh sách liên kết đơn
NodeSLL *findInSLL(NodeSLL *head, const char *studentID)
{
    NodeSLL *current = head;
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

// Hiển thị danh sách sinh viên trong danh sách liên kết đơn
void displaySLL(NodeSLL *head)
{
    if (head == NULL)
    {
        printWarning("Danh sách sinh viên rỗng!");
        return;
    }

    // Đếm số lượng sinh viên
    int count = 0;
    NodeSLL *countNode = head;
    while (countNode != NULL)
    {
        count++;
        countNode = countNode->next;
    }

    cout << BOLD << CYAN << "\n=== DANH SÁCH SINH VIÊN LIÊN KẾT ĐƠN (" << count << " sinh viên) ===" << RESET << endl;

    displayStudentTableHeader();

    // Hiển thị sinh viên
    NodeSLL *current = head;
    int index = 1;
    while (current != NULL)
    {
        // Hiện thị thông tin sinh viên
        cout << "│ " << setw(7) << left << index << " │";
        cout << " " << setw(15) << left << current->info.studentID << " │";
        cout << " " << setw(20) << left << current->info.firstName << " │";
        cout << " " << setw(20) << left << current->info.lastName << " │";
        cout << " " << setw(19) << left << current->info.studentClass << " │";
        cout << " " << setw(9) << fixed << setprecision(2) << current->info.score << " │" << endl;

        // Hiển thị dòng phân cách nếu không phải là node cuối cùng
        if (current->next != NULL)
        {
            cout << "├────────┼────────────────┼─────────────────────┼─────────────────────┼────────────────────┼───────────┤" << endl;
        }

        current = current->next;
        index++;
    }

    displayStudentTableFooter();
}

// Giải phóng bộ nhớ cho danh sách liên kết đơn
void freeSLL(NodeSLL *&head)
{
    while (head != NULL)
    {
        NodeSLL *temp = head;
        head = head->next;
        delete temp;
    }
}
