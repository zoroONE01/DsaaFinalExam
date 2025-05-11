#ifndef STUDENT_STRUCT_H
#define STUDENT_STRUCT_H

#include <iostream>
#include <cstring>
#include <iomanip>
#include <sstream>
#include "../ui/ui_library.h"

using namespace std;

// Định nghĩa cấu trúc Student (Sinh viên)
struct Student
{
    char studentID[20];
    char firstName[50];
    char lastName[50];
    char studentClass[20];
    float score;
};

// Hàm hỗ trợ căn giữa
string centerAlign(const string &text, int width)
{
    int padding = width - text.length();
    int padLeft = padding / 2;
    int padRight = padding - padLeft;
    return string(padLeft, ' ') + text + string(padRight, ' ');
}

// Hàm hỗ trợ căn giữa cho số
string centerAlign(float num, int width)
{
    stringstream ss;
    ss << fixed << setprecision(1) << num;
    return centerAlign(ss.str(), width);
}

// Hiển thị thông tin sinh viên
void displayStudent(const Student &student)
{
    displayStudentDetailed(student);
}

// Cài đặt các hàm hiển thị sinh viên được khai báo trong ui_library.h
void displayStudentInTable(const Student &student, int index)
{
    string indexStr = to_string(index);
    string studentIDStr = student.studentID;
    string firstNameStr = student.firstName;
    string lastNameStr = student.lastName;
    string classStr = student.studentClass;
    stringstream scoreStream;
    scoreStream << fixed << setprecision(1) << student.score;
    string scoreStr = scoreStream.str();

    cout << BOLD << "│" << RESET << " " << centerAlign(indexStr, 6) << " ";
    cout << BOLD << "│" << RESET << " " << centerAlign(studentIDStr, 14) << " ";
    cout << BOLD << "│" << RESET << " " << centerAlign(firstNameStr, 19) << " ";
    cout << BOLD << "│" << RESET << " " << centerAlign(lastNameStr, 19) << " ";
    cout << BOLD << "│" << RESET << " " << centerAlign(classStr, 18) << " ";
    cout << BOLD << "│" << RESET << " ";

    // Hiển thị điểm với màu sắc dựa trên giá trị
    if (student.score >= 8.0)
    {
        cout << GREEN << centerAlign(scoreStr, 9) << RESET;
    }
    else if (student.score >= 6.5)
    {
        cout << BLUE << centerAlign(scoreStr, 9) << RESET;
    }
    else if (student.score >= 5.0)
    {
        cout << YELLOW << centerAlign(scoreStr, 9) << RESET;
    }
    else
    {
        cout << RED << centerAlign(scoreStr, 9) << RESET;
    }
    cout << " " << BOLD << "│" << RESET << endl;
}

// Hàm hiển thị thông tin sinh viên
void displayStudentDetailed(const Student &student)
{
    cout << BOLD << "┌─────────────────────────────────────┐" << RESET << endl;
    cout << BOLD << "│" << CYAN << " THÔNG TIN SINH VIÊN                " << RESET << BOLD << "│" << RESET << endl;
    cout << BOLD << "├─────────────────────────────────────┤" << RESET << endl;

    cout << BOLD << "│ " << YELLOW << "Mã SV:  " << RESET << setw(26) << left << student.studentID << BOLD << " │" << RESET << endl;
    cout << BOLD << "│ " << YELLOW << "Họ:     " << RESET << setw(26) << left << student.firstName << BOLD << " │" << RESET << endl;
    cout << BOLD << "│ " << YELLOW << "Tên:    " << RESET << setw(26) << left << student.lastName << BOLD << " │" << RESET << endl;
    cout << BOLD << "│ " << YELLOW << "Lớp:    " << RESET << setw(26) << left << student.studentClass << BOLD << " │" << RESET << endl;

    // Màu sắc khác nhau dựa trên điểm số
    cout << BOLD << "│ " << YELLOW << "Điểm:   " << RESET;
    if (student.score >= 8.0)
    {
        cout << GREEN << setw(26) << left << student.score << RESET;
    }
    else if (student.score >= 6.5)
    {
        cout << BLUE << setw(26) << left << student.score << RESET;
    }
    else if (student.score >= 5.0)
    {
        cout << YELLOW << setw(26) << left << student.score << RESET;
    }
    else
    {
        cout << RED << setw(26) << left << student.score << RESET;
    }
    cout << BOLD << " │" << RESET << endl;

    cout << BOLD << "└─────────────────────────────────────┘" << RESET << endl;
}

#endif // STUDENT_STRUCT_H