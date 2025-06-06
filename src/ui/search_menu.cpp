#include "../../include/ui/search_menu.h"
#include "../../include/algorithms/search.h"
#include "../../include/algorithms/student_search.h"
#include "../../include/ui/common_ui.h"
#include "../../include/utils/constants.h"
#include "../../include/utils/validation.h"
#include <iostream>
#include <cstring>

using namespace std;

/**
 * @brief Nhập tiêu chí tìm kiếm
 */
int inputSearchCriteria()
{
    clearScreen();
    printHeader("CHỌN TIÊU CHÍ TÌM KIẾM");

    cout << GREEN << "Các tiêu chí tìm kiếm có sẵn:" << RESET << endl;
    cout << CYAN << "1. " << RESET << "Mã sinh viên" << endl;
    cout << CYAN << "2. " << RESET << "Họ" << endl;
    cout << CYAN << "3. " << RESET << "Tên" << endl;
    cout << CYAN << "4. " << RESET << "Lớp" << endl;
    cout << CYAN << "5. " << RESET << "Điểm" << endl;
    cout << CYAN << "0. " << RESET << "Quay lại" << endl;

    printDivider();

    int choice;
    cout << YELLOW << "Nhập lựa chọn của bạn (0-5): " << RESET;

    while (!(cin >> choice) || choice < 0 || choice > 5)
    {
        clearInputBuffer();
        printError("Lựa chọn không hợp lệ! Vui lòng nhập số từ 0-5.");
        cout << YELLOW << "Nhập lại lựa chọn: " << RESET;
    }

    clearInputBuffer();
    return choice;
}

/**
 * @brief Nhập thuật toán tìm kiếm (chỉ dành cho Array và Doubly Linked List)
 */
int inputSearchAlgorithm()
{
    clearScreen();
    printHeader("CHỌN THUẬT TOÁN TÌM KIẾM");

    cout << GREEN << "Các thuật toán tìm kiếm có sẵn:" << RESET << endl;
    cout << CYAN << "1. " << RESET << "Tìm kiếm tuần tự (Sequential Search)" << endl;
    cout << CYAN << "   " << RESET << "• Hoạt động với mọi loại dữ liệu" << endl;
    cout << "\n";
    cout << CYAN << "2. " << RESET << "Tìm kiếm nhị phân (Binary Search)" << endl;
    cout << CYAN << "   " << RESET << "• Yêu cầu dữ liệu được sắp xếp trước" << endl;
    cout << CYAN << "   " << RESET << "• Chỉ áp dụng cho tìm kiếm theo điểm" << endl;
    cout << "\n";
    cout << CYAN << "0. " << RESET << "Quay lại" << endl;

    printDivider();

    int choice;
    cout << YELLOW << "Nhập lựa chọn của bạn (0-2): " << RESET;

    while (!(cin >> choice) || choice < 0 || choice > 2)
    {
        clearInputBuffer();
        printError("Lựa chọn không hợp lệ! Vui lòng nhập số từ 0-2.");
        cout << YELLOW << "Nhập lại lựa chọn: " << RESET;
    }

    clearInputBuffer();
    return choice;
}

/**
 * @brief Hỏi người dùng có muốn hiển thị họ tên đảo ngược không
 */
