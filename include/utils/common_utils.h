#ifndef UTILS_H
#define UTILS_H

#include "../core/student.h"
#include "../data_structures/array_list.h"
#include "validation.h"
#include "../ui/common_ui.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// ========== Khai báo các hàm tiện ích chung ==========

// Đọc dữ liệu từ file CSV
bool readFromCSVFile(const char *filename, ArrayStudentList &list);

// Hàm trim() để loại bỏ khoảng trắng ở đầu và cuối chuỗi
string trim(string str);

#endif // UTILS_H