#ifndef STUDENT_STRUCT_H
#define STUDENT_STRUCT_H

#include <iostream>
#include <string>
#include "../utils/constants.h"

using namespace std;

// Định nghĩa cấu trúc Student (Sinh viên)
struct Student
{
    char studentID[MAX_STUDENT_ID_LENGTH];
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    char studentClass[MAX_CLASS_LENGTH];
    float score;
};

// Khai báo các hàm xử lý chuỗi UTF-8
int visualWidth(const string &str);
string centerAlign(const string &text, int width);
string centerAlign(float num, int width);

// Khai báo các hàm hiển thị sinh viên
void displayStudent(const Student &student);
void displayStudentInTable(const Student &student, int index);
void displayStudentDetailed(const Student &student);

#endif // STUDENT_STRUCT_H