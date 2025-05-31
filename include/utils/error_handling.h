#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include <iostream>
#include <string>
#include "constants.h"
#include "../ui/common_ui.h"

using namespace std;

// ========== Enum định nghĩa các loại lỗi ==========
enum ErrorType
{
    ERROR_INVALID_INPUT,
    ERROR_DUPLICATE_STUDENT_ID,
    ERROR_STUDENT_NOT_FOUND,
    ERROR_DATA_STRUCTURE_FULL,
    ERROR_DATA_STRUCTURE_EMPTY,
    ERROR_FILE_NOT_FOUND,
    ERROR_INVALID_FILE_FORMAT,
    ERROR_MEMORY_ALLOCATION,
    ERROR_INVALID_SCORE_RANGE,
    ERROR_INVALID_STUDENT_ID_FORMAT,
    ERROR_INVALID_NAME_FORMAT,
    ERROR_INVALID_CLASS_FORMAT
};

// ========== Struct để lưu trữ thông tin lỗi ==========
struct ErrorInfo
{
    ErrorType type;
    string message;
    string details;
};

// ========== Hàm tạo thông điệp lỗi ==========
string createErrorMessage(ErrorType type, const string &context = "");

// ========== Hàm hiển thị lỗi có định dạng ==========
void displayError(ErrorType type, const string &context = "");

// ========== Hàm hiển thị cảnh báo có định dạng ==========
void displayWarning(const string &message);

// ========== Hàm hiển thị thông tin có định dạng ==========
void displayInfo(const string &message);

// ========== Hàm kiểm tra và hiển thị lỗi validation ==========
bool validateAndDisplayError(bool isValid, ErrorType errorType, const string &context = "");

#endif // ERROR_HANDLING_H
