#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>
#include "../utils/student.h"

// Hàm validate mã sinh viên
bool validateStudentID(const std::string &studentID);

// Hàm validate họ tên sinh viên
bool validateName(const std::string &name);

// Hàm validate lớp học
bool validateClass(const std::string &className);

// Hàm validate điểm số
bool validateScore(const std::string &scoreStr, float &score);

// Kiểm tra và hiển thị thông báo về mã sinh viên
bool validateAndShowStudentID(const std::string &studentID);

// Kiểm tra trùng lặp mã sinh viên trong các cấu trúc dữ liệu
bool validateAndShowDuplicateStudentID(const std::string &studentID, int dataStructureType, 
                                       const struct ArrayStudentList &arrayList, 
                                       struct NodeSLL *singlyLinkedList,
                                       struct NodeSLL *circularLinkedList, 
                                       struct NodeDLL *doublyLinkedListHead);

#endif // VALIDATION_H
