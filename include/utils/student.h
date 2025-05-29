#ifndef STUDENT_H
#define STUDENT_H

// Định nghĩa cấu trúc sinh viên (Student)
struct Student
{
    char studentID[20];    // Mã sinh viên
    char firstName[50];    // Họ
    char lastName[50];     // Tên
    char studentClass[20]; // Lớp
    float score;           // Điểm
};

#endif // STUDENT_H
