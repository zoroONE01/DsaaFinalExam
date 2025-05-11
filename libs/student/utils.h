#ifndef UTILS_H
#define UTILS_H

#include "student_struct.h"
#include "array_list.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// ========== Đọc dữ liệu từ file CSV ==========
bool readFromCSVFile(const char* filename, ArrayStudentList &list) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;  // Không thể mở file
    }
    
    // Khởi tạo danh sách rỗng
    initArrayList(list);
    
    string line;
    // Đọc dòng tiêu đề (nếu có)
    getline(file, line);
    
    // Đọc từng dòng dữ liệu
    while (getline(file, line)) {
        if (line.empty()) {
            continue;  // Bỏ qua dòng trống
        }
        
        Student student;
        char buffer[200];
        strcpy(buffer, line.c_str());
        
        // Phân tích dữ liệu CSV bằng phân tách dấu phẩy
        char* token = strtok(buffer, ",");
        if (token) strcpy(student.studentID, token);
        
        token = strtok(NULL, ",");
        if (token) strcpy(student.firstName, token);
        
        token = strtok(NULL, ",");
        if (token) strcpy(student.lastName, token);
        
        token = strtok(NULL, ",");
        if (token) strcpy(student.studentClass, token);
        
        token = strtok(NULL, ",");
        if (token) student.score = atof(token);
        
        // Thêm sinh viên vào danh sách
        addToArrayList(list, student);
    }
    
    file.close();
    return true;
}

#endif // UTILS_H