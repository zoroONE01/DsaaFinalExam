#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "student_struct.h"
#include <iostream>
#include <iomanip>
#include "../ui/common_ui.h" // Include thư viện UI mới

using namespace std;

// ========== Cài đặt danh sách mảng ==========
const int MAX_STUDENTS = 100; // Kích thước tối đa của mảng

struct ArrayStudentList
{
    Student students[MAX_STUDENTS];
    int count; // Số lượng sinh viên hiện tại
};

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

// Cập nhật sinh viên theo mã sinh viên trong danh sách mảng
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

// Tìm kiếm sinh viên theo mã sinh viên trong danh sách mảng (tuần tự)
int searchInArrayList(const ArrayStudentList &list, const char *studentID)
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

// Hiển thị danh sách sinh viên từ mảng (sử dụng thư viện UI)
void displayArrayList(const ArrayStudentList &list)
{
    if (list.count == 0)
    {
        printWarning("Danh sách sinh viên rỗng!");
        return;
    }

    cout << BOLD << CYAN << "\n=== DANH SÁCH SINH VIÊN (" << list.count << " sinh viên) ===" << RESET << endl;

    displayStudentTableHeader();

    for (int i = 0; i < list.count; i++)
    {
        displayStudentInTable(list.students[i], i + 1);

        // Hiển thị dòng phân cách giữa các sinh viên nếu không phải sinh viên cuối cùng
        if (i < list.count - 1)
        {
            displayStudentTableSeparator();
        }
    }

    displayStudentTableFooter();
}

// Tìm sinh viên có điểm cao nhất trong danh sách mảng
float findHighestScore(const ArrayStudentList &list)
{
    if (list.count == 0)
    {
        return -1; // Danh sách rỗng
    }

    float highest = list.students[0].score;
    for (int i = 1; i < list.count; i++)
    {
        if (list.students[i].score > highest)
        {
            highest = list.students[i].score;
        }
    }

    return highest;
}

// Tìm sinh viên có điểm thấp nhất trong danh sách mảng
float findLowestScore(const ArrayStudentList &list)
{
    if (list.count == 0)
    {
        return -1; // Danh sách rỗng
    }

    float lowest = list.students[0].score;
    for (int i = 1; i < list.count; i++)
    {
        if (list.students[i].score < lowest)
        {
            lowest = list.students[i].score;
        }
    }

    return lowest;
}

// Tính điểm trung bình của danh sách mảng
float calculateAverageScore(const ArrayStudentList &list)
{
    if (list.count == 0)
    {
        return 0; // Danh sách rỗng
    }

    float sum = 0;
    for (int i = 0; i < list.count; i++)
    {
        sum += list.students[i].score;
    }

    return sum / list.count;
}

#endif // ARRAY_LIST_H