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
    MERGE_SORT = 5,
    HEAP_SORT = 6
};

enum SortCriteria
{
    SORT_BY_STUDENT_ID = 1,
    SORT_BY_NAME = 2,
    SORT_BY_SCORE = 3
};

using namespace std;

// ========== Định nghĩa các mã ANSI escape cho màu sắc ==========
extern const char *RESET;
extern const char *RED;
extern const char *GREEN;
extern const char *YELLOW;
extern const char *BLUE;
extern const char *MAGENTA;
extern const char *CYAN;
extern const char *WHITE;
extern const char *BOLD;
extern const char *UNDERLINE;

// ========== Các hàm hiển thị cơ bản ==========

// Hàm xóa màn hình console
void clearScreen();

// Hàm tạo tiêu đề đẹp
void printHeader(const char *title);

// Hàm tạo đường kẻ đẹp
void printDivider();

// ========== Các hàm thông báo ==========

// Hàm hiển thị thông báo thành công
void printSuccess(const char *message);

// Hàm hiển thị thông báo lỗi
void printError(const char *message);

// Hàm hiển thị thông báo cảnh báo
void printWarning(const char *message);

// Hàm hiển thị thông báo thông tin
void printInfo(const char *message);

// ========== Các hàm hiển thị bảng dữ liệu sinh viên ==========

// Hàm hiển thị tiêu đề bảng sinh viên
void displayStudentTableHeader();

// Hàm hiển thị footer bảng sinh viên
void displayStudentTableFooter();

// Hàm hiển thị dòng phân cách trong bảng sinh viên
void displayStudentTableSeparator();

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

// Hàm menu chọn tiêu chí sắp xếp
int selectSortCriteria();

// Hàm xóa bộ nhớ đệm (buffer) sau khi nhập dữ liệu
void clearInputBuffer();

// Hàm lấy tên cấu trúc dữ liệu theo mã
const char *getDataStructureName(int dataStructureType);

#endif // COMMON_UI_H