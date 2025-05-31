#include "../../include/data_structures/array_list.h"
#include "../../include/ui/ui_common.h"
#include "../../include/ui/ui_constants.h"
#include <iostream>
#include <cstring>

using namespace std;

// Khởi tạo danh sách mảng rỗng
void initArrayList(ArrayStudentList &list)
{
    list.count = 0;
}

// Thêm sinh viên vào cuối danh sách mảng
bool addToArrayList(ArrayStudentList &list, const Student &student)
{
    // Kiểm tra nếu mảng đã đầy
    if (list.count >= MAX_STUDENTS)
    {
        return false; // Danh sách đã đầy
    }

    // Thêm sinh viên vào cuối danh sách
    list.students[list.count] = student;
    list.count++;
    return true;
}

// Xóa sinh viên theo mã sinh viên trong danh sách mảng
bool deleteFromArrayList(ArrayStudentList &list, const char *studentID)
{
    // Tìm vị trí của sinh viên cần xóa
    int position = -1;
    for (int i = 0; i < list.count; i++)
    {
        if (strcmp(list.students[i].studentID, studentID) == 0)
        {
            position = i;
            break;
        }
    }

    if (position == -1)
    {
        return false; // Không tìm thấy sinh viên
    }

    // Di chuyển tất cả các sinh viên phía sau về trước một vị trí
    for (int i = position; i < list.count - 1; i++)
    {
        list.students[i] = list.students[i + 1];
    }

    list.count--;
    return true;
}

// Cập nhật thông tin sinh viên trong danh sách mảng
bool updateInArrayList(ArrayStudentList &list, const Student &student)
{
    // Tìm sinh viên cần cập nhật
    for (int i = 0; i < list.count; i++)
    {
        if (strcmp(list.students[i].studentID, student.studentID) == 0)
        {
            // Cập nhật thông tin sinh viên
            list.students[i] = student;
            return true;
        }
    }

    return false; // Không tìm thấy sinh viên
}

// Tìm sinh viên theo mã sinh viên trong danh sách mảng
int findInArrayList(const ArrayStudentList &list, const char *studentID)
{
    return sequentialSearchInArrayList(list, studentID);
}

// Tìm sinh viên theo mã sinh viên bằng tìm kiếm tuần tự
int sequentialSearchInArrayList(const ArrayStudentList &list, const char *studentID)
{
    for (int i = 0; i < list.count; i++)
    {
        if (strcmp(list.students[i].studentID, studentID) == 0)
        {
            return i; // Trả về vị trí tìm thấy
        }
    }

    return -1; // Không tìm thấy sinh viên
}

// Tìm sinh viên theo mã sinh viên bằng tìm kiếm nhị phân
int binarySearchInArrayList(const ArrayStudentList &list, const char *studentID, int left, int right)
{
    if (right >= left)
    {
        int mid = left + (right - left) / 2;

        // Nếu phần tử ở giữa là số cần tìm
        if (strcmp(list.students[mid].studentID, studentID) == 0)
            return mid;

        // Nếu phần tử nhỏ hơn mid, thì nó chỉ có thể
        // nằm trong mảng con bên trái
        if (strcmp(list.students[mid].studentID, studentID) > 0)
            return binarySearchInArrayList(list, studentID, left, mid - 1);

        // Ngược lại, phần tử chỉ có thể nằm
        // trong mảng con bên phải
        return binarySearchInArrayList(list, studentID, mid + 1, right);
    }

    // Không tìm thấy
    return -1;
}

// Hiển thị danh sách sinh viên trong danh sách mảng
void displayArrayList(const ArrayStudentList &list)
{
    if (list.count == 0)
    {
        printWarning("Danh sách sinh viên rỗng!");
        return;
    }

    cout << BOLD << CYAN << "\n=== DANH SÁCH SINH VIÊN MẢNG (" << list.count << " sinh viên) ===" << COLOR_RESET << endl;

    displayStudentTableHeader();

    for (int i = 0; i < list.count; i++)
    {
        displayStudentRow(list.students[i]);

        // Hiển thị dòng phân cách nếu không phải là dòng cuối cùng
        if (i < list.count - 1)
        {
            cout << "├────────┼────────────────┼─────────────────────┼─────────────────────┼────────────────────┼───────────┤" << endl;
        }
    }

    displayStudentTableFooter();
}
