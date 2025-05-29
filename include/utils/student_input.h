#ifndef STUDENT_INPUT_H
#define STUDENT_INPUT_H

#include "student.h"
#include "../data_structures/array_list.h"

// Hàm nhập thông tin sinh viên từ bàn phím
bool inputStudent(Student &student);

// Hàm nhập mã sinh viên từ bàn phím
bool inputStudentID(char *studentID);

// Hàm nhập điểm số sinh viên từ bàn phím
bool inputStudentScore(float &score);

// Hàm đọc dữ liệu sinh viên từ file CSV
bool readStudentsFromCSV(const char *filename, ArrayStudentList &list);

#endif // STUDENT_INPUT_H