#ifndef UTILS_H
#define UTILS_H

#include <string>
#include "../utils/student.h"

// Các hàm tiện ích chung

// Hàm xóa khoảng trắng thừa ở hai đầu chuỗi
std::string trim(const std::string &str);

// Tính độ rộng hiển thị thực tế của chuỗi UTF-8
int visualWidth(const std::string &str);

// Hàm chuyển đổi chuỗi thành chữ hoa
std::string toUpperCase(const std::string &str);

// Hàm chuyển đổi chuỗi thành chữ thường
std::string toLowerCase(const std::string &str);

// Hàm xóa buffer đầu vào
void clearInputBuffer();

// Hiển thị thông tin một sinh viên
void displayStudent(const Student &student);

#endif // UTILS_H
