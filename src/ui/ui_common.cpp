#include "../../include/ui/ui_common.h"
#include "../../include/ui/ui_constants.h"
#include "../../include/utils/student.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cstdlib>
#include <limits>
#include <thread>
#include <chrono>

using namespace std;

// ========== Hàm xóa màn hình và điều hướng cơ bản ==========

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen()
{
    cout << COLOR_INFO << "\nNhấn Enter để tiếp tục..." << COLOR_RESET;
    cin.get();
}

void showWelcomeBanner()
{
    clearScreen();
    cout << COLOR_HEADER << BOLD;
    printLine("═", CONSOLE_WIDTH);
    centerText("🎓 HỆ THỐNG QUẢN LÝ SINH VIÊN PTIT 🎓");
    centerText("Data Structures & Algorithms Final Project");
    printLine("═", CONSOLE_WIDTH);
    cout << COLOR_RESET << endl;
}

// ========== Hàm hiển thị header và footer cải tiến ==========

void printHeader(const char *header)
{
    cout << COLOR_HEADER << BOLD;
    printLine("═", CONSOLE_WIDTH);
    centerText(header);
    printLine("═", CONSOLE_WIDTH);
    cout << COLOR_RESET << endl;
}

void printSubHeader(const char *subheader)
{
    cout << COLOR_INFO;
    printLine('-', CONSOLE_WIDTH);
    centerText(subheader);
    printLine('-', CONSOLE_WIDTH);
    cout << COLOR_RESET << endl;
}

void printSeparator()
{
    cout << COLOR_TABLE_HEADER;
    printLine('-', CONSOLE_WIDTH);
    cout << COLOR_RESET;
}

void printFooter()
{
    cout << COLOR_HEADER;
    printLine('-', CONSOLE_WIDTH);
    cout << COLOR_RESET << endl;
}

void printApplicationHeader()
{
    cout << COLOR_HEADER << BOLD;
    cout << "╔════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                                    🎓 HỆ THỐNG QUẢN LÝ SINH VIÊN PTIT 🎓                                            ║" << endl;
    cout << "║                                   Data Structures & Algorithms Project                                             ║" << endl;
    cout << "║                                          " << COLOR_ACCENT << "Phiên bản 2.0 - Giao diện nâng cao" << COLOR_HEADER << "                                         ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << COLOR_RESET << endl;
    
    // Thêm thanh trạng thái đẹp
    cout << COLOR_BORDER;
    cout << "┌" << string(CONSOLE_WIDTH - 2, '-') << "┐" << endl;
    cout << "│" << COLOR_MUTED << " Khởi tạo hệ thống... " << COLOR_SUCCESS << ICON_CHECK << " Sẵn sàng" << COLOR_BORDER;
    cout << string(CONSOLE_WIDTH - 30, ' ') << "│" << endl;
    cout << "└" << string(CONSOLE_WIDTH - 2, '-') << "┘" << COLOR_RESET << endl;
}

// ========== Hàm hiển thị thông báo cải tiến ==========

void printError(const char *message)
{
    cout << COLOR_ERROR << BOLD << "┌─ " << ICON_ERROR << " LỖI ────────────────────────────────────────┐" << COLOR_RESET << endl;
    cout << COLOR_ERROR << "│ ";
    printPaddedText(message, 45, true);
    cout << "│" << COLOR_RESET << endl;
    cout << COLOR_ERROR << BOLD << "└──────────────────────────────────────────────────┘" << COLOR_RESET << endl;
}

void printSuccess(const char *message)
{
    cout << COLOR_SUCCESS << BOLD << "┌─ " << ICON_SUCCESS << " THÀNH CÔNG ─────────────────────────────────┐" << COLOR_RESET << endl;
    cout << COLOR_SUCCESS << "│ ";
    printPaddedText(message, 45, true);
    cout << "│" << COLOR_RESET << endl;
    cout << COLOR_SUCCESS << BOLD << "└──────────────────────────────────────────────────┘" << COLOR_RESET << endl;
}

void printInfo(const char *message)
{
    cout << COLOR_INFO << BOLD << "┌─ " << ICON_INFO << " THÔNG TIN ──────────────────────────────────┐" << COLOR_RESET << endl;
    cout << COLOR_INFO << "│ ";
    printPaddedText(message, 45, true);
    cout << "│" << COLOR_RESET << endl;
    cout << COLOR_INFO << BOLD << "└──────────────────────────────────────────────────┘" << COLOR_RESET << endl;
}

void printWarning(const char *message)
{
    cout << COLOR_WARNING << BOLD << "┌─ " << ICON_WARNING << " CẢNH BÁO ───────────────────────────────────┐" << COLOR_RESET << endl;
    cout << COLOR_WARNING << "│ ";
    printPaddedText(message, 45, true);
    cout << "│" << COLOR_RESET << endl;
    cout << COLOR_WARNING << BOLD << "└──────────────────────────────────────────────────┘" << COLOR_RESET << endl;
}

void printNotification(const char *message, const char *type)
{
    if (strcmp(type, "error") == 0) {
        printError(message);
    } else if (strcmp(type, "success") == 0) {
        printSuccess(message);
    } else if (strcmp(type, "warning") == 0) {
        printWarning(message);
    } else {
        printInfo(message);
    }
}

// ========== Hàm hiển thị status và loading ==========

