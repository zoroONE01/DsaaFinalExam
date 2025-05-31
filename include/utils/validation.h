#ifndef VALIDATION_H
#define VALIDATION_H

#include "../core/student.h"
#include "constants.h"
#include "error_handling.h"
#include "../ui/common_ui.h"
#include <iostream>
#include <regex>
#include <string>
#include <limits>
#include <cstring>

using namespace std;

// ========== Khai báo các hàm validation ==========

// Hàm trả về thông báo lỗi chung với tên trường
string getInvalidFieldMessage(const char *fieldName);

// Hàm trả về thông báo lỗi cho độ dài chuỗi vượt quá giới hạn
string getStringLengthValidationMessage(const char *fieldName, size_t maxLength);

// Hàm kiểm tra tính hợp lệ của điểm số
bool validateScore(float score);

// Các hàm validate bằng regex
bool validateStudentID(const string &studentID);
bool validateName(const string &name);
bool validateClassName(const string &className);

// Hàm kiểm tra và hiển thị thông báo lỗi cho mã sinh viên
bool validateAndShowStudentID(const string &studentID);

// Hàm kiểm tra và hiển thị thông báo lỗi cho họ và tên
bool validateAndShowName(const string &name);

// Hàm kiểm tra và hiển thị thông báo lỗi cho tên lớp
bool validateAndShowClassName(const string &className);

// Hàm kiểm tra và hiển thị thông báo lỗi cho điểm số
bool validateAndShowScore(float score);

#endif // VALIDATION_H