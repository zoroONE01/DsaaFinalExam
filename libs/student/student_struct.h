#ifndef STUDENT_STRUCT_H
#define STUDENT_STRUCT_H

#include <iostream>
#include <cstring>

using namespace std;

// Định nghĩa cấu trúc Student (Sinh viên)
struct Student {
    char studentID[20];
    char firstName[50];
    char lastName[50];
    char studentClass[20];
    float score;
};

// Hiển thị thông tin sinh viên
void displayStudent(const Student &student) {
    cout << "Mã SV: " << student.studentID << "\n";
    cout << "Họ: " << student.firstName << "\n";
    cout << "Tên: " << student.lastName << "\n";
    cout << "Lớp: " << student.studentClass << "\n";
    cout << "Điểm: " << student.score << "\n";
}

#endif // STUDENT_STRUCT_H