void printStatusBar(int dataStructureType, int studentCount)
{
    cout << COLOR_STATUS;
    cout << "┌─ " << ICON_STATS << " TRẠNG THÁI HỆ THỐNG " << string(CONSOLE_WIDTH - 25, '-') << "┐" << endl;
    cout << "│ ";
    
    // Icon cho cấu trúc dữ liệu
    cout << COLOR_INFO << ICON_GEAR << " ";
    
    switch (dataStructureType)
    {
    case 1: cout << COLOR_ACCENT << "Danh sách mảng"; break;
    case 2: cout << COLOR_ACCENT << "Danh sách liên kết đơn"; break;
    case 3: cout << COLOR_ACCENT << "Danh sách liên kết vòng"; break;
    case 4: cout << COLOR_ACCENT << "Danh sách liên kết đôi"; break;
    case 5: cout << COLOR_ACCENT << "Cây nhị phân tìm kiếm"; break;
    default: cout << COLOR_WARNING << "Chưa chọn"; break;
    }
    
    cout << COLOR_STATUS << " │ " << COLOR_INFO << ICON_STUDENT << " ";
    cout << COLOR_ACCENT << "Sinh viên: " << setw(3) << studentCount;
    
    // Thêm trạng thái bộ nhớ và thời gian
    cout << COLOR_STATUS << " │ " << COLOR_INFO << ICON_CLOCK << COLOR_MUTED << " ";
    
    // Lấy thời gian hiện tại
    auto now = chrono::system_clock::now();
    auto time_t = chrono::system_clock::to_time_t(now);
    cout << put_time(localtime(&time_t), "%H:%M:%S");
    
    cout << COLOR_STATUS << " │" << endl;
    cout << "└" << string(CONSOLE_WIDTH - 2, '-') << "┘" << COLOR_RESET << endl;
}

void printLoadingAnimation(const char *message, int duration)
{
    const char* spinners[] = {"|", "/", "-", "\\"};
    int spinnerCount = 4;
    
    cout << COLOR_LOADING << message << " ";
    for (int i = 0; i < duration * 10; i++) {
        cout << "\r" << message << " " << spinners[i % spinnerCount] << flush;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << "\r" << message << " " << ICON_SUCCESS << COLOR_RESET << endl;
}

void printProgress(int current, int total, const char *label)
{
    const int barWidth = 50;
    float progress = (float)current / total;
    int pos = barWidth * progress;

    cout << COLOR_LOADING << label << " [";
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) cout << "█";
        else if (i == pos) cout << ">";
        else cout << " ";
    }
    cout << "] " << int(progress * 100.0) << "%" << COLOR_RESET << "\r";
    cout.flush();
}

// ========== Hàm menu cải tiến ==========

void displayMainMenu(int dataStructureType)
{
    clearScreen();
    printApplicationHeader();
    cout << endl;
    
    // Hiển thị status bar
    printStatusBar(dataStructureType, 0); // TODO: Pass actual student count
    cout << endl;

    cout << COLOR_MENU_ITEM;
    cout << "┌─ " << ICON_MENU << " MENU CHÍNH " << string(CONSOLE_WIDTH - 15, '-') << "┐" << endl;
    cout << "│" << string(CONSOLE_WIDTH - 2, ' ') << "│" << endl;
    
    // Phần quản lý dữ liệu
    cout << "│  " << COLOR_INFO << ICON_FOLDER << " QUẢN LÝ DỮ LIỆU:" << COLOR_MENU_ITEM << string(85, ' ') << "│" << endl;
    cout << "│    " << COLOR_HIGHLIGHT << "1." << COLOR_MENU_ITEM << " " << ICON_SETTINGS << " Chọn cấu trúc dữ liệu" << string(75, ' ') << "│" << endl;
    cout << "│    " << COLOR_HIGHLIGHT << "2." << COLOR_MENU_ITEM << " " << ICON_FILE << " Nhập dữ liệu từ file CSV" << string(72, ' ') << "│" << endl;
    cout << "│" << string(CONSOLE_WIDTH - 2, ' ') << "│" << endl;
    
    // Phần quản lý sinh viên
    cout << "│  " << COLOR_INFO << ICON_STUDENT << " QUẢN LÝ SINH VIÊN:" << COLOR_MENU_ITEM << string(81, ' ') << "│" << endl;
    cout << "│    " << COLOR_HIGHLIGHT << "3." << COLOR_MENU_ITEM << " " << ICON_ADD << " Thêm sinh viên mới" << string(79, ' ') << "│" << endl;
    cout << "│    " << COLOR_HIGHLIGHT << "4." << COLOR_MENU_ITEM << " " << ICON_DELETE << " Xóa sinh viên theo mã" << string(75, ' ') << "│" << endl;
    cout << "│    " << COLOR_HIGHLIGHT << "5." << COLOR_MENU_ITEM << " " << ICON_EDIT << " Cập nhật thông tin sinh viên" << string(70, ' ') << "│" << endl;
    cout << "│    " << COLOR_HIGHLIGHT << "6." << COLOR_MENU_ITEM << " " << ICON_BOOK << " Hiển thị danh sách sinh viên" << string(70, ' ') << "│" << endl;
    cout << "│" << string(CONSOLE_WIDTH - 2, ' ') << "│" << endl;
    
    // Phần tìm kiếm và thống kê
    cout << "│  " << COLOR_INFO << ICON_SEARCH << " TÌM KIẾM VÀ THỐNG KÊ:" << COLOR_MENU_ITEM << string(77, ' ') << "│" << endl;
    cout << "│    " << COLOR_HIGHLIGHT << "7." << COLOR_MENU_ITEM << " " << ICON_SEARCH << " Tìm kiếm sinh viên theo mã" << string(72, ' ') << "│" << endl;
    cout << "│    " << COLOR_HIGHLIGHT << "8." << COLOR_MENU_ITEM << " " << ICON_GRAPH << " Thống kê điểm sinh viên" << string(75, ' ') << "│" << endl;
    cout << "│    " << COLOR_HIGHLIGHT << "9." << COLOR_MENU_ITEM << " " << ICON_SORT << " Sắp xếp danh sách sinh viên theo điểm" << string(62, ' ') << "│" << endl;
    cout << "│" << string(CONSOLE_WIDTH - 2, ' ') << "│" << endl;
    
    // Phần tính năng khác
    cout << "│  " << COLOR_INFO << ICON_STAR << " TÍNH NĂNG KHÁC:" << COLOR_MENU_ITEM << string(83, ' ') << "│" << endl;
    cout << "│   " << COLOR_HIGHLIGHT << "10." << COLOR_MENU_ITEM << " " << ICON_TARGET << " Giải bài toán mã đi tuần" << string(74, ' ') << "│" << endl;
    cout << "│" << string(CONSOLE_WIDTH - 2, ' ') << "│" << endl;
    
    // Phần thoát
    cout << "│    " << COLOR_WARNING << "0." << COLOR_MENU_ITEM << " " << ICON_EXIT << " Thoát chương trình" << string(80, ' ') << "│" << endl;
    cout << "│" << string(CONSOLE_WIDTH - 2, ' ') << "│" << endl;
    cout << "└" << string(CONSOLE_WIDTH - 2, '-') << "┘" << COLOR_RESET << endl;
    
    // Thêm hướng dẫn navigation
    cout << endl;
    cout << COLOR_MUTED << "💡 " << COLOR_SECONDARY << "Hướng dẫn: Nhập số tương ứng với lựa chọn của bạn" << COLOR_RESET << endl;
    cout << COLOR_INPUT_PROMPT << "\n" << ICON_ARROW_RIGHT << " Nhập lựa chọn của bạn: " << COLOR_RESET;
}

