#include "../../include/ui/search_menu.h"
#include "../../include/algorithms/searching.h"
#include "../../include/algorithms/sorting.h" // Thêm include cho sorting algorithms
#include "../../include/utils/constants.h"
#include "../../include/ui/common_ui.h"
#include "../../include/utils/validation.h"
#include <iostream>
#include <cstring>

using namespace std;

/**
 * @brief Nhập tiêu chí tìm kiếm dựa trên thuật toán đã chọn
 */
int inputSearchCriteria(int searchAlgorithm)
{
    clearScreen();
    printHeader("CHỌN TIÊU CHÍ TÌM KIẾM");

    cout << GREEN << "Các tiêu chí tìm kiếm có sẵn:" << RESET << endl;

    if (searchAlgorithm == 1)
    { // Sequential Search
        cout << CYAN << "1. " << RESET << "Mã sinh viên" << endl;
        cout << CYAN << "2. " << RESET << "Họ" << endl;
        cout << CYAN << "3. " << RESET << "Tên" << endl;
        cout << CYAN << "4. " << RESET << "Lớp" << endl;
        cout << CYAN << "5. " << RESET << "Điểm" << endl;
        cout << YELLOW << "\n💡 Tìm kiếm tuần tự hỗ trợ tất cả các tiêu chí" << RESET << endl;
    }
    else
    { // Binary Search
        cout << CYAN << "1. " << RESET << "Mã sinh viên" << endl;
        cout << CYAN << "5. " << RESET << "Điểm" << endl;
        cout << YELLOW << "\n💡 Tìm kiếm nhị phân chỉ hỗ trợ mã sinh viên và điểm số" << RESET << endl;
        cout << YELLOW << "💡 Dữ liệu sẽ được sắp xếp tự động nếu cần thiết" << RESET << endl;
    }

    cout << CYAN << "0. " << RESET << "Quay lại" << endl;

    printDivider();

    int choice;
    cout << YELLOW << "Nhập lựa chọn của bạn: " << RESET;

    if (searchAlgorithm == 1)
    { // Sequential Search
        while (!(cin >> choice) || choice < 0 || choice > 5)
        {
            clearInputBuffer();
            printError("Lựa chọn không hợp lệ! Vui lòng nhập số từ 0-5.");
            cout << YELLOW << "Nhập lại lựa chọn: " << RESET;
        }
    }
    else
    { // Binary Search
        while (!(cin >> choice) || (choice != 0 && choice != 1 && choice != 5))
        {
            clearInputBuffer();
            printError("Lựa chọn không hợp lệ! Vui lòng nhập 0, 1 hoặc 5.");
            cout << YELLOW << "Nhập lại lựa chọn: " << RESET;
        }
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
    cout << CYAN << "   " << RESET << "• Hỗ trợ: Mã sinh viên, Điểm số" << endl;
    cout << CYAN << "   " << RESET << "• Tiêu chí tìm kiếm phải khớp với tiêu chí sắp xếp" << endl;
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
    // Bước 1: Chọn thuật toán tìm kiếm
    int algorithmChoice = inputSearchAlgorithm();
    if (algorithmChoice == 0)
        return;

    // Bước 2: Chọn tiêu chí tìm kiếm dựa trên thuật toán
    int searchCriteria = inputSearchCriteria(algorithmChoice);
    if (searchCriteria == 0)
        return;

    // Bước 3: Nhập từ khóa tìm kiếm
    char keyword[100];
    if (!inputSearchKeyword(keyword, searchCriteria))
    {
        printError("Từ khóa tìm kiếm không hợp lệ!");
        cout << YELLOW << "\nNhấn Enter để tiếp tục..." << RESET;
        cin.get();
        return;
    }

    // Bước 4: Kiểm tra và xử lý sắp xếp cho Binary Search
    ArrayStudentList *workingList = const_cast<ArrayStudentList *>(&list);
    bool needsNewSorting = false;
    int newSortCriteria = sortCriteria;

    if (algorithmChoice == 2)
    { // Binary Search
        int requiredSortCriteria = mapSearchToSortCriteria(searchCriteria);

        if (!isSorted || sortCriteria != requiredSortCriteria)
        {
            // Cần sắp xếp mới
            int sortAlgorithm = selectSortAlgorithmForSearch(searchCriteria, ARRAY_LIST);
            if (sortAlgorithm == 0)
            {
                return; // Người dùng hủy bỏ
            }

            // Thực hiện sắp xếp
            if (performSortingArray(*workingList, sortAlgorithm, requiredSortCriteria))
            {
                needsNewSorting = true;
                newSortCriteria = requiredSortCriteria;
            }
            else
            {
                printError("Không thể thực hiện sắp xếp. Chuyển về tìm kiếm tuần tự.");
                algorithmChoice = 1; // Chuyển về sequential search
            }
        }
    }

    bool showReversedName = askForReversedName();

    SearchResult result;

    // Bước 5: Thực hiện tìm kiếm
    if (algorithmChoice == 2 && canUseBinarySearch(searchCriteria, newSortCriteria, true))
    {
        // Dùng binary search
        result = binarySearchArray(*workingList, keyword, searchCriteria, newSortCriteria);
    }
    else
    {
        // Dùng sequential search
        result = sequentialSearchArray(*workingList, keyword, searchCriteria);
    }

    // Hiển thị kết quả
    displaySearchResultsWithDataStructure(result, keyword, searchCriteria, showReversedName, getDataStructureName(ARRAY_LIST));

    // Hiển thị thông tin thuật toán
    if (needsNewSorting)
    {
        cout << "\n"
             << GREEN << "📊 Thông tin sắp xếp:" << RESET << endl;
        cout << YELLOW << "• " << RESET << "Dữ liệu đã được sắp xếp theo ";
        switch (newSortCriteria)
        {
        case SORT_BY_STUDENT_ID:
            cout << "mã sinh viên";
            break;
        case SORT_BY_SCORE:
            cout << "điểm số";
            break;
        default:
            cout << "tiêu chí được chọn";
        }
        cout << " để hỗ trợ tìm kiếm nhị phân" << endl;
    }

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
    printInfo("Danh sách liên kết đơn chỉ hỗ trợ tìm kiếm tuần tự");

    int searchCriteria = inputSearchCriteria(1); // Chỉ sequential search
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
    displaySearchResultsWithDataStructure(result, keyword, searchCriteria, showReversedName, getDataStructureName(SINGLY_LINKED_LIST));

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
    printInfo("Danh sách liên kết vòng chỉ hỗ trợ tìm kiếm tuần tự");

    int searchCriteria = inputSearchCriteria(1); // Chỉ sequential search
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
    displaySearchResultsWithDataStructure(result, keyword, searchCriteria, showReversedName, getDataStructureName(CIRCULAR_LINKED_LIST));

    // Giải phóng bộ nhớ
    freeSearchResult(result);

    cout << YELLOW << "\nNhấn Enter để tiếp tục..." << RESET;
    cin.get();
}

/**
 * @brief Thực hiện tìm kiếm sinh viên cho danh sách liên kết kép
 */
void performSearchDLL(NodeDLL *head, NodeDLL *tail, bool isSorted, int sortCriteria)
{
    // Bước 1: Chọn thuật toán tìm kiếm
    int algorithmChoice = inputSearchAlgorithm();
    if (algorithmChoice == 0)
        return;

    // Bước 2: Chọn tiêu chí tìm kiếm dựa trên thuật toán
    int searchCriteria = inputSearchCriteria(algorithmChoice);
    if (searchCriteria == 0)
        return;

    // Bước 3: Nhập từ khóa tìm kiếm
    char keyword[100];
    if (!inputSearchKeyword(keyword, searchCriteria))
    {
        printError("Từ khóa tìm kiếm không hợp lệ!");
        cout << YELLOW << "\nNhấn Enter để tiếp tục..." << RESET;
        cin.get();
        return;
    }

    // Bước 4: Kiểm tra và xử lý sắp xếp cho Binary Search
    bool needsNewSorting = false;
    int newSortCriteria = sortCriteria;

    if (algorithmChoice == 2)
    { // Binary Search
        int requiredSortCriteria = mapSearchToSortCriteria(searchCriteria);

        if (!isSorted || sortCriteria != requiredSortCriteria)
        {
            // Cần sắp xếp mới
            int sortAlgorithm = selectSortAlgorithmForSearch(searchCriteria, DOUBLY_LINKED_LIST);
            if (sortAlgorithm == 0)
            {
                return; // Người dùng hủy bỏ
            }

            // Thực hiện sắp xếp
            NodeDLL *headPtr = const_cast<NodeDLL *>(head);
            NodeDLL *tailPtr = const_cast<NodeDLL *>(tail);

            if (performSortingDLL(headPtr, tailPtr, sortAlgorithm, requiredSortCriteria))
            {
                needsNewSorting = true;
                newSortCriteria = requiredSortCriteria;
                // Cập nhật head sau khi sắp xếp
                head = headPtr;
            }
            else
            {
                printError("Không thể thực hiện sắp xếp. Chuyển về tìm kiếm tuần tự.");
                algorithmChoice = 1; // Chuyển về sequential search
            }
        }
    }

    bool showReversedName = askForReversedName();

    // Bước 5: Thực hiện tìm kiếm
    SearchResult result = searchDoublyLinkedList(head, keyword, searchCriteria,
                                                 algorithmChoice == 2 && canUseBinarySearch(searchCriteria, newSortCriteria, true),
                                                 newSortCriteria);

    // Hiển thị kết quả
    displaySearchResultsWithDataStructure(result, keyword, searchCriteria, showReversedName, getDataStructureName(DOUBLY_LINKED_LIST));

    // Hiển thị thông tin thuật toán
    cout << "\n";
    cout << YELLOW << "• " << RESET << "Thuật toán: " << BOLD
         << (result.isBinarySearch ? "Binary Search" : "Sequential Search") << RESET << endl;
    cout << YELLOW << "• " << RESET << "Độ phức tạp: " << BOLD
         << (result.isBinarySearch ? "O(log n)" : "O(n)") << RESET << endl;

    if (result.isBinarySearch)
    {
        cout << YELLOW << "• " << RESET << "Lý do: Danh sách đã sắp xếp và tìm kiếm theo tiêu chí phù hợp" << RESET << endl;
    }
    else
    {
        cout << YELLOW << "• " << RESET << "Lý do: ";
        if (algorithmChoice == 1)
        {
            cout << "Người dùng chọn tìm kiếm tuần tự" << RESET << endl;
        }
        else if (!isSorted && !needsNewSorting)
        {
            cout << "Danh sách chưa được sắp xếp" << RESET << endl;
        }
        else if (searchCriteria != newSortCriteria && !needsNewSorting)
        {
            cout << "Tiêu chí tìm kiếm khác với tiêu chí sắp xếp" << RESET << endl;
        }
        else
        {
            cout << "Chuyển về sequential search do điều kiện không phù hợp" << RESET << endl;
        }
    }

    if (needsNewSorting)
    {
        cout << "\n"
             << GREEN << "📊 Thông tin sắp xếp:" << RESET << endl;
        cout << YELLOW << "• " << RESET << "Dữ liệu đã được sắp xếp theo ";
        switch (newSortCriteria)
        {
        case SORT_BY_STUDENT_ID:
            cout << "mã sinh viên";
            break;
        case SORT_BY_SCORE:
            cout << "điểm số";
            break;
        default:
            cout << "tiêu chí được chọn";
        }
        cout << " để hỗ trợ tìm kiếm nhị phân" << endl;
    }

    // Giải phóng bộ nhớ
    freeSearchResult(result);

    cout << YELLOW << "\nNhấn Enter để tiếp tục..." << RESET;
    cin.get();
}

/**
 * @brief Thực hiện sắp xếp cho Array List
 */
bool performSortingArray(ArrayStudentList &list, int sortAlgorithm, int sortCriteria)
{
    printInfo("Đang thực hiện sắp xếp...");

    try
    {
        switch (sortAlgorithm)
        {
        case BUBBLE_SORT:
            bubbleSortArrayList(list, sortCriteria);
            break;
        case SELECTION_SORT:
            selectionSortArrayList(list, sortCriteria);
            break;
        case INSERTION_SORT:
            insertionSortArrayList(list, sortCriteria);
            break;
        case QUICK_SORT:
            quickSortArrayList(list, sortCriteria);
            break;
        case MERGE_SORT:
            mergeSortArrayList(list, sortCriteria);
            break;
        case HEAP_SORT:
            heapSortArrayList(list, sortCriteria);
            break;
        default:
            printError("Thuật toán sắp xếp không hỗ trợ!");
            return false;
        }
        printSuccess("Sắp xếp hoàn tất!");
        return true;
    }
    catch (...)
    {
        printError("Có lỗi xảy ra trong quá trình sắp xếp!");
        return false;
    }
}

/**
 * @brief Thực hiện sắp xếp cho Doubly Linked List
 */
bool performSortingDLL(NodeDLL *&head, NodeDLL *&tail, int sortAlgorithm, int sortCriteria)
{
    printInfo("Đang thực hiện sắp xếp...");

    try
    {
        switch (sortAlgorithm)
        {
        case BUBBLE_SORT:
            bubbleSortDLL(head, tail, sortCriteria);
            break;
        case SELECTION_SORT:
            selectionSortDLL(head, tail, sortCriteria);
            break;
        case INSERTION_SORT:
            insertionSortDLL(head, tail, sortCriteria);
            break;
        case QUICK_SORT:
            quickSortDLL(head, tail, sortCriteria);
            break;
        case MERGE_SORT:
            mergeSortDLL(&head, sortCriteria);
            break;
        case HEAP_SORT:
            heapSortDLL(head, tail, sortCriteria);
            break;
        default:
            printError("Thuật toán sắp xếp không hỗ trợ!");
            return false;
        }
        printSuccess("Sắp xếp hoàn tất!");
        return true;
    }
    catch (...)
    {
        printError("Có lỗi xảy ra trong quá trình sắp xếp!");
        return false;
    }
}

/**
 * @brief Chọn thuật toán sắp xếp dựa trên tiêu chí tìm kiếm và cấu trúc dữ liệu
 */
int selectSortAlgorithmForSearch(int searchCriteria, int dataStructureType)
{
    clearScreen();
    printHeader("CHỌN THUẬT TOÁN SẮP XẾP TRƯỚC KHI TÌM KIẾM");

    cout << GREEN << "Dữ liệu cần được sắp xếp trước khi thực hiện tìm kiếm nhị phân!" << RESET << endl;

    // Hiển thị tiêu chí sắp xếp được chọn
    cout << YELLOW << "Tiêu chí sắp xếp: " << RESET;
    switch (searchCriteria)
    {
    case SEARCH_BY_STUDENT_ID:
        cout << "Mã sinh viên" << endl;
        break;
    case SEARCH_BY_SCORE:
        cout << "Điểm số" << endl;
        break;
    default:
        cout << "Không xác định" << endl;
    }

    cout << "\n"
         << GREEN << "Các thuật toán sắp xếp có sẵn:" << RESET << endl;

    // Hiển thị thuật toán sắp xếp phù hợp với cấu trúc dữ liệu
    if (dataStructureType == ARRAY_LIST)
    {
        cout << CYAN << "1. " << RESET << "Bubble Sort" << endl;
        cout << CYAN << "2. " << RESET << "Selection Sort" << endl;
        cout << CYAN << "3. " << RESET << "Insertion Sort" << endl;
        cout << CYAN << "4. " << RESET << "Quick Sort" << endl;
        cout << CYAN << "5. " << RESET << "Merge Sort" << endl;
        cout << CYAN << "6. " << RESET << "Heap Sort" << endl;
    }
    else if (dataStructureType == DOUBLY_LINKED_LIST)
    {
        cout << CYAN << "1. " << RESET << "Bubble Sort" << endl;
        cout << CYAN << "2. " << RESET << "Selection Sort" << endl;
        cout << CYAN << "3. " << RESET << "Insertion Sort" << endl;
        cout << CYAN << "4. " << RESET << "Quick Sort" << endl;
        cout << CYAN << "5. " << RESET << "Merge Sort" << endl;
        cout << CYAN << "6. " << RESET << "Heap Sort" << endl;
    }

    cout << CYAN << "0. " << RESET << "Hủy bỏ và quay lại" << endl;

    printDivider();

    int choice;
    cout << YELLOW << "Nhập lựa chọn của bạn (0-6): " << RESET;

    while (!(cin >> choice) || choice < 0 || choice > 6)
    {
        clearInputBuffer();
        printError("Lựa chọn không hợp lệ! Vui lòng nhập số từ 0-6.");
        cout << YELLOW << "Nhập lại lựa chọn: " << RESET;
    }

    clearInputBuffer();
    return choice;
}

/**
 * @brief Giao diện tìm kiếm sinh viên chính
 */
