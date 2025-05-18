#ifndef VALIDATION_H
#define VALIDATION_H

#include "student_struct.h"
#include "../ui/common_ui.h"
#include <iostream>
#include <regex>
#include <string>
#include <limits>
#include <cstring>

using namespace std;

// Hàm trả về thông báo lỗi chung với tên trường
string getInvalidFieldMessage(const char *fieldName)
{
    string message = fieldName;
    message += " không hợp lệ.";
    return message;
}

// Hàm trả về thông báo lỗi cho độ dài chuỗi vượt quá giới hạn
string getStringLengthValidationMessage(const char *fieldName, size_t maxLength)
{
    string message = "Độ dài ";
    message += fieldName;
    message += " vượt quá giới hạn cho phép.";
    return message;
}

// Hàm kiểm tra tính hợp lệ của điểm số
bool validateScore(float score)
{
    return score >= 0 && score <= 10;
}

// Các hàm validate bằng regex
bool validateStudentID(const string &studentID)
{
    // Mã sinh viên gồm chữ và số, từ 3 đến 19 ký tự (vì mảng 20 ký tự cần 1 byte cho null terminator)
    regex pattern("^[a-zA-Z0-9]{3,19}$");
    return regex_match(studentID, pattern);
}

bool validateName(const string &name)
{
    // Tên họ chỉ được chứa chữ cái, khoảng trắng và dấu gạch ngang
    // Giới hạn độ dài tối đa 49 ký tự (vì mảng 50 ký tự cần 1 byte cho null terminator)
    if (name.length() > 49)
    {
        return false;
    }
    regex pattern("^[a-zA-ZÀÁÂÃÈÉÊÌÍÒÓÔÕÙÚĂĐĨŨƠàáâãèéêìíòóôõùúăđĩũơƯĂẠẢẤẦẨẪẬẮẰẲẴẶẸẺẼỀỀỂưăạảấầẩẫậắằẳẵặẹẻẽềềểỄỆỉịọỏốồổỗộớờởỡợụủứừửữựỳỵỷỹ\\s-]+$");
    return regex_match(name, pattern);
}

bool validateClassName(const string &className)
{
    // Tên lớp có thể chứa chữ cái, số và một số ký tự đặc biệt
    // Giới hạn độ dài từ 2 đến 19 ký tự (vì mảng 20 ký tự cần 1 byte cho null terminator)
    regex pattern("^[a-zA-Z0-9\\._-]{2,19}$");
    return regex_match(className, pattern);
}

// Hàm kiểm tra và hiển thị thông báo lỗi cho mã sinh viên
bool validateAndShowStudentID(const string &studentID)
{
    bool isValid = validateStudentID(studentID);
    if (!isValid)
    {
        printError(getInvalidFieldMessage("Mã sinh viên").c_str());
        printWarning("Mã sinh viên phải có từ 3-19 ký tự và chỉ bao gồm chữ cái và số.");
    }
    return isValid;
}

// Hàm kiểm tra và hiển thị thông báo lỗi cho họ và tên
bool validateAndShowName(const string &name)
{
    bool isValid = validateName(name);
    if (!isValid)
    {
        printError(getInvalidFieldMessage("Họ/tên").c_str());
        printWarning("Họ/tên chỉ được chứa chữ cái, dấu cách và dấu gạch ngang, tối đa 49 ký tự.");
    }
    return isValid;
}

// Hàm kiểm tra và hiển thị thông báo lỗi cho tên lớp
bool validateAndShowClassName(const string &className)
{
    bool isValid = validateClassName(className);
    if (!isValid)
    {
        printError(getInvalidFieldMessage("Tên lớp").c_str());
        printWarning("Tên lớp phải có từ 2-19 ký tự và chỉ chứa chữ cái, số, dấu gạch ngang, dấu chấm và gạch dưới.");
    }
    return isValid;
}

// Hàm kiểm tra và hiển thị thông báo lỗi cho điểm số
bool validateAndShowScore(float score)
{
    bool isValid = validateScore(score);
    if (!isValid)
    {
        printError(getInvalidFieldMessage("Điểm số").c_str());
        printWarning("Điểm phải là số thực từ 0 đến 10.");
    }
    return isValid;
}

// Các hàm nhập thông tin sẽ được định nghĩa trong main.cpp

#endif // VALIDATION_H