// ========== Phần còn lại của file sẽ được tiếp tục... ==========

void displayEnhancedMenu(const char *title, const char *options[], int optionCount, int currentSelection)
{
    cout << COLOR_MENU_ITEM;
    cout << "┌─ " << title << string(safeCalculatePadding(title, MENU_WIDTH, 3), '-') << "┐" << endl;
    
    for (int i = 0; i < optionCount; i++) {
        if (i == currentSelection) {
            cout << "│" << COLOR_MENU_SELECTED << " ▶ " << options[i];
            cout << string(safeCalculatePadding(options[i], MENU_WIDTH, 6), ' ') << COLOR_MENU_ITEM << "│" << endl;
        } else {
            cout << "│   " << options[i];
            cout << string(safeCalculatePadding(options[i], MENU_WIDTH, 6), ' ') << "│" << endl;
        }
    }
    
    cout << "└" << string(MENU_WIDTH - 2, '-') << "┘" << COLOR_RESET << endl;
}

int selectDataStructure()
{
    int choice;
    clearScreen();
    printHeader("CHỌN CẤU TRÚC DỮ LIỆU");

    cout << COLOR_MENU_ITEM;
    cout << "┌─ CÁC CẤU TRÚC DỮ LIỆU CÓ SẴN ──────────────────────────────────────────────────────────────────────────────────┐" << endl;
    cout << "│                                                                                                                 │" << endl;
    cout << "│  1. " << ICON_BULLET << " 📋 Danh sách mảng (Array List)                                                               │" << endl;
    cout << "│     " << COLOR_STATUS << "• Truy cập nhanh theo chỉ số • Hỗ trợ đầy đủ các thuật toán sắp xếp" << COLOR_MENU_ITEM << "                        │" << endl;
    cout << "│                                                                                                                 │" << endl;
    cout << "│  2. " << ICON_BULLET << " 🔗 Danh sách liên kết đơn (Singly Linked List)                                              │" << endl;
    cout << "│     " << COLOR_STATUS << "• Thêm/xóa linh hoạt • Tiết kiệm bộ nhớ" << COLOR_MENU_ITEM << "                                                    │" << endl;
    cout << "│                                                                                                                 │" << endl;
    cout << "│  3. " << ICON_BULLET << " 🔄 Danh sách liên kết vòng (Circular Linked List)                                           │" << endl;
    cout << "│     " << COLOR_STATUS << "• Duyệt vòng lặp • Thích hợp cho ứng dụng tuần hoàn" << COLOR_MENU_ITEM << "                               │" << endl;
    cout << "│                                                                                                                 │" << endl;
    cout << "│  4. " << ICON_BULLET << " ⬌ Danh sách liên kết đôi (Doubly Linked List)                                              │" << endl;
    cout << "│     " << COLOR_STATUS << "• Duyệt hai chiều • Hỗ trợ merge sort" << COLOR_MENU_ITEM << "                                                 │" << endl;
    cout << "│                                                                                                                 │" << endl;
    cout << "│  5. " << ICON_BULLET << " 🌳 Cây nhị phân tìm kiếm (Binary Search Tree)                                               │" << endl;
    cout << "│     " << COLOR_STATUS << "• Tìm kiếm nhanh • Duyệt có thứ tự" << COLOR_MENU_ITEM << "                                                     │" << endl;
    cout << "│                                                                                                                 │" << endl;
    cout << "│  0. " << ICON_ARROW_LEFT << " Quay lại menu chính                                                                        │" << endl;
    cout << "│                                                                                                                 │" << endl;
    cout << "└─────────────────────────────────────────────────────────────────────────────────────────────────────────────┘" << COLOR_RESET << endl;

    do
    {
        cout << COLOR_INPUT_PROMPT << "\nNhập lựa chọn của bạn " << ICON_ARROW_RIGHT << " " << COLOR_RESET;
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

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

int selectSortAlgorithm(int dataStructureType)
{
    int choice;
    clearScreen();
    printHeader("CHỌN THUẬT TOÁN SẮP XẾP");

    if (dataStructureType == 1)
    { // Mảng
        cout << COLOR_MENU_ITEM;
        cout << "┌─ THUẬT TOÁN SẮP XẾP CHO DANH SÁCH MẢNG ────────────────────────────────────────────────────────────────────┐" << endl;
        cout << "│                                                                                                             │" << endl;
        cout << "│  1. " << ICON_BULLET << " 🫧 Bubble Sort (Sắp xếp nổi bọt)                                                         │" << endl;
        cout << "│     " << COLOR_STATUS << "• Độ phức tạp: O(n²) • Đơn giản, dễ hiểu" << COLOR_MENU_ITEM << "                                                │" << endl;
        cout << "│                                                                                                             │" << endl;
        cout << "│  2. " << ICON_BULLET << " 🎯 Selection Sort (Sắp xếp chọn)                                                         │" << endl;
        cout << "│     " << COLOR_STATUS << "• Độ phức tạp: O(n²) • Ít phép hoán đổi" << COLOR_MENU_ITEM << "                                               │" << endl;
        cout << "│                                                                                                             │" << endl;
        cout << "│  3. " << ICON_BULLET << " 📥 Insertion Sort (Sắp xếp chèn)                                                         │" << endl;
        cout << "│     " << COLOR_STATUS << "• Độ phức tạp: O(n²) • Hiệu quả với dữ liệu nhỏ" << COLOR_MENU_ITEM << "                                      │" << endl;
        cout << "│                                                                                                             │" << endl;
        cout << "│  4. " << ICON_BULLET << " ⚡ Quick Sort (Sắp xếp nhanh)                                                            │" << endl;
        cout << "│     " << COLOR_STATUS << "• Độ phức tạp: O(n log n) • Hiệu quả cao" << COLOR_MENU_ITEM << "                                            │" << endl;
        cout << "│                                                                                                             │" << endl;
        cout << "│  5. " << ICON_BULLET << " 🔀 Merge Sort (Sắp xếp trộn)                                                            │" << endl;
        cout << "│     " << COLOR_STATUS << "• Độ phức tạp: O(n log n) • Ổn định" << COLOR_MENU_ITEM << "                                                 │" << endl;
        cout << "│                                                                                                             │" << endl;
        cout << "│  0. " << ICON_ARROW_LEFT << " Quay lại menu chính                                                                    │" << endl;
        cout << "│                                                                                                             │" << endl;
        cout << "└─────────────────────────────────────────────────────────────────────────────────────────────────────────┘" << COLOR_RESET << endl;

        do
        {
            cout << COLOR_INPUT_PROMPT << "\nNhập lựa chọn của bạn " << ICON_ARROW_RIGHT << " " << COLOR_RESET;
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
        cout << COLOR_MENU_ITEM;
        cout << "┌─ THUẬT TOÁN SẮP XẾP CHO DANH SÁCH LIÊN KẾT ĐÔI ───────────────────────────────────────────────────────────┐" << endl;
        cout << "│                                                                                                             │" << endl;
        cout << "│  1. " << ICON_BULLET << " 🔀 Merge Sort (Sắp xếp trộn)                                                            │" << endl;
        cout << "│     " << COLOR_STATUS << "• Độ phức tạp: O(n log n) • Phù hợp với danh sách liên kết" << COLOR_MENU_ITEM << "                          │" << endl;
        cout << "│                                                                                                             │" << endl;
        cout << "│  0. " << ICON_ARROW_LEFT << " Quay lại menu chính                                                                    │" << endl;
        cout << "│                                                                                                             │" << endl;
        cout << "└─────────────────────────────────────────────────────────────────────────────────────────────────────────┘" << COLOR_RESET << endl;

        do
        {
            cout << COLOR_INPUT_PROMPT << "\nNhập lựa chọn của bạn " << ICON_ARROW_RIGHT << " " << COLOR_RESET;
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

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

// ========== Hàm input cải tiến ==========

void printInputBox(const char *prompt, const char *hint)
{
    cout << COLOR_INPUT_PROMPT;
    cout << "┌─ NHẬP DỮ LIỆU " << string(INPUT_BOX_WIDTH - 15, '-') << "┐" << endl;
    
    // Sử dụng safeCalculatePadding cho prompt
    cout << "│ " << prompt;
    int promptPadding = safeCalculatePadding(prompt, INPUT_BOX_WIDTH, 3);
    cout << string(promptPadding, ' ') << "│" << endl;
    
    if (hint) {
        cout << "│ " << COLOR_STATUS << hint;
        int hintPadding = safeCalculatePadding(hint, INPUT_BOX_WIDTH, 3);
        cout << string(hintPadding, ' ') << COLOR_INPUT_PROMPT << "│" << endl;
    }
    cout << "└" << string(INPUT_BOX_WIDTH, '-') << "┘" << COLOR_RESET << endl;
    cout << COLOR_INPUT_PROMPT << ICON_ARROW_RIGHT << " " << COLOR_RESET;
}

void printInputPrompt(const char *prompt)
{
    cout << COLOR_INPUT_PROMPT << prompt << " " << ICON_ARROW_RIGHT << " " << COLOR_RESET;
}

bool confirmCancel()
{
    char choice;
    cout << COLOR_WARNING;
    cout << "┌─ XÁC NHẬN ──────────────────────────────────┐" << endl;
    cout << "│ Bạn có chắc chắn muốn hủy bỏ thao tác này?  │" << endl;
    cout << "│ (Y/N): " << string(33, ' ') << "│" << endl;
    cout << "└─────────────────────────────────────────────┘" << COLOR_RESET << endl;
    cout << COLOR_INPUT_PROMPT << ICON_ARROW_RIGHT << " " << COLOR_RESET;
    cin >> choice;
    return (choice == 'Y' || choice == 'y');
}

bool confirmAction(const char *action)
{
    char choice;
    cout << COLOR_WARNING;
    cout << "┌─ XÁC NHẬN ──────────────────────────────────┐" << endl;
    cout << "│ Bạn có chắc chắn muốn " << setw(20) << left << action << "?│" << endl;
    cout << "│ (Y/N): " << string(33, ' ') << "│" << endl;
    cout << "└─────────────────────────────────────────────┘" << COLOR_RESET << endl;
    cout << COLOR_INPUT_PROMPT << ICON_ARROW_RIGHT << " " << COLOR_RESET;
    cin >> choice;
    return (choice == 'Y' || choice == 'y');
}

// ========== Hàm hiển thị bảng cải tiến ==========

void displayStudentTableHeader()
{
    cout << COLOR_TABLE_HEADER << BOLD;
    cout << "┌─────┬─────────────┬─────────────────┬─────────────────┬─────────────┬─────────┐" << endl;
    cout << "│ STT │    MSSV     │       HỌ        │       TÊN       │     LỚP     │  ĐIỂM   │" << endl;
    cout << "├─────┼─────────────┼─────────────────┼─────────────────┼─────────────┼─────────┤" << COLOR_RESET << endl;
}

void displayStudentRow(const struct Student &student, int rowNumber)
{
    const char* rowColor = (rowNumber >= 0 && rowNumber % 2 == 0) ? COLOR_TABLE_ROW_EVEN : COLOR_TABLE_ROW_ODD;
    
    cout << rowColor;
    
    // Cột STT - 5 ký tự (bao gồm spaces)
    cout << "│ ";
    if (rowNumber >= 0) {
        cout << setw(3) << right << rowNumber + 1;
    } else {
        cout << "   ";
    }
    cout << " ";
    
    // Cột MSSV - 11 ký tự
    cout << "│ ";
    printPaddedText(student.studentID, 11, true);
    
    // Cột HỌ - 15 ký tự (tính đúng với ký tự có dấu)
    cout << "│ ";
    printPaddedText(student.firstName, 15, true);
    
    // Cột TÊN - 15 ký tự (tính đúng với ký tự có dấu)
    cout << "│ ";
    printPaddedText(student.lastName, 15, true);
    
    // Cột LỚP - 11 ký tự
    cout << "│ ";
    printPaddedText(student.studentClass, 11, true);
    
    // Cột ĐIỂM - 7 ký tự
    cout << "│ " << setw(7) << fixed << setprecision(2) << student.score << " │" << COLOR_RESET << endl;
}

void displayStudentTableFooter()
{
    cout << COLOR_TABLE_HEADER << BOLD;
    cout << "└─────┴─────────────┴─────────────────┴─────────────────┴─────────────┴─────────┘" << COLOR_RESET << endl;
}

void displayEnhancedStudentTable(const struct Student students[], int count)
{
    if (count == 0) {
        displayEmptyMessage("Danh sách sinh viên trống");
        return;
    }

    cout << COLOR_INFO;
    string countText = "┌─ DANH SÁCH SINH VIÊN (" + to_string(count) + " sinh viên) ";
    int headerPadding = safeCalculatePadding(countText.c_str(), 100, 1);
    cout << countText << string(headerPadding, '-') << "┐" << endl;
    cout << "└" << string(100, '-') << "┘" << COLOR_RESET << endl;

    displayStudentTableHeader();
    for (int i = 0; i < count; i++) {
        displayStudentRow(students[i], i);
    }
    displayStudentTableFooter();
}

// ========== Hàm hiển thị thống kê cải tiến ==========

void displayStatsDashboard(float minScore, float maxScore, float avgScore, int totalStudents)
{
    cout << COLOR_STATS;
    cout << "┌─ " << ICON_STATS << " THỐNG KÊ ĐIỂM SỐ ──────────────────────────────────────────────────────────────────────────────┐" << endl;
    cout << "│                                                                                                             │" << endl;
    cout << "│   📊 Tổng số sinh viên: " << setw(3) << totalStudents << string(65, ' ') << "│" << endl;
    cout << "│   📉 Điểm thấp nhất:    " << setw(6) << fixed << setprecision(2) << minScore << string(62, ' ') << "│" << endl;
    cout << "│   📈 Điểm cao nhất:     " << setw(6) << fixed << setprecision(2) << maxScore << string(62, ' ') << "│" << endl;
    cout << "│   📊 Điểm trung bình:   " << setw(6) << fixed << setprecision(2) << avgScore << string(62, ' ') << "│" << endl;
    cout << "│                                                                                                             │" << endl;
    cout << "└─────────────────────────────────────────────────────────────────────────────────────────────────────────┘" << COLOR_RESET << endl;
}

void displaySearchResults(const struct Student &student)
{
    cout << COLOR_SUCCESS;
    cout << "┌─ " << ICON_SEARCH << " KẾT QUẢ TÌM KIẾM ──────────────────────────────────────────────────────────────────────────────┐" << endl;
    cout << "└─────────────────────────────────────────────────────────────────────────────────────────────────────────┘" << COLOR_RESET << endl;
    
    displayStudentTableHeader();
    displayStudentRow(student, -1);
    displayStudentTableFooter();
}

void displayEmptyMessage(const char *message)
{
    cout << COLOR_WARNING;
    cout << "┌─ THÔNG BÁO ─────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
    cout << "│                                                                                                         │" << endl;
    centerText(message);
    cout << "│                                                                                                         │" << endl;
    cout << "└─────────────────────────────────────────────────────────────────────────────────────────────────────┘" << COLOR_RESET << endl;
}

// ========== Hàm tiện ích hiển thị ==========

void centerText(const char *text, int width)
{
    if (!text) {
        cout << string(width, ' ') << endl;
        return;
    }
    
    int displayWidth = getDisplayWidth(text);
    int padding = (width - displayWidth) / 2;
    int rightPadding = width - displayWidth - padding;
    
    if (padding < 0) {
        // Text quá dài, cắt ngắn và hiển thị
        string truncated = truncateText(text, width);
        cout << truncated << endl;
        return;
    }
    
    cout << string(padding, ' ') << text << string(rightPadding, ' ') << endl;
}

// Overload với default width
void centerText(const char *text)
{
    centerText(text, CONSOLE_WIDTH);
}

void printLine(char character, int length)
{
    cout << string(length, character) << endl;
}

// Overload cho Unicode strings
void printLine(const char *character, int length)
{
    for (int i = 0; i < length; i++) {
        cout << character;
    }
    cout << endl;
}

void printColoredLine(const char *color, char character, int length)
{
    cout << color << string(length, character) << COLOR_RESET << endl;
}

// ========== UTF-8 và text processing helpers ==========

// Hàm tính độ dài hiển thị thực tế của chuỗi UTF-8
int getDisplayWidth(const char *text)
{
    if (!text) return 0;
    
    int width = 0;
    const unsigned char *utf8 = (const unsigned char *)text;
    
    while (*utf8) {
        // Đếm các ký tự UTF-8
        if ((*utf8 & 0x80) == 0) {
            // ASCII character (1 byte)
            width++;
            utf8++;
        } else if ((*utf8 & 0xE0) == 0xC0) {
            // 2-byte UTF-8 character
            if (*(utf8 + 1) && ((*(utf8 + 1) & 0xC0) == 0x80)) {
                width++;
                utf8 += 2;
            } else {
                // Invalid sequence, treat as single byte
                width++;
                utf8++;
            }
        } else if ((*utf8 & 0xF0) == 0xE0) {
            // 3-byte UTF-8 character (most Vietnamese characters)
            if (*(utf8 + 1) && *(utf8 + 2) && 
                ((*(utf8 + 1) & 0xC0) == 0x80) && 
                ((*(utf8 + 2) & 0xC0) == 0x80)) {
                width++;
                utf8 += 3;
            } else {
                // Invalid sequence, treat as single byte
                width++;
                utf8++;
            }
        } else if ((*utf8 & 0xF8) == 0xF0) {
            // 4-byte UTF-8 character
            if (*(utf8 + 1) && *(utf8 + 2) && *(utf8 + 3) &&
                ((*(utf8 + 1) & 0xC0) == 0x80) && 
                ((*(utf8 + 2) & 0xC0) == 0x80) &&
                ((*(utf8 + 3) & 0xC0) == 0x80)) {
                width++;
                utf8 += 4;
            } else {
                // Invalid sequence, treat as single byte
                width++;
                utf8++;
            }
        } else {
            // Invalid UTF-8, skip
            width++;
            utf8++;
        }
    }
    
    return width;
}

// Hàm in text với padding chính xác cho UTF-8
void printPaddedText(const char *text, int width, bool leftAlign)
{
    if (!text) {
        cout << string(width, ' ');
        return;
    }
    
    int displayWidth = getDisplayWidth(text);
    int padding = width - displayWidth;
    
    if (padding < 0) {
        // Text quá dài, cắt ngắn
        string truncated = truncateText(text, width);
        cout << truncated;
        return;
    }
    
    if (leftAlign) {
        cout << text << string(padding, ' ');
    } else {
        cout << string(padding, ' ') << text;
    }
}

// Hàm cắt ngắn text nếu quá dài
string truncateText(const char *text, int maxWidth)
{
    if (!text || maxWidth <= 0) return "";
    
    int currentWidth = 0;
    const unsigned char *utf8 = (const unsigned char *)text;
    const unsigned char *start = utf8;
    
    while (*utf8 && currentWidth < maxWidth) {
        const unsigned char *charStart = utf8;
        
        if ((*utf8 & 0x80) == 0) {
            // ASCII character
            utf8++;
        } else if ((*utf8 & 0xE0) == 0xC0) {
            // 2-byte UTF-8
            if (*(utf8 + 1) && ((*(utf8 + 1) & 0xC0) == 0x80)) {
                utf8 += 2;
            } else {
                utf8++;
            }
        } else if ((*utf8 & 0xF0) == 0xE0) {
            // 3-byte UTF-8
            if (*(utf8 + 1) && *(utf8 + 2) && 
                ((*(utf8 + 1) & 0xC0) == 0x80) && 
                ((*(utf8 + 2) & 0xC0) == 0x80)) {
                utf8 += 3;
            } else {
                utf8++;
            }
        } else if ((*utf8 & 0xF8) == 0xF0) {
            // 4-byte UTF-8
            if (*(utf8 + 1) && *(utf8 + 2) && *(utf8 + 3) &&
                ((*(utf8 + 1) & 0xC0) == 0x80) && 
                ((*(utf8 + 2) & 0xC0) == 0x80) &&
                ((*(utf8 + 3) & 0xC0) == 0x80)) {
                utf8 += 4;
            } else {
                utf8++;
            }
        } else {
            utf8++;
        }
        
        currentWidth++;
        
        // Nếu thêm ký tự này sẽ vượt quá maxWidth
        if (currentWidth >= maxWidth) {
            if (maxWidth >= 3) {
                // Thêm "..." nếu có đủ chỗ
                string result(reinterpret_cast<const char*>(start), charStart - start);
                result += "...";
                return result;
            }
        }
    }
    
    return string(reinterpret_cast<const char*>(start), utf8 - start);
}

// Hàm helper tính padding an toàn
int safeCalculatePadding(const char *text, int totalWidth, int usedSpace)
{
    if (!text) return totalWidth - usedSpace;
    
    int displayWidth = getDisplayWidth(text);
    int availableWidth = totalWidth - usedSpace;
    int padding = availableWidth - displayWidth;
    
    return (padding > 0) ? padding : 0;
}

// ========== Pagination và Navigation ==========

void displayPaginatedStudentTable(const struct Student students[], int totalCount, int currentPage, int pageSize)
{
    if (totalCount == 0) {
        displayEmptyMessage("Danh sách sinh viên trống");
        return;
    }

    int totalPages = (totalCount + pageSize - 1) / pageSize;
    int startIndex = currentPage * pageSize;
    int endIndex = min(startIndex + pageSize, totalCount);

    cout << COLOR_INFO;
    string pageHeader = "┌─ " + string(ICON_BOOK) + " DANH SÁCH SINH VIÊN (Trang " + to_string(currentPage + 1) + "/" + to_string(totalPages) + ") ";
    int headerPadding = safeCalculatePadding(pageHeader.c_str(), 100, 1);
    cout << pageHeader << string(headerPadding, '-') << "┐" << endl;
    cout << "└" << string(100, '-') << "┘" << COLOR_RESET << endl;

    displayStudentTableHeader();
    for (int i = startIndex; i < endIndex; i++) {
        displayStudentRow(students[i], i);
    }
    displayStudentTableFooter();
    
    displayPageNavigation(currentPage, totalPages, totalCount);
}

void displayPageNavigation(int currentPage, int totalPages, int totalItems)
{
    cout << COLOR_STATUS;
    cout << "┌─ ĐIỀU HƯỚNG " << string(CONSOLE_WIDTH - 15, '-') << "┐" << endl;
    cout << "│ ";
    
    // Previous page indicator
    if (currentPage > 0) {
        cout << COLOR_ACCENT << ICON_ARROW_LEFT << " PgUp: Trang trước";
    } else {
        cout << COLOR_MUTED << "   ─────────────";
    }
    
    cout << COLOR_STATUS << " │ ";
    
    // Page info
    cout << COLOR_INFO << "Trang " << (currentPage + 1) << "/" << totalPages;
    cout << COLOR_STATUS << " │ ";
    
    // Next page indicator
    if (currentPage < totalPages - 1) {
        cout << COLOR_ACCENT << "PgDn: Trang sau " << ICON_ARROW_RIGHT;
    } else {
        cout << COLOR_MUTED << "─────────────   ";
    }
    
    cout << COLOR_STATUS << " │" << endl;
    cout << "│ " << COLOR_MUTED << "Tổng " << totalItems << " sinh viên";
    string totalText = "Tổng " + to_string(totalItems) + " sinh viên";
    int totalPadding = safeCalculatePadding(totalText.c_str(), CONSOLE_WIDTH, 4);
    cout << string(totalPadding, ' ') << COLOR_STATUS << "│" << endl;
    cout << "└" << string(CONSOLE_WIDTH - 2, '-') << "┘" << COLOR_RESET << endl;
}

void printBreadcrumbs(const char* path)
{
    cout << COLOR_SECONDARY;
    cout << "┌─ VỊ TRÍ " << string(CONSOLE_WIDTH - 11, '-') << "┐" << endl;
    cout << "│ " << ICON_HOME << " Trang chủ " << ICON_ARROW_RIGHT << " " << path;
    int pathPadding = safeCalculatePadding(path, CONSOLE_WIDTH, 18);
    cout << string(pathPadding, ' ') << "│" << endl;
    cout << "└" << string(CONSOLE_WIDTH - 2, '-') << "┘" << COLOR_RESET << endl;
}

void displayQuickHelp(const char* context)
{
    cout << COLOR_MUTED;
    cout << "┌─ " << ICON_HELP << " TRỢ GIÚP NHANH " << string(CONSOLE_WIDTH - 18, '-') << "┐" << endl;
    cout << "│ ";
    
    if (strcmp(context, "menu") == 0) {
        cout << "ESC: Thoát • Enter: Xác nhận • 0-9: Chọn chức năng";
        int helpPadding = safeCalculatePadding("ESC: Thoát • Enter: Xác nhận • 0-9: Chọn chức năng", CONSOLE_WIDTH, 4);
        cout << string(helpPadding, ' ') << "│" << endl;
    } else if (strcmp(context, "table") == 0) {
        cout << "PgUp/PgDn: Chuyển trang • Q: Quay lại • S: Tìm kiếm";
        int helpPadding = safeCalculatePadding("PgUp/PgDn: Chuyển trang • Q: Quay lại • S: Tìm kiếm", CONSOLE_WIDTH, 4);
        cout << string(helpPadding, ' ') << "│" << endl;
    } else if (strcmp(context, "input") == 0) {
        cout << "Enter: Xác nhận • ESC: Hủy bỏ • Tab: Chuyển trường";
        int helpPadding = safeCalculatePadding("Enter: Xác nhận • ESC: Hủy bỏ • Tab: Chuyển trường", CONSOLE_WIDTH, 4);
        cout << string(helpPadding, ' ') << "│" << endl;
    } else {
        cout << "F1: Trợ giúp • ESC: Quay lại • Enter: Tiếp tục";
        int helpPadding = safeCalculatePadding("F1: Trợ giúp • ESC: Quay lại • Enter: Tiếp tục", CONSOLE_WIDTH, 4);
        cout << string(helpPadding, ' ') << "│" << endl;
    }
    cout << "└" << string(CONSOLE_WIDTH - 2, '-') << "┘" << COLOR_RESET << endl;
}

// ========== Enhanced Error Handling ==========

void displayDetailedError(const char* operation, const char* error, const char* suggestion)
{
    cout << COLOR_ERROR << BOLD;
    cout << "┌─ " << ICON_ERROR << " LỖI THỰC HIỆN " << string(CONSOLE_WIDTH - 18, '-') << "┐" << endl;
    cout << "│ " << COLOR_ERROR << "Thao tác: " << COLOR_WARNING << operation << COLOR_ERROR;
    int operationPadding = safeCalculatePadding(operation, CONSOLE_WIDTH, 12);
    cout << string(operationPadding, ' ') << "│" << endl;
    cout << "│ " << COLOR_ERROR << "Lỗi:      " << COLOR_WARNING << error << COLOR_ERROR;
    int errorPadding = safeCalculatePadding(error, CONSOLE_WIDTH, 12);
    cout << string(errorPadding, ' ') << "│" << endl;
    
    if (suggestion) {
        cout << "│ " << COLOR_INFO << "Gợi ý:    " << COLOR_ACCENT << suggestion << COLOR_ERROR;
        int suggestionPadding = safeCalculatePadding(suggestion, CONSOLE_WIDTH, 12);
        cout << string(suggestionPadding, ' ') << "│" << endl;
    }
    
    cout << "└" << string(CONSOLE_WIDTH - 2, '-') << "┘" << COLOR_RESET << endl;
}

void displayValidationError(const char* field, const char* expectedFormat)
{
    cout << COLOR_WARNING << BOLD;
    cout << "┌─ " << ICON_WARNING << " LỖI VALIDATION " << string(CONSOLE_WIDTH - 19, '-') << "┐" << endl;
    cout << "│ " << COLOR_WARNING << "Trường:      " << COLOR_ACCENT << field << COLOR_WARNING;
    cout << string(safeCalculatePadding(field, CONSOLE_WIDTH, 15), ' ') << "│" << endl;
    cout << "│ " << COLOR_WARNING << "Định dạng:   " << COLOR_INFO << expectedFormat << COLOR_WARNING;
    cout << string(safeCalculatePadding(expectedFormat, CONSOLE_WIDTH, 15), ' ') << "│" << endl;
    cout << "│ " << COLOR_MUTED << "Vui lòng nhập lại theo đúng định dạng" << COLOR_WARNING;
    cout << string(CONSOLE_WIDTH - 40, ' ') << "│" << endl;
    cout << "└" << string(CONSOLE_WIDTH - 2, '-') << "┘" << COLOR_RESET << endl;
}

void displayProgressMessage(const char* message, bool success)
{
    const char* icon = success ? ICON_SUCCESS : ICON_LOADING;
    const char* color = success ? COLOR_SUCCESS : COLOR_LOADING;
    
    cout << color;
    cout << "┌─ TIẾN TRÌNH " << string(CONSOLE_WIDTH - 15, '-') << "┐" << endl;
    cout << "│ " << icon << " " << message;
    cout << string(safeCalculatePadding(message, CONSOLE_WIDTH, 6), ' ') << "│" << endl;
    cout << "└" << string(CONSOLE_WIDTH - 2, '-') << "┘" << COLOR_RESET << endl;
}

// ========== Interactive Elements ==========

void displayConfirmationDialog(const char* title, const char* message, const char* yesText, const char* noText)
{
    cout << COLOR_WARNING;
    cout << "┌─ " << ICON_WARNING << " " << title << string(safeCalculatePadding(title, CONSOLE_WIDTH, 5), '-') << "┐" << endl;
    cout << "│" << string(CONSOLE_WIDTH - 2, ' ') << "│" << endl;
    
    // Center the message với safe padding
    int messagePadding = safeCalculatePadding(message, CONSOLE_WIDTH, 2) / 2;
    int remainingPadding = safeCalculatePadding(message, CONSOLE_WIDTH, 2) - messagePadding;
    cout << "│" << string(messagePadding, ' ') << message << string(remainingPadding, ' ') << "│" << endl;
    cout << "│" << string(CONSOLE_WIDTH - 2, ' ') << "│" << endl;
    
    // Display options với safe padding
    int totalOptionsLen = strlen(yesText) + strlen(noText) + 10; // 10 for formatting
    int optionsPadding = max(0, (CONSOLE_WIDTH - totalOptionsLen) / 2);
    int optionsRemainingPadding = max(0, CONSOLE_WIDTH - totalOptionsLen - optionsPadding - 2);
    cout << "│" << string(optionsPadding, ' ') << COLOR_ACCENT << "[Y] " << yesText << "   " << COLOR_WARNING << "[N] " << noText;
    cout << string(optionsRemainingPadding, ' ') << "│" << endl;
    cout << "│" << string(CONSOLE_WIDTH - 2, ' ') << "│" << endl;
    cout << "└" << string(CONSOLE_WIDTH - 2, '-') << "┘" << COLOR_RESET << endl;
}

void displayInputDialog(const char* title, const char* prompt, char* buffer, int maxLength)
{
    cout << COLOR_INPUT_PROMPT;
    cout << "┌─ " << ICON_EDIT << " " << title << string(safeCalculatePadding(title, CONSOLE_WIDTH, 5), '-') << "┐" << endl;
    cout << "│" << string(CONSOLE_WIDTH - 2, ' ') << "│" << endl;
    cout << "│ " << prompt << string(safeCalculatePadding(prompt, CONSOLE_WIDTH, 3), ' ') << "│" << endl;
    cout << "│ " << COLOR_BORDER << string(maxLength + 4, '-') << COLOR_INPUT_PROMPT;
    cout << string(max(0, CONSOLE_WIDTH - maxLength - 7), ' ') << "│" << endl;
    cout << "│ │ " << COLOR_RESET;
}

void displaySelectionMenu(const char* title, const char* options[], int optionCount, int defaultSelection)
{
    cout << COLOR_MENU_ITEM;
    cout << "┌─ " << ICON_MENU << " " << title << string(safeCalculatePadding(title, CONSOLE_WIDTH, 5), '-') << "┐" << endl;
    cout << "│" << string(CONSOLE_WIDTH - 2, ' ') << "│" << endl;
    
    for (int i = 0; i < optionCount; i++) {
        cout << "│ ";
        if (i == defaultSelection) {
            cout << COLOR_MENU_SELECTED << " ▶ " << options[i] << COLOR_MENU_ITEM;
        } else {
            cout << "   " << options[i];
        }
        cout << string(safeCalculatePadding(options[i], CONSOLE_WIDTH, 6), ' ') << "│" << endl;
    }
    
    cout << "│" << string(CONSOLE_WIDTH - 2, ' ') << "│" << endl;
    cout << "└" << string(CONSOLE_WIDTH - 2, '-') << "┘" << COLOR_RESET << endl;
}