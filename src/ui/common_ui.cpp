#include "../../include/ui/common_ui.h"

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
const char *ITALIC = "\033[3m";

// ========== Cài đặt các hàm hiển thị cơ bản ==========

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
    cout << "│   7    │  Thống kê sinh viên                               │" << endl;
    cout << "│   8    │  Sắp xếp sinh viên                                │" << endl;
    cout << "│   9    │  Tìm kiếm sinh viên                               │" << endl;
    cout << "│  10    │  Xóa toàn bộ danh sách sinh viên                  │" << endl;
    cout << "│  11    │  Lưu danh sách ra file CSV                        │" << endl;
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
    cout << "│  CHỌN  │             CẤU TRÚC DỮ LIỆU              │" << endl;
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
        // Đặt lại trạng thái của cin để tránh lỗi khi nhập không phải số
        cin.clear();
        // Xóa bộ đệm nhập để tránh lỗi khi nhập không phải số
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    clearInputBuffer();
    return choice;
}

// Hàm menu chọn tiêu chí sắp xếp
int selectSortCriteria()
{
    int choice;

    clearScreen();
    printHeader("CHỌN TIÊU CHÍ SẮP XẾP");

    // Hiển thị menu dưới dạng bảng
    cout << BOLD;
    cout << "┌────────┬──────────────────────────────────────┐" << endl;
    cout << "│  CHỌN  │              TIÊU CHÍ SẮP XẾP       │" << endl;
    cout << "├────────┼──────────────────────────────────────┤" << endl;
    cout << "│   1    │  Mã sinh viên                        │" << endl;
    cout << "│   2    │  Tên sinh viên                       │" << endl;
    cout << "│   3    │  Điểm số                             │" << endl;
    cout << "└────────┴──────────────────────────────────────┘" << RESET << endl;

    cout << "\nNhập lựa chọn: ";

    while (!(cin >> choice) || choice < 1 || choice > 3)
    {
        printError("Lựa chọn không hợp lệ. Vui lòng nhập lại (1-3).");
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
        // Hiển thị menu dưới dạng bảng cho Array List
        cout << BOLD;
        cout << "┌────────┬──────────────────────────────────────┐" << endl;
        cout << "│  CHỌN  │           THUẬT TOÁN SẮP XẾP         │" << endl;
        cout << "├────────┼──────────────────────────────────────┤" << endl;
        cout << "│   1    │  Bubble Sort                         │" << endl;
        cout << "│   2    │  Insertion Sort                      │" << endl;
        cout << "│   3    │  Selection Sort                      │" << endl;
        cout << "│   4    │  Quick Sort                          │" << endl;
        cout << "│   5    │  Merge Sort                          │" << endl;
        cout << "│   6    │  Heap Sort                           │" << endl;
        cout << "└────────┴──────────────────────────────────────┘" << RESET << endl;

        cout << "\nNhập lựa chọn: ";
        while (!(cin >> choice) || choice < 1 || choice > 6)
        {
            printError("Lựa chọn không hợp lệ. Vui lòng nhập lại (1-6).");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    else if (dataStructureType == SINGLY_LINKED_LIST)
    {
        // Hiển thị menu cho Singly Linked List
        cout << BOLD;
        cout << "┌────────┬──────────────────────────────────────┐" << endl;
        cout << "│  CHỌN  │           THUẬT TOÁN SẮP XẾP         │" << endl;
        cout << "├────────┼──────────────────────────────────────┤" << endl;
        cout << "│   1    │  Bubble Sort                         │" << endl;
        cout << "│   2    │  Insertion Sort                      │" << endl;
        cout << "│   3    │  Selection Sort                      │" << endl;
        cout << "│   5    │  Merge Sort                          │" << endl;
        cout << "└────────┴──────────────────────────────────────┘" << RESET << endl;

        cout << "\nNhập lựa chọn: ";
        while (!(cin >> choice) || (choice != 1 && choice != 2 && choice != 3 && choice != 5))
        {
            printError("Lựa chọn không hợp lệ. Chỉ hỗ trợ: 1(Bubble), 2(Insertion), 3(Selection), 5(Merge).");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    else if (dataStructureType == CIRCULAR_LINKED_LIST)
    {
        // Hiển thị menu cho Circular Linked List
        cout << BOLD;
        cout << "┌────────┬──────────────────────────────────────┐" << endl;
        cout << "│  CHỌN  │           THUẬT TOÁN SẮP XẾP         │" << endl;
        cout << "├────────┼──────────────────────────────────────┤" << endl;
        cout << "│   1    │  Bubble Sort                         │" << endl;
        cout << "│   2    │  Insertion Sort                      │" << endl;
        cout << "│   3    │  Selection Sort                      │" << endl;
        cout << "│   5    │  Merge Sort                          │" << endl;
        cout << "└────────┴──────────────────────────────────────┘" << RESET << endl;

        cout << "\nNhập lựa chọn: ";
        while (!(cin >> choice) || (choice != 1 && choice != 2 && choice != 3 && choice != 5))
        {
            printError("Lựa chọn không hợp lệ. Chỉ hỗ trợ: 1(Bubble), 2(Insertion), 3(Selection), 5(Merge).");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    else if (dataStructureType == DOUBLY_LINKED_LIST)
    {
        // Hiển thị menu cho Doubly Linked List
        cout << BOLD;
        cout << "┌────────┬──────────────────────────────────────┐" << endl;
        cout << "│  CHỌN  │           THUẬT TOÁN SẮP XẾP         │" << endl;
        cout << "├────────┼──────────────────────────────────────┤" << endl;
        cout << "│   1    │  Bubble Sort                         │" << endl;
        cout << "│   2    │  Insertion Sort                      │" << endl;
        cout << "│   3    │  Selection Sort                      │" << endl;
        cout << "│   4    │  Quick Sort                          │" << endl;
        cout << "│   5    │  Merge Sort                          │" << endl;
        cout << "│   6    │  Heap Sort                           │" << endl;
        cout << "└────────┴──────────────────────────────────────┘" << RESET << endl;

        cout << "\nNhập lựa chọn: ";
        while (!(cin >> choice) || choice < 1 || choice > 6)
        {
            printError("Lựa chọn không hợp lệ. Vui lòng nhập lại (1-6).");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    else
    {
        printWarning("Không có thuật toán sắp xếp được hỗ trợ cho cấu trúc dữ liệu này.");
        return -1;
    }

    clearInputBuffer();
    return choice;
}

// Hàm menu chọn tiêu chí tìm kiếm
int selectSearchCriteria()
{
    printHeader("CHỌN TIÊU CHÍ TÌM KIẾM");

    cout << BOLD;
    cout << "┌────────┬──────────────────────────────────────┐" << endl;
    cout << "│  CHỌN  │           TIÊU CHÍ TÌM KIẾM          │" << endl;
    cout << "├────────┼──────────────────────────────────────┤" << endl;
    cout << "│   1    │ Tìm theo Mã sinh viên                │" << endl;
    cout << "│   2    │ Tìm theo Tên                         │" << endl;
    cout << "│   3    │ Tìm theo Họ                          │" << endl;
    cout << "│   4    │ Tìm theo Lớp                         │" << endl;
    cout << "│   5    │ Tìm theo Điểm số                     │" << endl;
    cout << "└────────┴──────────────────────────────────────┘" << endl;
    cout << RESET;

    cout << CYAN << "Lựa chọn của bạn (1-5): " << RESET;

    int choice;
    while (!(cin >> choice) || choice < 1 || choice > 5)
    {
        printError("Lựa chọn không hợp lệ. Vui lòng chọn từ 1-5.");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << CYAN << "Lựa chọn của bạn (1-5): " << RESET;
    }

    clearInputBuffer();
    return choice;
}

// Hàm nhập từ khóa tìm kiếm
bool inputSearchKeyword(char *keyword, int searchCriteria)
{
    cout << "\n";
    printInfo("Nhập từ khóa tìm kiếm:");

    string prompt;
    switch (searchCriteria)
    {
    case SEARCH_BY_STUDENT_ID:
        prompt = "Mã sinh viên (ví dụ: SV001): ";
        break;
    case SEARCH_BY_FIRST_NAME:
        prompt = "Họ (ví dụ: Nguyen): ";
        break;
    case SEARCH_BY_LAST_NAME:
        prompt = "Tên (ví dụ: Van): ";
        break;
    case SEARCH_BY_CLASS:
        prompt = "Lớp (ví dụ: CNTT1): ";
        break;
    case SEARCH_BY_SCORE:
        prompt = "Điểm số (ví dụ: 8.5): ";
        break;
    default:
        prompt = "Từ khóa: ";
    }

    cout << CYAN << prompt << RESET;
    cin.getline(keyword, 100);

    // Kiểm tra từ khóa không rỗng
    if (strlen(keyword) == 0)
    {
        printError("Từ khóa không được để trống!");
        return false;
    }

    // Validate score input if searching by score
    if (searchCriteria == SEARCH_BY_SCORE)
    {
        char *endptr;
        float score = strtof(keyword, &endptr);
        if (*endptr != '\0' || score < 0 || score > 10)
        {
            printError("Điểm số không hợp lệ! Vui lòng nhập điểm từ 0 đến 10.");
            return false;
        }
    }

    return true;
}
