#ifndef UI_LIBRARY_H
#define UI_LIBRARY_H

#include <iostream>
#include <iomanip>
#include <cstring>

// Sử dụng tiền khai báo thay vì include trực tiếp để tránh include cycle
struct Student;

using namespace std;

// ========== Định nghĩa các mã ANSI escape cho màu sắc ==========
const char *RESET = "\033[0m";
const char *RED = "\033[31m";
const char *GREEN = "\033[32m";
const char *YELLOW = "\033[33m";
const char *BLUE = "\033[34m";
const char *MAGENTA = "\033[35m";
const char *CYAN = "\033[36m";
const char *WHITE = "\033[37m";
const char *BOLD = "\033[1m";
const char *UNDERLINE = "\033[4m";

// ========== Các hàm hiển thị cơ bản ==========

// Hàm xóa màn hình console
void clearScreen()
{
    cout << "\033[2J\033[1;1H"; // ANSI escape code để xóa màn hình và di chuyển con trỏ về đầu
}

// Hàm tạo tiêu đề đẹp
void printHeader(const char *title)
{
    int length = strlen(title);
    cout << BOLD << CYAN;
    cout << "┌";
    for (int i = 0; i < length + 4; i++)
    {
        cout << "─";
    }
    cout << "┐" << endl;
    cout << "│  " << title << "  │" << endl;
    cout << "└";
    for (int i = 0; i < length + 4; i++)
    {
        cout << "─";
    }
    cout << "┘" << RESET << endl;
}

// Hàm tạo đường kẻ đẹp
void printDivider()
{
    cout << YELLOW << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << RESET << endl;
}

// ========== Các hàm thông báo ==========

// Hàm hiển thị thông báo thành công
void printSuccess(const char *message)
{
    cout << GREEN << "✓ " << message << RESET << endl;
}

// Hàm hiển thị thông báo lỗi
void printError(const char *message)
{
    cout << RED << "✗ " << message << RESET << endl;
}

// Hàm hiển thị thông báo cảnh báo
void printWarning(const char *message)
{
    cout << YELLOW << "! " << message << RESET << endl;
}

// Hàm hiển thị thông báo thông tin
void printInfo(const char *message)
{
    cout << BLUE << "ℹ " << message << RESET << endl;
}

// ========== Các hàm hiển thị bảng dữ liệu sinh viên ==========

// Hàm hiển thị tiêu đề bảng sinh viên
void displayStudentTableHeader()
{
    cout << BOLD;
    cout << "┌────────┬────────────────┬─────────────────────┬─────────────────────┬────────────────────┬───────────┐" << endl;
    cout << "│   STT  │  MÃ SINH VIÊN  │        HỌ           │         TÊN         │        LỚP         │   ĐIỂM    │" << endl;
    cout << "├────────┼────────────────┼─────────────────────┼─────────────────────┼────────────────────┼───────────┤" << RESET << endl;
}

// Hàm hiển thị footer bảng sinh viên
void displayStudentTableFooter()
{
    cout << BOLD << "└────────┴────────────────┴─────────────────────┴─────────────────────┴────────────────────┴───────────┘" << RESET << endl;
}

// Hàm hiển thị dòng phân cách trong bảng sinh viên
void displayStudentTableSeparator()
{
    cout << BOLD << "├────────┼────────────────┼─────────────────────┼─────────────────────┼────────────────────┼───────────┤" << RESET << endl;
}

// Khai báo tiền định nghĩa các hàm hiển thị sinh viên (được định nghĩa trong student_struct.h)
void displayStudentInTable(const Student &student, int index);
void displayStudentDetailed(const Student &student);

#endif // UI_LIBRARY_H