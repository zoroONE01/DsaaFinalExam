#include "../../include/utils/error_handling.h"

using namespace std;

// ========== Hàm tạo thông điệp lỗi ==========
string createErrorMessage(ErrorType type, const string &context)
{
    string baseMessage;

    switch (type)
    {
    case ERROR_INVALID_INPUT:
        baseMessage = "Dữ liệu nhập vào không hợp lệ";
        break;
    case ERROR_DUPLICATE_STUDENT_ID:
        baseMessage = "Mã sinh viên đã tồn tại trong hệ thống";
        break;
    case ERROR_STUDENT_NOT_FOUND:
        baseMessage = "Không tìm thấy sinh viên";
        break;
    case ERROR_DATA_STRUCTURE_FULL:
        baseMessage = "Cấu trúc dữ liệu đã đầy";
        break;
    case ERROR_DATA_STRUCTURE_EMPTY:
        baseMessage = "Cấu trúc dữ liệu rỗng";
        break;
    case ERROR_FILE_NOT_FOUND:
        baseMessage = "Không tìm thấy file";
        break;
    case ERROR_INVALID_FILE_FORMAT:
        baseMessage = "Định dạng file không hợp lệ";
        break;
    case ERROR_MEMORY_ALLOCATION:
        baseMessage = "Lỗi cấp phát bộ nhớ";
        break;
    case ERROR_INVALID_SCORE_RANGE:
        baseMessage = "Điểm số phải trong khoảng " + to_string((int)MIN_SCORE) + " - " + to_string((int)MAX_SCORE);
        break;
    case ERROR_INVALID_STUDENT_ID_FORMAT:
        baseMessage = "Mã sinh viên phải từ 3-" + to_string(MAX_STUDENT_ID_LENGTH - 1) + " ký tự (chữ và số)";
        break;
    case ERROR_INVALID_NAME_FORMAT:
        baseMessage = "Tên chỉ được chứa chữ cái, khoảng trắng và dấu gạch ngang";
        break;
    case ERROR_INVALID_CLASS_FORMAT:
        baseMessage = "Tên lớp không hợp lệ";
        break;
    default:
        baseMessage = "Lỗi không xác định";
        break;
    }

    if (!context.empty())
    {
        return baseMessage + ": " + context;
    }

    return baseMessage;
}

// ========== Hàm hiển thị lỗi có định dạng ==========
void displayError(ErrorType type, const string &context)
{
    string errorMessage = createErrorMessage(type, context);
    printError(errorMessage.c_str());
}

// ========== Hàm hiển thị cảnh báo có định dạng ==========
void displayWarning(const string &message)
{
    printWarning(message.c_str());
}

// ========== Hàm hiển thị thông tin có định dạng ==========
void displayInfo(const string &message)
{
    printInfo(message.c_str());
}

// ========== Hàm kiểm tra và hiển thị lỗi validation ==========
bool validateAndDisplayError(bool isValid, ErrorType errorType, const string &context)
{
    if (!isValid)
    {
        displayError(errorType, context);
        return false;
    }
    return true;
}