bool askForReversedName()
{
    cout << "\n";
    printInfo("Tùy chọn hiển thị:");
    cout << CYAN << "Bạn có muốn hiển thị họ tên đảo ngược không? (y/n): " << RESET;

    char choice;
    while (!(cin >> choice) || (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N'))
    {
        clearInputBuffer();
        printError("Vui lòng nhập 'y' (có) hoặc 'n' (không).");
        cout << CYAN << "Nhập lại lựa chọn: " << RESET;
    }

    clearInputBuffer();
    return (choice == 'y' || choice == 'Y');
}

/**
 * @brief Thực hiện tìm kiếm sinh viên cho mảng
 */
void performSearchArray(const ArrayStudentList &list, bool isSorted, int sortCriteria)
{
    int searchCriteria = inputSearchCriteria();
    if (searchCriteria == 0)
        return;

    char keyword[100];
    if (!inputSearchKeyword(keyword, searchCriteria))
    {
        printError("Từ khóa tìm kiếm không hợp lệ!");
        cout << YELLOW << "\nNhấn Enter để tiếp tục..." << RESET;
        cin.get();
        return;
    }

    // Chọn thuật toán tìm kiếm
    int algorithmChoice = inputSearchAlgorithm();
    if (algorithmChoice == 0)
        return;

    bool showReversedName = askForReversedName();

    SearchResult result;

    // Quyết định thuật toán tìm kiếm
    if (algorithmChoice == 2)
    { // Binary Search
        if (searchCriteria != SEARCH_BY_SCORE)
        {
            printError("Tìm kiếm nhị phân chỉ hỗ trợ tìm kiếm theo điểm!");
            cout << YELLOW << "\nSẽ chuyển sang tìm kiếm tuần tự..." << RESET;
            algorithmChoice = 1;
        }
        else if (!isSorted || sortCriteria != SORT_BY_SCORE)
        {
            printInfo("Dữ liệu chưa được sắp xếp theo điểm. Đang thực hiện sắp xếp...");
            // Thông báo cần sắp xếp trước khi tìm kiếm nhị phân
            cout << YELLOW << "Lưu ý: Để sử dụng tìm kiếm nhị phân, dữ liệu cần được sắp xếp theo điểm trước." << RESET << endl;
            cout << YELLOW << "Sẽ chuyển sang tìm kiếm tuần tự..." << RESET << endl;
            algorithmChoice = 1;
        }
    }

    if (algorithmChoice == 2 && searchCriteria == SEARCH_BY_SCORE)
    {
        // Dùng binary search cho điểm số đã sắp xếp
        float targetScore = atof(keyword);
        result = binarySearchArrayByScore(list, targetScore);
    }
    else
    {
        // Dùng sequential search
        result = sequentialSearchArray(list, keyword, searchCriteria);
    }

    // Hiển thị kết quả
    displaySearchResults(result, keyword, searchCriteria, showReversedName, getDataStructureName(ARRAY_LIST));

    // Giải phóng bộ nhớ
    freeSearchResult(result);

    cout << YELLOW << "\nNhấn Enter để tiếp tục..." << RESET;
    cin.get();
}

/**
 * @brief Thực hiện tìm kiếm sinh viên cho danh sách liên kết đơn
 */
void performSearchSLL(NodeSLL *head)
{
    int searchCriteria = inputSearchCriteria();
    if (searchCriteria == 0)
        return;

    char keyword[100];
    if (!inputSearchKeyword(keyword, searchCriteria))
    {
        printError("Từ khóa tìm kiếm không hợp lệ!");
        cout << YELLOW << "\nNhấn Enter để tiếp tục..." << RESET;
        cin.get();
        return;
    }

    bool showReversedName = askForReversedName();

    SearchResult result = sequentialSearchSLL(head, keyword, searchCriteria);

    // Hiển thị kết quả
    displaySearchResults(result, keyword, searchCriteria, showReversedName, getDataStructureName(SINGLY_LINKED_LIST));

    // Giải phóng bộ nhớ
    freeSearchResult(result);

    cout << YELLOW << "\nNhấn Enter để tiếp tục..." << RESET;
    cin.get();
}

/**
 * @brief Thực hiện tìm kiếm sinh viên cho danh sách liên kết vòng
 */
void performSearchCLL(NodeSLL *head)
{
    int searchCriteria = inputSearchCriteria();
    if (searchCriteria == 0)
        return;

    char keyword[100];
    if (!inputSearchKeyword(keyword, searchCriteria))
    {
        printError("Từ khóa tìm kiếm không hợp lệ!");
        cout << YELLOW << "\nNhấn Enter để tiếp tục..." << RESET;
        cin.get();
        return;
    }

    bool showReversedName = askForReversedName();

    SearchResult result = sequentialSearchCLL(head, keyword, searchCriteria);

    // Hiển thị kết quả
    displaySearchResults(result, keyword, searchCriteria, showReversedName, getDataStructureName(CIRCULAR_LINKED_LIST));

    // Giải phóng bộ nhớ
    freeSearchResult(result);

    cout << YELLOW << "\nNhấn Enter để tiếp tục..." << RESET;
    cin.get();
}

/**
 * @brief Thực hiện tìm kiếm sinh viên cho danh sách liên kết kép
 */
void performSearchDLL(NodeDLL *head, bool isSorted, int sortCriteria)
{
    int searchCriteria = inputSearchCriteria();
    if (searchCriteria == 0)
        return;

    char keyword[100];
    if (!inputSearchKeyword(keyword, searchCriteria))
    {
        printError("Từ khóa tìm kiếm không hợp lệ!");
        cout << YELLOW << "\nNhấn Enter để tiếp tục..." << RESET;
        cin.get();
        return;
    }

    // Chọn thuật toán tìm kiếm
    int algorithmChoice = inputSearchAlgorithm();
    if (algorithmChoice == 0)
        return;

    bool showReversedName = askForReversedName();

    // Kiểm tra khả năng sử dụng binary search
    bool canUseBinarySearch = false;
    if (algorithmChoice == 2)
    { // Binary Search
        if (searchCriteria != SEARCH_BY_SCORE)
        {
            printError("Tìm kiếm nhị phân chỉ hỗ trợ tìm kiếm theo điểm!");
            cout << YELLOW << "\nSẽ chuyển sang tìm kiếm tuần tự..." << RESET;
        }
        else if (!isSorted || sortCriteria != SORT_BY_SCORE)
        {
            printInfo("Dữ liệu chưa được sắp xếp theo điểm. Cần sắp xếp trước khi tìm kiếm nhị phân.");
            cout << YELLOW << "Sẽ chuyển sang tìm kiếm tuần tự..." << RESET << endl;
        }
        else
        {
            canUseBinarySearch = true;
        }
    }

    SearchResult result = searchDoublyLinkedList(head, keyword, searchCriteria,
                                                 canUseBinarySearch && isSorted,
                                                 sortCriteria);

    // Hiển thị kết quả
    displaySearchResults(result, keyword, searchCriteria, showReversedName, getDataStructureName(DOUBLY_LINKED_LIST));

    // Hiển thị thông tin thuật toán
    cout << "\n";
    cout << YELLOW << "• " << RESET << "Thuật toán: " << BOLD
         << (result.isBinarySearch ? "Binary Search" : "Sequential Search") << RESET << endl;
    cout << YELLOW << "• " << RESET << "Độ phức tạp: " << BOLD
         << (result.isBinarySearch ? "O(log n)" : "O(n)") << RESET << endl;

    if (result.isBinarySearch)
    {
        cout << YELLOW << "• " << RESET << "Lý do: Danh sách đã sắp xếp theo điểm và tìm kiếm theo điểm" << RESET << endl;
    }
    else
    {
        cout << YELLOW << "• " << RESET << "Lý do: ";
        if (!isSorted)
        {
            cout << "Danh sách chưa được sắp xếp" << RESET << endl;
        }
        else if (searchCriteria != sortCriteria)
        {
            cout << "Tiêu chí tìm kiếm khác với tiêu chí sắp xếp" << RESET << endl;
        }
        else
        {
            cout << "Chỉ hỗ trợ binary search cho điểm số" << RESET << endl;
        }
    }

    // Giải phóng bộ nhớ
    freeSearchResult(result);

    cout << YELLOW << "\nNhấn Enter để tiếp tục..." << RESET;
    cin.get();
}

/**
 * @brief Giao diện tìm kiếm sinh viên chính
 */

