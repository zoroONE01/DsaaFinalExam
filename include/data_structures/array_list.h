#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "../utils/student.h"
#include "../utils/constants.h"

// Định nghĩa cấu trúc danh sách mảng
struct ArrayStudentList
{
    Student students[MAX_STUDENTS];
    int count; // Số lượng sinh viên hiện tại
};

// Khởi tạo danh sách mảng rỗng
void initArrayList(ArrayStudentList &list);

// Thêm sinh viên vào cuối danh sách mảng
bool addToArrayList(ArrayStudentList &list, const Student &student);

// Xóa sinh viên theo mã sinh viên trong danh sách mảng
bool deleteFromArrayList(ArrayStudentList &list, const char *studentID);

// Cập nhật thông tin sinh viên trong danh sách mảng
bool updateInArrayList(ArrayStudentList &list, const Student &student);

// Tìm sinh viên theo mã sinh viên trong danh sách mảng
int findInArrayList(const ArrayStudentList &list, const char *studentID);

// Tìm sinh viên theo mã sinh viên trong danh sách mảng (sử dụng tìm kiếm tuần tự)
int sequentialSearchInArrayList(const ArrayStudentList &list, const char *studentID);

// Tìm sinh viên theo mã sinh viên trong danh sách mảng (sử dụng tìm kiếm nhị phân) - danh sách phải được sắp xếp
int binarySearchInArrayList(const ArrayStudentList &list, const char *studentID, int left, int right);

// Hiển thị danh sách sinh viên trong danh sách mảng
void displayArrayList(const ArrayStudentList &list);

#endif // ARRAY_LIST_H
