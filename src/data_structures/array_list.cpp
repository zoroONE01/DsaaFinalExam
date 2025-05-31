#include "../../include/data_structures/array_list.h"
#include "../../include/ui/common_ui.h"
#include <iostream>

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
    return -1; // Không tìm thấy
}

// Xóa sinh viên theo mã sinh viên trong danh sách mảng
bool deleteFromArrayList(ArrayStudentList &list, const char *studentID)
{
    // Tìm sinh viên cần xóa
    int position = searchInArrayList(list, studentID);

    if (position != -1)
    {
        // Dịch chuyển các phần tử về phía trước để lấp đầy chỗ trống
        for (int i = position; i < list.count - 1; i++)
        {
            list.students[i] = list.students[i + 1];
        }
        list.count--;
        return true;
    }

    return false; // Không tìm thấy sinh viên
}

// Cập nhật sinh viên theo mã sinh viên trong danh sách mảng
bool updateInArrayList(ArrayStudentList &list, const Student &student)
{
    // Tìm sinh viên cần cập nhật
    int position = searchInArrayList(list, student.studentID);

    if (position != -1)
    {
        // Cập nhật thông tin sinh viên
        list.students[position] = student;
        return true;
    }

    return false; // Không tìm thấy sinh viên
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

// Tìm điểm cao nhất trong danh sách mảng
float findHighestScore(const ArrayStudentList &list)
{
    if (list.count == 0)
    {
        return 0.0f; // Trường hợp danh sách rỗng
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

// Tìm điểm thấp nhất trong danh sách mảng
float findLowestScore(const ArrayStudentList &list)
{
    if (list.count == 0)
    {
        return 0.0f; // Trường hợp danh sách rỗng
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
        return 0.0f; // Trường hợp danh sách rỗng
    }

    float sum = 0.0f;
    for (int i = 0; i < list.count; i++)
    {
        sum += list.students[i].score;
    }
    return sum / list.count;
}

// Tìm kiếm nhị phân sinh viên theo mã sinh viên (danh sách phải được sắp xếp trước)
int binarySearchArrayList(const ArrayStudentList &list, const char *studentID)
{
    int left = 0;
    int right = list.count - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(list.students[mid].studentID, studentID);

        if (cmp == 0)
        {
            return mid; // Tìm thấy
        }
        else if (cmp < 0)
        {
            left = mid + 1; // Tìm ở nửa phải
        }
        else
        {
            right = mid - 1; // Tìm ở nửa trái
        }
    }

    return -1; // Không tìm thấy
}
