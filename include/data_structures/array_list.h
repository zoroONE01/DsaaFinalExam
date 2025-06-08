#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "../core/student.h"
#include "../utils/constants.h"
#include <iostream>

using namespace std;

// ========== Cài đặt danh sách mảng ==========

// Định nghĩa cấu trúc cho danh sách sinh viên dạng mảng
struct ArrayStudentList
{
    Student students[MAX_STUDENTS];
    int count;
};

// Function declarations
void initArrayList(ArrayStudentList &list);
bool addToArrayList(ArrayStudentList &list, const Student &student);
bool deleteFromArrayList(ArrayStudentList &list, const char *studentID);
int searchInArrayList(const ArrayStudentList &list, const char *studentID);
bool updateInArrayList(ArrayStudentList &list, const Student &newInfo);
void displayArrayList(const ArrayStudentList &list);
float findHighestScore(const ArrayStudentList &list);
float findLowestScore(const ArrayStudentList &list);
float calculateAverageScore(const ArrayStudentList &list);

#endif // ARRAY_LIST_H