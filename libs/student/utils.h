#ifndef UTILS_H
#define UTILS_H

#include "student_struct.h"
#include "array_list.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// ========== Đọc dữ liệu từ file CSV ==========
bool readFromCSVFile(const char *filename, ArrayStudentList &list)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        return false; // Không thể mở file
    }

    // Khởi tạo danh sách rỗng
    initArrayList(list);

    string line;
    // Đọc dòng tiêu đề (nếu có)
    getline(file, line);

    // Đọc từng dòng dữ liệu
    while (getline(file, line))
    {
        if (line.empty())
        {
            continue; // Bỏ qua dòng trống
        }

        Student student;
        char buffer[200];
        strcpy(buffer, line.c_str());

        // Phân tích dữ liệu CSV bằng phân tách dấu phẩy
        char *token = strtok(buffer, ",");
        if (token)
            strcpy(student.studentID, token);

        token = strtok(NULL, ",");
        if (token)
            strcpy(student.firstName, token);

        token = strtok(NULL, ",");
        if (token)
            strcpy(student.lastName, token);

        token = strtok(NULL, ",");
        if (token)
            strcpy(student.studentClass, token);

        token = strtok(NULL, ",");
        if (token)
            student.score = atof(token);

        // Thêm sinh viên vào danh sách
        addToArrayList(list, student);
    }

    file.close();
    return true;
}

// Hàm trim() để loại bỏ khoảng trắng ở đầu và cuối chuỗi
string trim(string str)
{
    // Loại bỏ khoảng trắng ở đầu chuỗi
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    if (start == string::npos)
        return "";

    // Loại bỏ khoảng trắng ở cuối chuỗi
    size_t end = str.find_last_not_of(" \t\n\r\f\v");

    // Trả về chuỗi đã được trim
    return str.substr(start, end - start + 1);
}

#endif // UTILS_H