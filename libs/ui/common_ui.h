#ifndef COMMON_UI_H
#define COMMON_UI_H

#include <iostream>
#include <iomanip>
#include <cstring>
#include <limits>
#include <string>

// Sử dụng tiền khai báo thay vì include trực tiếp để tránh include cycle
struct Student;
struct ArrayStudentList;

// Tiền khai báo các hằng số cần thiết cho UI
enum DataStructureType
{
    ARRAY_LIST = 1,
    SINGLY_LINKED_LIST = 2,
    CIRCULAR_LINKED_LIST = 3,
    DOUBLY_LINKED_LIST = 4,
    BINARY_SEARCH_TREE = 5
};

enum SortAlgorithm
{
    BUBBLE_SORT = 1,
    INSERTION_SORT = 2,
    SELECTION_SORT = 3,
    QUICK_SORT = 4,
    MERGE_SORT = 5
};

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
    cout << "│   " << title << "   │" << endl;
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
void displayStudent(const Student &student);
void displayStudentInTable(const Student &student, int index);
void displayStudentDetailed(const Student &student);

// ========== Các hàm hiển thị menu và giao diện người dùng ==========

// Hàm xóa bộ nhớ đệm (buffer) sau khi nhập dữ liệu
void clearInputBuffer();

// Hàm lấy tên cấu trúc dữ liệu theo mã
const char *getDataStructureName(int dataStructureType);

// Hàm menu chính
void displayMainMenu(int dataStructureType);

// Hàm menu chọn cấu trúc dữ liệu
int selectDataStructure();

// Hàm menu chọn thuật toán sắp xếp
int selectSortAlgorithm(int dataStructureType);

// ========== Cài đặt các hàm UI ==========

// Hàm xóa bộ nhớ đệm (buffer) sau khi nhập dữ liệu
void clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Hàm lấy tên cấu trúc dữ liệu theo mã
const char *getDataStructureName(int dataStructureType)
{
    switch (dataStructureType)
    {
    case ARRAY_LIST:
        return "Danh sách mảng";
    case SINGLY_LINKED_LIST:
        return "Danh sách liên kết đơn";
    case CIRCULAR_LINKED_LIST:
        return "Danh sách liên kết vòng";
    case DOUBLY_LINKED_LIST:
        return "Danh sách liên kết đôi";
    case BINARY_SEARCH_TREE:
        return "Cây tìm kiếm nhị phân";
    default:
        return "Không xác định";
    }
}

// Hàm menu chính
void displayMainMenu(int dataStructureType)
{
    clearScreen();
    printHeader("HỆ THỐNG QUẢN LÝ SINH VIÊN");

    // Hiển thị thông tin cấu trúc dữ liệu đang sử dụng
    cout << BOLD;
    cout << "┌────────────────────────────────────────────────────────────────┐" << endl;
    cout << "│  Cấu trúc dữ liệu hiện tại: " << setw(30) << left << getDataStructureName(dataStructureType) << "│" << endl;
    cout << "└────────────────────────────────────────────────────────────────┘" << RESET << endl;

    cout << endl;

    // Hiển thị menu dưới dạng bảng
    cout << BOLD;
    cout << "┌────────┬───────────────────────────────────────────────────┐" << endl;
    cout << "│  CHỌN  │                     CHỨC NĂNG                     │" << endl;
    cout << "├────────┼───────────────────────────────────────────────────┤" << endl;
    cout << "│   1    │  Chọn cấu trúc dữ liệu                            │" << endl;
    cout << "│   2    │  Nhập dữ liệu từ file CSV                         │" << endl;
    cout << "│   3    │  Thêm sinh viên mới                               │" << endl;
    cout << "│   4    │  Xóa sinh viên theo mã                            │" << endl;
    cout << "│   5    │  Cập nhật sinh viên theo mã                       │" << endl;
    cout << "│   6    │  Hiển thị danh sách sinh viên                     │" << endl;
    cout << "│   7    │  Tìm kiếm sinh viên theo mã                       │" << endl;
    cout << "│   8    │  Thống kê sinh viên (chỉ cho mảng)                │" << endl;
    cout << "│   9    │  Sắp xếp sinh viên theo điểm số                   │" << endl;
    cout << "│   10   │  Bài toán Mã Đi Tuần                              │" << endl;
    cout << "│   0    │  Thoát chương trình                               │" << endl;
    cout << "└────────┴───────────────────────────────────────────────────┘" << RESET << endl;

    cout << "\nNhập lựa chọn: ";
}

