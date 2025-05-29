#include "../../include/ui/ui_common.h"
#include "../../include/ui/ui_constants.h"
#include "../../include/utils/student.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cstdlib>
#include <limits>
#include <iomanip> // Thêm thư viện iomanip để sử dụng setw, left, fixed, setprecision

using namespace std;

// Hàm xóa màn hình console
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Hàm hiển thị header với định dạng
void printHeader(const char *header)
{
    int length = strlen(header);
    cout << COLOR_HEADER;
    cout << "╔";
    for (int i = 0; i < length + 2; i++)
        cout << "═";
    cout << "╗" << endl;
    cout << "║ " << header << " ║" << endl;
    cout << "╚";
    for (int i = 0; i < length + 2; i++)
        cout << "═";
    cout << "╝" << COLOR_RESET << endl;
}

// Hàm hiển thị thông báo lỗi
void printError(const char *message)
{
    cout << COLOR_ERROR << "✗ Lỗi: " << message << COLOR_RESET << endl;
}

// Hàm hiển thị thông báo thành công
void printSuccess(const char *message)
{
    cout << COLOR_SUCCESS << "✓ " << message << COLOR_RESET << endl;
}

// Hàm hiển thị thông báo thông tin
void printInfo(const char *message)
{
    cout << COLOR_INFO << "ℹ " << message << COLOR_RESET << endl;
}

// Hàm hiển thị thông báo cảnh báo
void printWarning(const char *message)
{
    cout << COLOR_WARNING << "⚠ " << message << COLOR_RESET << endl;
}

// Hàm hiển thị menu chính
void displayMainMenu(int dataStructureType)
{
    clearScreen();
    printHeader("HỆ THỐNG QUẢN LÝ SINH VIÊN");

    // Hiển thị cấu trúc dữ liệu hiện tại
    cout << COLOR_INFO << "Cấu trúc dữ liệu đang sử dụng: ";
    switch (dataStructureType)
    {
    case 1:
        cout << "Danh sách mảng";
        break;
    case 2:
        cout << "Danh sách liên kết đơn";
        break;
    case 3:
        cout << "Danh sách liên kết vòng";
        break;
    case 4:
        cout << "Danh sách liên kết đôi";
        break;
    case 5:
        cout << "Cây nhị phân tìm kiếm";
        break;
    default:
        cout << "Không xác định";
    }
    cout << COLOR_RESET << endl
         << endl;

    cout << "Chọn chức năng:" << endl;
    cout << "1. Chọn cấu trúc dữ liệu" << endl;
    cout << "2. Nhập dữ liệu từ file CSV" << endl;
    cout << "3. Thêm sinh viên mới" << endl;
    cout << "4. Xóa sinh viên theo mã" << endl;
    cout << "5. Cập nhật thông tin sinh viên" << endl;
    cout << "6. Hiển thị danh sách sinh viên" << endl;
    cout << "7. Tìm kiếm sinh viên theo mã" << endl;
    cout << "8. Thống kê điểm sinh viên" << endl;
    cout << "9. Sắp xếp danh sách sinh viên theo điểm" << endl;
    cout << "10. Giải bài toán mã đi tuần" << endl;
    cout << "0. Thoát" << endl;
    cout << endl;
    cout << "Nhập lựa chọn của bạn: ";
}

// Hàm cho phép người dùng chọn cấu trúc dữ liệu
int selectDataStructure()
{
    int choice;

    clearScreen();
    printHeader("CHỌN CẤU TRÚC DỮ LIỆU");

    cout << "Các cấu trúc dữ liệu có sẵn:" << endl;
    cout << "1. Danh sách mảng" << endl;
    cout << "2. Danh sách liên kết đơn" << endl;
    cout << "3. Danh sách liên kết vòng" << endl;
    cout << "4. Danh sách liên kết đôi" << endl;
    cout << "5. Cây nhị phân tìm kiếm" << endl;
    cout << "0. Quay lại" << endl;
    cout << endl;

    do
    {
        cout << "Nhập lựa chọn của bạn: ";
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            printError("Lựa chọn không hợp lệ!");
            continue;
        }

        if (choice < 0 || choice > 5)
        {
            printError("Lựa chọn không hợp lệ!");
        }
    } while (choice < 0 || choice > 5);

    // Xóa buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return choice;
}

// Hàm hiển thị menu chọn thuật toán sắp xếp
int selectSortAlgorithm(int dataStructureType)
{
    int choice;

    clearScreen();
    printHeader("CHỌN THUẬT TOÁN SẮP XẾP");

    if (dataStructureType == 1)
    { // Mảng
        cout << "Các thuật toán sắp xếp cho danh sách mảng:" << endl;
        cout << "1. Bubble Sort (Sắp xếp nổi bọt)" << endl;
        cout << "2. Selection Sort (Sắp xếp chọn)" << endl;
        cout << "3. Insertion Sort (Sắp xếp chèn)" << endl;
        cout << "4. Quick Sort (Sắp xếp nhanh)" << endl;
        cout << "5. Merge Sort (Sắp xếp trộn)" << endl;
        cout << "0. Quay lại" << endl;
        cout << endl;

        do
        {
            cout << "Nhập lựa chọn của bạn: ";
            if (!(cin >> choice))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                printError("Lựa chọn không hợp lệ!");
                continue;
            }

            if (choice < 0 || choice > 5)
            {
                printError("Lựa chọn không hợp lệ!");
            }
        } while (choice < 0 || choice > 5);
    }
    else if (dataStructureType == 4)
    { // Danh sách liên kết đôi
        cout << "Các thuật toán sắp xếp cho danh sách liên kết đôi:" << endl;
        cout << "1. Merge Sort (Sắp xếp trộn)" << endl;
        cout << "0. Quay lại" << endl;
        cout << endl;

        do
        {
            cout << "Nhập lựa chọn của bạn: ";
            if (!(cin >> choice))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                printError("Lựa chọn không hợp lệ!");
                continue;
            }

            if (choice < 0 || choice > 1)
            {
                printError("Lựa chọn không hợp lệ!");
            }
        } while (choice < 0 || choice > 1);
    }
    else
    {
        printError("Cấu trúc dữ liệu hiện tại không hỗ trợ sắp xếp!");
        return -1;
    }

    // Xóa buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return choice;
}

// Hiển thị header của bảng sinh viên
void displayStudentTableHeader()
{
    cout << "┌─────────────┬─────────────────┬─────────────────┬─────────────┬─────────┐" << endl;
    cout << "│ MSSV        │ Họ              │ Tên             │ Lớp         │ Điểm    │" << endl;
    cout << "├─────────────┼─────────────────┼─────────────────┼─────────────┼─────────┤" << endl;
}

// Hiển thị một dòng sinh viên trong bảng
void displayStudentRow(const struct Student &student)
{
    cout << "│ " << setw(11) << left << student.studentID
         << " │ " << setw(15) << left << student.firstName
         << " │ " << setw(15) << left << student.lastName
         << " │ " << setw(11) << left << student.studentClass
         << " │ " << setw(7) << fixed << setprecision(2) << student.score << " │" << endl;
}

// Hiển thị footer của bảng sinh viên
void displayStudentTableFooter()
{
    cout << "└─────────────┴─────────────────┴─────────────────┴─────────────┴─────────┘" << endl;
}

// Xác nhận hủy bỏ thao tác
bool confirmCancel()
{
    char choice;
    cout << "Bạn có chắc chắn muốn hủy bỏ thao tác này? (Y/N): ";
    cin >> choice;
    return (choice == 'Y' || choice == 'y');
}