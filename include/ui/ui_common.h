#ifndef UI_COMMON_H
#define UI_COMMON_H

#include <string>

// Hàm xóa màn hình console
void clearScreen();

// Hàm hiển thị header với định dạng
void printHeader(const char *header);

// Hàm hiển thị thông báo lỗi
void printError(const char *message);

// Hàm hiển thị thông báo thành công
void printSuccess(const char *message);

// Hàm hiển thị thông báo thông tin
void printInfo(const char *message);

// Hàm hiển thị thông báo cảnh báo
void printWarning(const char *message);

// Hàm hiển thị menu chính
void displayMainMenu(int dataStructureType);

// Hàm cho phép người dùng chọn cấu trúc dữ liệu
int selectDataStructure();

// Hàm hiển thị menu chọn thuật toán sắp xếp
int selectSortAlgorithm(int dataStructureType);

// Hàm xác nhận hủy bỏ thao tác
bool confirmCancel();

// Hàm hiển thị thông tin sinh viên theo định dạng bảng
void displayStudentTableHeader();

// Hiển thị thông tin một sinh viên dạng bảng
void displayStudentRow(const struct Student &student);

// Hiển thị chân bảng sinh viên
void displayStudentTableFooter();

#endif // UI_COMMON_H