// Hàm menu chọn cấu trúc dữ liệu
int selectDataStructure()
{
    int choice;

    clearScreen();
    printHeader("CHỌN CẤU TRÚC DỮ LIỆU");

    // Hiển thị menu dưới dạng bảng
    cout << BOLD;
    cout << "┌────────┬───────────────────────────────────────────┐" << endl;
    cout << "│  CHỌN  │             CẤU TRÚC DỮ LIỆU             │" << endl;
    cout << "├────────┼───────────────────────────────────────────┤" << endl;
    cout << "│   1    │  Danh sách mảng                           │" << endl;
    cout << "│   2    │  Danh sách liên kết đơn                   │" << endl;
    cout << "│   3    │  Danh sách liên kết vòng                  │" << endl;
    cout << "│   4    │  Danh sách liên kết đôi                   │" << endl;
    cout << "│   5    │  Cây tìm kiếm nhị phân (BST)              │" << endl;
    cout << "└────────┴───────────────────────────────────────────┘" << RESET << endl;

    cout << "\nNhập lựa chọn: ";

    while (!(cin >> choice) || choice < 1 || choice > 5)
    {
        printError("Lựa chọn không hợp lệ. Vui lòng nhập lại.");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    clearInputBuffer();
    return choice;
}

// Hàm menu chọn thuật toán sắp xếp
int selectSortAlgorithm(int dataStructureType)
{
    int choice;

    clearScreen();
    printHeader("CHỌN THUẬT TOÁN SẮP XẾP");

    if (dataStructureType == ARRAY_LIST)
    {
        // Hiển thị menu dưới dạng bảng
        cout << BOLD;
        cout << "┌────────┬──────────────────────────────────────┐" << endl;
        cout << "│  CHỌN  │           THUẬT TOÁN SẮP XẾP         │" << endl;
        cout << "├────────┼──────────────────────────────────────┤" << endl;
        cout << "│   1    │  Bubble Sort                         │" << endl;
        cout << "│   2    │  Insertion Sort                      │" << endl;
        cout << "│   3    │  Selection Sort                      │" << endl;
        cout << "│   4    │  Quick Sort                          │" << endl;
        cout << "└────────┴──────────────────────────────────────┘" << RESET << endl;
    }
    else if (dataStructureType == DOUBLY_LINKED_LIST)
    {
        cout << BOLD;
        cout << "┌────────┬──────────────────────────────────────┐" << endl;
        cout << "│  CHỌN  │           THUẬT TOÁN SẮP XẾP         │" << endl;
        cout << "├────────┼──────────────────────────────────────┤" << endl;
        cout << "│   5    │  Merge Sort                          │" << endl;
        cout << "└────────┴──────────────────────────────────────┘" << RESET << endl;
    }
    else
    {
        printWarning("Không có thuật toán sắp xếp được hỗ trợ cho cấu trúc dữ liệu này.");
        return -1;
    }

    cout << "\nNhập lựa chọn: ";

    while (!(cin >> choice) ||
           (dataStructureType == ARRAY_LIST && (choice < 1 || choice > 4)) ||
           (dataStructureType == DOUBLY_LINKED_LIST && choice != 5))
    {
        printError("Lựa chọn không hợp lệ. Vui lòng nhập lại.");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    clearInputBuffer();
    return choice;
}

#endif // COMMON_UI_H