#include "../../include/core/operations.h"
#include "../../include/utils/validation.h"
#include "../../include/utils/common_utils.h"
#include "../../include/ui/search_menu.h"
#include "../../include/data_structures/binary_search_tree.h"
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <chrono>
#include <cstring>

using namespace std;

// Helper function to get criteria name
const char *getCriteriaName(int sortCriteria)
{
    switch (sortCriteria)
    {
    case SORT_BY_STUDENT_ID:
        return "mã sinh viên";
    case SORT_BY_NAME:
        return "tên sinh viên";
    case SORT_BY_SCORE:
        return "điểm số";
    default:
        return "không xác định";
    }
}

// Hàm kiểm tra xem một cấu trúc dữ liệu có rỗng hay không
bool isDataStructureEmpty(int dataStructureType,
                          const ArrayStudentList &arrayList,
                          NodeSLL *singlyLinkedList,
                          NodeSLL *circularLinkedList,
                          NodeDLL *doublyLinkedListHead,
                          NodeBST *binarySearchTree)
{
    switch (dataStructureType)
    {
    case ARRAY_LIST:
        return arrayList.count == 0;
    case SINGLY_LINKED_LIST:
        return singlyLinkedList == NULL;
    case CIRCULAR_LINKED_LIST:
        return circularLinkedList == NULL;
    case DOUBLY_LINKED_LIST:
        return doublyLinkedListHead == NULL;
    case BINARY_SEARCH_TREE:
        return binarySearchTree == NULL;
    default:
        return true; // Mặc định là cấu trúc rỗng
    }
}

// Hàm kiểm tra sinh viên tồn tại trong cấu trúc dữ liệu
bool isStudentExists(const char *studentID, int dataStructureType,
                     const ArrayStudentList &arrayList,
                     NodeSLL *singlyLinkedList,
                     NodeSLL *circularLinkedList,
                     NodeDLL *doublyLinkedListHead,
                     NodeBST *binarySearchTree)
{
    switch (dataStructureType)
    {
    case ARRAY_LIST:
        return searchInArrayList(arrayList, studentID) != -1;
    case SINGLY_LINKED_LIST:
        return searchInSLL(singlyLinkedList, studentID) != NULL;
    case CIRCULAR_LINKED_LIST:
        return searchInCLL(circularLinkedList, studentID) != NULL;
    case DOUBLY_LINKED_LIST:
        return searchInDLL(doublyLinkedListHead, studentID) != NULL;
    case BINARY_SEARCH_TREE:
        return isStudentExistsInBST(binarySearchTree, studentID);
    default:
        return false; // Mặc định là không tồn tại
    }
}

// Hàm kiểm tra trùng mã sinh viên và hiển thị thông báo lỗi
bool validateAndShowDuplicateStudentID(const string &studentID, int dataStructureType,
                                       const ArrayStudentList &arrayList,
                                       NodeSLL *singlyLinkedList,
                                       NodeSLL *circularLinkedList,
                                       NodeDLL *doublyLinkedListHead,
                                       NodeBST *binarySearchTree)
{
    bool isExist = isStudentExists(studentID.c_str(), dataStructureType, arrayList,
                                   singlyLinkedList, circularLinkedList, doublyLinkedListHead, binarySearchTree);
    if (isExist)
    {
        printError(("Mã sinh viên " + studentID + " đã tồn tại!").c_str());
    }
    return !isExist;
}

// Hàm thoát chương trình, giải phóng bộ nhớ
void exitProgram(NodeSLL *&singlyLinkedList,
                 NodeSLL *&circularLinkedList,
                 NodeDLL *&doublyLinkedListHead,
                 NodeDLL *&doublyLinkedListTail,
                 NodeBST *&binarySearchTree)
{
    printInfo("Đang thoát chương trình...");

    // Giải phóng bộ nhớ
    freeSLL(singlyLinkedList);
    freeCLL(circularLinkedList);
    freeDLL(doublyLinkedListHead, doublyLinkedListTail);
    freeBST(binarySearchTree);
}

// Hàm xác nhận hủy bỏ thao tác nhập liệu
bool confirmCancel()
{
    cout << "Bạn có chắc muốn hủy thao tác? (Nhập 0 để hủy, nhập khác để tiếp tục): ";
    string confirm;
    cin >> confirm;
    clearInputBuffer();

    if (confirm == "0")
    {
        printInfo("Đã hủy bỏ thao tác nhập liệu.");
        return true; // Xác nhận hủy
    }
    printInfo("Tiếp tục nhập liệu.");
    return false; // Tiếp tục nhập liệu
}

// Hàm thêm sinh viên vào cấu trúc dữ liệu đã chọn
bool addStudentToDataStructure(const Student &student, int dataStructureType,
                               ArrayStudentList &arrayList,
                               NodeSLL *&singlyLinkedList,
                               NodeSLL *&circularLinkedList,
                               NodeDLL *&doublyLinkedListHead,
                               NodeDLL *&doublyLinkedListTail,
                               NodeBST *&binarySearchTree)
{
    bool success = true;

    switch (dataStructureType)
    {
    case ARRAY_LIST:
        if (addToArrayList(arrayList, student))
        {
            printSuccess("Đã thêm sinh viên vào danh sách mảng thành công.");
        }
        else
        {
            printError("Không thể thêm sinh viên. Danh sách mảng đã đầy.");
            success = false;
        }
        break;
    case SINGLY_LINKED_LIST:
        addToTailSLL(singlyLinkedList, student);
        printSuccess("Đã thêm sinh viên vào danh sách liên kết đơn thành công.");
        break;
    case CIRCULAR_LINKED_LIST:
        addToCLL(circularLinkedList, student);
        printSuccess("Đã thêm sinh viên vào danh sách liên kết vòng thành công.");
        break;
    case DOUBLY_LINKED_LIST:
        addToTailDLL(doublyLinkedListHead, doublyLinkedListTail, student);
        printSuccess("Đã thêm sinh viên vào danh sách liên kết đôi thành công.");
        break;
    case BINARY_SEARCH_TREE:
        insertToBST(binarySearchTree, student);
        printSuccess("Đã thêm sinh viên vào cây tìm kiếm nhị phân thành công.");
        break;
    default:
        printError("Cấu trúc dữ liệu không hợp lệ.");
        success = false;
        break;
    }

    return success;
}

// Hàm xóa sinh viên khỏi cấu trúc dữ liệu đã chọn
bool deleteStudentFromDataStructure(const char *studentID, int dataStructureType,
                                    ArrayStudentList &arrayList,
                                    NodeSLL *&singlyLinkedList,
                                    NodeSLL *&circularLinkedList,
                                    NodeDLL *&doublyLinkedListHead,
                                    NodeDLL *&doublyLinkedListTail)
{
    bool success = false;

    switch (dataStructureType)
    {
    case ARRAY_LIST:
        if (deleteFromArrayList(arrayList, studentID))
        {
            printSuccess("Đã xóa sinh viên khỏi danh sách mảng thành công.");
            success = true;
        }
        else
        {
            printError("Không tìm thấy sinh viên để xóa trong danh sách mảng.");
        }
        break;
    case SINGLY_LINKED_LIST:
        if (deleteFromSLL(singlyLinkedList, studentID))
        {
            printSuccess("Đã xóa sinh viên khỏi danh sách liên kết đơn thành công.");
            success = true;
        }
        else
        {
            printError("Không tìm thấy sinh viên để xóa trong danh sách liên kết đơn.");
        }
        break;
    case CIRCULAR_LINKED_LIST:
        if (deleteFromCLL(circularLinkedList, studentID))
        {
            printSuccess("Đã xóa sinh viên khỏi danh sách liên kết vòng thành công.");
            success = true;
        }
        else
        {
            printError("Không tìm thấy sinh viên để xóa trong danh sách liên kết vòng.");
        }
        break;
    case DOUBLY_LINKED_LIST:
        if (deleteFromDLL(doublyLinkedListHead, doublyLinkedListTail, studentID))
        {
            printSuccess("Đã xóa sinh viên khỏi danh sách liên kết đôi thành công.");
            success = true;
        }
        else
        {
            printError("Không tìm thấy sinh viên để xóa trong danh sách liên kết đôi.");
        }
        break;
    case BINARY_SEARCH_TREE:
        printInfo("Chức năng xóa theo mã sinh viên không áp dụng cho BST.");
        printInfo("Sử dụng chức năng xóa node theo điểm số trong menu BST.");
        break;
    default:
        printError("Cấu trúc dữ liệu không hợp lệ.");
        break;
    }

    return success;
}

// Hàm cập nhật sinh viên trong cấu trúc dữ liệu đã chọn
bool updateStudentInDataStructure(const Student &student, int dataStructureType,
                                  ArrayStudentList &arrayList,
                                  NodeSLL *&singlyLinkedList,
                                  NodeSLL *&circularLinkedList,
                                  NodeDLL *&doublyLinkedListHead)
{
    bool success = false;

    switch (dataStructureType)
    {
    case ARRAY_LIST:
        if (updateInArrayList(arrayList, student))
        {
            printSuccess("Đã cập nhật sinh viên trong danh sách mảng thành công.");
            success = true;
        }
        else
        {
            printError("Không tìm thấy sinh viên để cập nhật trong danh sách mảng.");
        }
        break;
    case SINGLY_LINKED_LIST:
        if (updateInSLL(singlyLinkedList, student))
        {
            printSuccess("Đã cập nhật sinh viên trong danh sách liên kết đơn thành công.");
            success = true;
        }
        else
        {
            printError("Không tìm thấy sinh viên để cập nhật trong danh sách liên kết đơn.");
        }
        break;
    case CIRCULAR_LINKED_LIST:
        if (updateInCLL(circularLinkedList, student))
        {
            printSuccess("Đã cập nhật sinh viên trong danh sách liên kết vòng thành công.");
            success = true;
        }
        else
        {
            printError("Không tìm thấy sinh viên để cập nhật trong danh sách liên kết vòng.");
        }
        break;
    case DOUBLY_LINKED_LIST:
        if (updateInDLL(doublyLinkedListHead, student))
        {
            printSuccess("Đã cập nhật sinh viên trong danh sách liên kết đôi thành công.");
            success = true;
        }
        else
        {
            printError("Không tìm thấy sinh viên để cập nhật trong danh sách liên kết đôi.");
        }
        break;
    case BINARY_SEARCH_TREE:
        printWarning("Chức năng cập nhật chưa được hiện thực cho cây tìm kiếm nhị phân.");
        break;
    default:
        printError("Cấu trúc dữ liệu không hợp lệ.");
        break;
    }

    return success;
}

// Hàm hiển thị danh sách sinh viên hiện tại
void displayCurrentList(int dataStructureType,
                        const ArrayStudentList &arrayList,
                        NodeSLL *singlyLinkedList,
                        NodeSLL *circularLinkedList,
                        NodeDLL *doublyLinkedListHead,
                        NodeBST *binarySearchTree)
{
    switch (dataStructureType)
    {
    case ARRAY_LIST:
        displayArrayList(arrayList);
        break;
    case SINGLY_LINKED_LIST:
        displaySLL(singlyLinkedList);
        break;
    case CIRCULAR_LINKED_LIST:
        displayCLL(circularLinkedList);
        break;
    case DOUBLY_LINKED_LIST:
        displayDLL(doublyLinkedListHead);
        break;
    case BINARY_SEARCH_TREE:
        if (binarySearchTree != NULL)
        {
            cout << BOLD << CYAN << "\n=== CÂY TÌM KIẾM NHỊ PHÂN ===" << RESET << endl;

            cout << "\n"
                 << BOLD << YELLOW << "Duyệt cây theo thứ tự giữa (In-order):" << RESET;
            inorderTraversalBST(binarySearchTree);
        }
        else
        {
            printWarning("Cây tìm kiếm nhị phân rỗng!");
        }
        break;
    default:
        printError("Cấu trúc dữ liệu không hợp lệ.");
        break;
    }
}

// Hàm tìm kiếm sinh viên đơn giản với nhiều tiêu chí
void searchStudentInDataStructure(int dataStructureType,
                                  const ArrayStudentList &arrayList,
                                  NodeSLL *singlyLinkedList,
                                  NodeSLL *circularLinkedList,
                                  NodeDLL *doublyLinkedListHead,
                                  int currentSortCriteria)
{
    // Kiểm tra trường hợp đặc biệt cho BST
    if (dataStructureType == BINARY_SEARCH_TREE)
    {
        printWarning("Chức năng tìm kiếm chưa được hiện thực cho cây tìm kiếm nhị phân.");
        return;
    }

    // Kiểm tra cấu trúc dữ liệu có rỗng không
    if (isDataStructureEmpty(dataStructureType, arrayList, singlyLinkedList, circularLinkedList, doublyLinkedListHead, nullptr))
    {
        printWarning("Cấu trúc dữ liệu hiện tại đang rỗng. Vui lòng thêm dữ liệu trước khi tìm kiếm.");
        return;
    }

    // Sử dụng giao diện tìm kiếm với lựa chọn thuật toán
    switch (dataStructureType)
    {
    case ARRAY_LIST:
        performSearchArray(arrayList, (currentSortCriteria != -1), currentSortCriteria);
        break;
    case SINGLY_LINKED_LIST:
        performSearchSLL(singlyLinkedList);
        break;
    case CIRCULAR_LINKED_LIST:
        performSearchCLL(circularLinkedList);
        break;
    case DOUBLY_LINKED_LIST:
        performSearchDLL(doublyLinkedListHead, (currentSortCriteria != -1), currentSortCriteria);
        break;
    default:
        printError("Cấu trúc dữ liệu không được hỗ trợ!");
        return;
    }
}

// Hàm thực hiện thống kê sinh viên
void performStatistics(int dataStructureType,
                       const ArrayStudentList &arrayList,
                       NodeSLL *singlyLinkedList,
                       NodeSLL *circularLinkedList,
                       NodeDLL *doublyLinkedListHead)
{
    // Kiểm tra dữ liệu có rỗng không
    if (isDataStructureEmpty(dataStructureType, arrayList, singlyLinkedList, circularLinkedList, doublyLinkedListHead, NULL))
    {
        printError("Danh sách sinh viên trống. Vui lòng nhập dữ liệu trước khi thực hiện thống kê!");
        return;
    }

    // Hiển thị menu chọn loại thống kê
    printHeader("CHỌN LOẠI THỐNG KÊ");
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
    cout << "┃                                       MENU THỐNG KÊ                                          ┃" << endl;
    cout << "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫" << endl;
    cout << "┃ 1. Thống kê tổng quát                                                                       ┃" << endl;
    cout << "┃ 2. Thống kê theo lớp                                                                        ┃" << endl;
    cout << "┃ 3. Cả hai loại thống kê                                                                     ┃" << endl;
    cout << "┃ 0. Quay lại                                                                                 ┃" << endl;
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;

    int choice;
    do
    {
        cout << "Nhập lựa chọn: ";
        cin >> choice;
        
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            printError("Vui lòng nhập số!");
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (choice)
        {
        case 1:
            performGeneralStatistics(dataStructureType, arrayList, singlyLinkedList, circularLinkedList, doublyLinkedListHead);
            break;
        case 2:
            displayAllClassStatistics(dataStructureType, arrayList, singlyLinkedList, circularLinkedList, doublyLinkedListHead);
            break;
        case 3:
            performGeneralStatistics(dataStructureType, arrayList, singlyLinkedList, circularLinkedList, doublyLinkedListHead);
            cout << endl;
            displayAllClassStatistics(dataStructureType, arrayList, singlyLinkedList, circularLinkedList, doublyLinkedListHead);
            break;
        case 0:
            return;
        default:
            printError("Lựa chọn không hợp lệ!");
            break;
        }
    } while (choice != 0 && choice != 1 && choice != 2 && choice != 3);
}

// Hàm thống kê tổng quát (logic cũ của performStatistics)
void performGeneralStatistics(int dataStructureType,
                             const ArrayStudentList &arrayList,
                             NodeSLL *singlyLinkedList,
                             NodeSLL *circularLinkedList,
                             NodeDLL *doublyLinkedListHead)
{
    float highest = 0.0f, lowest = 0.0f, average = 0.0f;
    bool isEmpty = false;

    // Kiểm tra cấu trúc dữ liệu có rỗng không và tính toán thống kê
    switch (dataStructureType)
    {
    case ARRAY_LIST:
        if (arrayList.count == 0)
        {
            isEmpty = true;
        }
        else
        {
            highest = findHighestScore(arrayList);
            lowest = findLowestScore(arrayList);
            average = calculateAverageScore(arrayList);
        }
        break;

    case SINGLY_LINKED_LIST:
        if (singlyLinkedList == NULL)
        {
            isEmpty = true;
        }
        else
        {
            highest = findHighestScoreSLL(singlyLinkedList);
            lowest = findLowestScoreSLL(singlyLinkedList);
            average = calculateAverageScoreSLL(singlyLinkedList);
        }
        break;

    case CIRCULAR_LINKED_LIST:
        if (circularLinkedList == NULL)
        {
            isEmpty = true;
        }
        else
        {
            highest = findHighestScoreCLL(circularLinkedList);
            lowest = findLowestScoreCLL(circularLinkedList);
            average = calculateAverageScoreCLL(circularLinkedList);
        }
        break;

    case DOUBLY_LINKED_LIST:
        if (doublyLinkedListHead == NULL)
        {
            isEmpty = true;
        }
        else
        {
            highest = findHighestScoreDLL(doublyLinkedListHead);
            lowest = findLowestScoreDLL(doublyLinkedListHead);
            average = calculateAverageScoreDLL(doublyLinkedListHead);
        }
        break;

    default:
        printWarning("Chức năng thống kê chưa được hiện thực cho cấu trúc dữ liệu này.");
        return;
    }

    if (isEmpty)
    {
        printWarning("Danh sách sinh viên rỗng. Không có thống kê.");
        return;
    }

    // Hiển thị thống kê cơ bản
    printHeader("THỐNG KÊ ĐIỂM SINH VIÊN");

    // Đếm số lượng sinh viên theo từng cấu trúc dữ liệu
    int studentCount = 0;
    switch (dataStructureType)
    {
    case ARRAY_LIST:
        studentCount = arrayList.count;
        break;
    case SINGLY_LINKED_LIST:
    case CIRCULAR_LINKED_LIST:
    case DOUBLY_LINKED_LIST:
        // Đếm node trong linked list
        switch (dataStructureType)
        {
        case SINGLY_LINKED_LIST:
        {
            NodeSLL *current = singlyLinkedList;
            while (current != NULL)
            {
                studentCount++;
                current = current->next;
            }
        }
        break;
        case CIRCULAR_LINKED_LIST:
        {
            NodeSLL *current = circularLinkedList;
            if (current != NULL)
            {
                do
                {
                    studentCount++;
                    current = current->next;
                } while (current != circularLinkedList);
            }
        }
        break;
        case DOUBLY_LINKED_LIST:
        {
            NodeDLL *current = doublyLinkedListHead;
            while (current != NULL)
            {
                studentCount++;
                current = current->next;
            }
        }
        break;
        }
        break;
    }

    cout << "Số lượng sinh viên: " << studentCount << "\n";
    cout << GREEN << "Điểm cao nhất: " << highest << RESET << "\n";
    cout << RED << "Điểm thấp nhất: " << lowest << RESET << "\n";
    cout << BLUE << "Điểm trung bình: " << fixed << setprecision(2) << average << RESET << "\n";

    // Hiển thị sinh viên có điểm cao nhất
    cout << CYAN << "\nSinh viên có điểm cao nhất:\n"
         << RESET;
    printDivider();

    switch (dataStructureType)
    {
    case ARRAY_LIST:
        for (int i = 0; i < arrayList.count; i++)
        {
            if (arrayList.students[i].score == highest)
            {
                displayStudent(arrayList.students[i]);
                printDivider();
            }
        }
        break;

    case SINGLY_LINKED_LIST:
    {
        NodeSLL *current = singlyLinkedList;
        while (current != NULL)
        {
            if (current->info.score == highest)
            {
                displayStudent(current->info);
                printDivider();
            }
            current = current->next;
        }
    }
    break;

    case CIRCULAR_LINKED_LIST:
    {
        NodeSLL *current = circularLinkedList;
        if (current != NULL)
        {
            do
            {
                if (current->info.score == highest)
                {
                    displayStudent(current->info);
                    printDivider();
                }
                current = current->next;
            } while (current != circularLinkedList);
        }
    }
    break;

    case DOUBLY_LINKED_LIST:
    {
        NodeDLL *current = doublyLinkedListHead;
        while (current != NULL)
        {
            if (current->info.score == highest)
            {
                displayStudent(current->info);
                printDivider();
            }
            current = current->next;
        }
    }
    break;
    }

    // Hiển thị sinh viên có điểm thấp nhất
    cout << CYAN << "\nSinh viên có điểm thấp nhất:\n"
         << RESET;
    printDivider();

    switch (dataStructureType)
    {
    case ARRAY_LIST:
        for (int i = 0; i < arrayList.count; i++)
        {
            if (arrayList.students[i].score == lowest)
            {
                displayStudent(arrayList.students[i]);
                printDivider();
            }
        }
        break;

    case SINGLY_LINKED_LIST:
    {
        NodeSLL *current = singlyLinkedList;
        while (current != NULL)
        {
            if (current->info.score == lowest)
            {
                displayStudent(current->info);
                printDivider();
            }
            current = current->next;
        }
    }
    break;

    case CIRCULAR_LINKED_LIST:
    {
        NodeSLL *current = circularLinkedList;
        if (current != NULL)
        {
            do
            {
                if (current->info.score == lowest)
                {
                    displayStudent(current->info);
                    printDivider();
                }
                current = current->next;
            } while (current != circularLinkedList);
        }
    }
    break;

    case DOUBLY_LINKED_LIST:
    {
        NodeDLL *current = doublyLinkedListHead;
        while (current != NULL)
        {
            if (current->info.score == lowest)
            {
                displayStudent(current->info);
                printDivider();
            }
            current = current->next;
        }
    }
    break;
    }
}

// Hàm sắp xếp danh sách sinh viên theo tiêu chí được chọn sử dụng thuật toán được chọn
bool sortStudentList(int dataStructureType, int sortAlgorithm, int sortCriteria,
                     ArrayStudentList &arrayList,
                     NodeSLL *&singlyLinkedList,
                     NodeSLL *&circularLinkedList,
                     NodeDLL *&doublyLinkedListHead,
                     NodeDLL *&doublyLinkedListTail)
{
    bool success = false;

    // Hiển thị thông tin tiêu chí sắp xếp được chọn
    printInfo(("Thực hiện sắp xếp theo " + string(getCriteriaName(sortCriteria)) + "...").c_str());

    switch (dataStructureType)
    {
    case ARRAY_LIST:
        switch (sortAlgorithm)
        {
        case BUBBLE_SORT:
            bubbleSortArrayList(arrayList, sortCriteria);
            printSuccess(("Đã sắp xếp danh sách mảng theo " + string(getCriteriaName(sortCriteria)) + " bằng thuật toán Bubble Sort.").c_str());
            success = true;
            break;
        case INSERTION_SORT:
            insertionSortArrayList(arrayList, sortCriteria);
            printSuccess(("Đã sắp xếp danh sách mảng theo " + string(getCriteriaName(sortCriteria)) + " bằng thuật toán Insertion Sort.").c_str());
            success = true;
            break;
        case SELECTION_SORT:
            selectionSortArrayList(arrayList, sortCriteria);
            printSuccess(("Đã sắp xếp danh sách mảng theo " + string(getCriteriaName(sortCriteria)) + " bằng thuật toán Selection Sort.").c_str());
            success = true;
            break;
        case QUICK_SORT:
            quickSortArrayList(arrayList, sortCriteria);
            printSuccess(("Đã sắp xếp danh sách mảng theo " + string(getCriteriaName(sortCriteria)) + " bằng thuật toán Quick Sort.").c_str());
            success = true;
            break;
        case HEAP_SORT:
            heapSortArrayList(arrayList, sortCriteria);
            printSuccess(("Đã sắp xếp danh sách mảng theo " + string(getCriteriaName(sortCriteria)) + " bằng thuật toán Heap Sort.").c_str());
            success = true;
            break;
        case MERGE_SORT:
            mergeSortArrayList(arrayList, sortCriteria);
            printSuccess(("Đã sắp xếp danh sách mảng theo " + string(getCriteriaName(sortCriteria)) + " bằng thuật toán Merge Sort.").c_str());
            success = true;
            break;
        default:
            printError("Thuật toán sắp xếp không hợp lệ cho danh sách mảng.");
            break;
        }
        break;

    case SINGLY_LINKED_LIST:
        switch (sortAlgorithm)
        {
        case BUBBLE_SORT:
            bubbleSortSLL(singlyLinkedList, sortCriteria);
            printSuccess(("Đã sắp xếp danh sách liên kết đơn theo " + string(getCriteriaName(sortCriteria)) + " bằng thuật toán Bubble Sort.").c_str());
            success = true;
            break;
        case INSERTION_SORT:
            insertionSortSLL(singlyLinkedList, sortCriteria);
            printSuccess(("Đã sắp xếp danh sách liên kết đơn theo " + string(getCriteriaName(sortCriteria)) + " bằng thuật toán Insertion Sort.").c_str());
            success = true;
            break;
        case SELECTION_SORT:
            selectionSortSLL(singlyLinkedList, sortCriteria);
            printSuccess(("Đã sắp xếp danh sách liên kết đơn theo " + string(getCriteriaName(sortCriteria)) + " bằng thuật toán Selection Sort.").c_str());
            success = true;
            break;
        case MERGE_SORT:
            mergeSortSLL(singlyLinkedList, sortCriteria);
            printSuccess(("Đã sắp xếp danh sách liên kết đơn theo " + string(getCriteriaName(sortCriteria)) + " bằng thuật toán Merge Sort.").c_str());
            success = true;
            break;
        default:
            printError("Thuật toán sắp xếp không hợp lệ cho danh sách liên kết đơn. Chỉ hỗ trợ: Bubble, Insertion, Selection, Merge Sort.");
            break;
        }
        break;

    case CIRCULAR_LINKED_LIST:
        switch (sortAlgorithm)
        {
        case BUBBLE_SORT:
            bubbleSortCLL(circularLinkedList, sortCriteria);
            printSuccess(("Đã sắp xếp danh sách liên kết tròn theo " + string(getCriteriaName(sortCriteria)) + " bằng thuật toán Bubble Sort.").c_str());
            success = true;
            break;
        case INSERTION_SORT:
            insertionSortCLL(circularLinkedList, sortCriteria);
            printSuccess(("Đã sắp xếp danh sách liên kết tròn theo " + string(getCriteriaName(sortCriteria)) + " bằng thuật toán Insertion Sort.").c_str());
            success = true;
            break;
        case SELECTION_SORT:
            selectionSortCLL(circularLinkedList, sortCriteria);
            printSuccess(("Đã sắp xếp danh sách liên kết tròn theo " + string(getCriteriaName(sortCriteria)) + " bằng thuật toán Selection Sort.").c_str());
            success = true;
            break;
        case MERGE_SORT:
            mergeSortCLL(circularLinkedList, sortCriteria);
            printSuccess(("Đã sắp xếp danh sách liên kết tròn theo " + string(getCriteriaName(sortCriteria)) + " bằng thuật toán Merge Sort.").c_str());
            success = true;
            break;
        default:
            printError("Thuật toán sắp xếp không hợp lệ cho danh sách liên kết tròn. Chỉ hỗ trợ: Bubble, Insertion, Selection, Merge Sort.");
            break;
        }
        break;

    case DOUBLY_LINKED_LIST:
        switch (sortAlgorithm)
        {
        case BUBBLE_SORT:
            bubbleSortDLL(doublyLinkedListHead, doublyLinkedListTail, sortCriteria);
            printSuccess(("Đã sắp xếp danh sách liên kết đôi theo " + string(getCriteriaName(sortCriteria)) + " bằng thuật toán Bubble Sort.").c_str());
            success = true;
            break;
        case INSERTION_SORT:
            insertionSortDLL(doublyLinkedListHead, doublyLinkedListTail, sortCriteria);
            printSuccess(("Đã sắp xếp danh sách liên kết đôi theo " + string(getCriteriaName(sortCriteria)) + " bằng thuật toán Insertion Sort.").c_str());
            success = true;
            break;
        case SELECTION_SORT:
            selectionSortDLL(doublyLinkedListHead, doublyLinkedListTail, sortCriteria);
            printSuccess(("Đã sắp xếp danh sách liên kết đôi theo " + string(getCriteriaName(sortCriteria)) + " bằng thuật toán Selection Sort.").c_str());
            success = true;
            break;
        case QUICK_SORT:
            quickSortDLL(doublyLinkedListHead, doublyLinkedListTail, sortCriteria);
            printSuccess(("Đã sắp xếp danh sách liên kết đôi theo " + string(getCriteriaName(sortCriteria)) + " bằng thuật toán Quick Sort.").c_str());
            success = true;
            break;
        case HEAP_SORT:
            heapSortDLL(doublyLinkedListHead, doublyLinkedListTail, sortCriteria);
            printSuccess(("Đã sắp xếp danh sách liên kết đôi theo " + string(getCriteriaName(sortCriteria)) + " bằng thuật toán Heap Sort.").c_str());
            success = true;
            break;
        case MERGE_SORT:
            mergeSortDLL(&doublyLinkedListHead, sortCriteria);
            printSuccess(("Đã sắp xếp danh sách liên kết đôi theo " + string(getCriteriaName(sortCriteria)) + " bằng thuật toán Merge Sort.").c_str());
            success = true;
            break;
        default:
            printError("Thuật toán sắp xếp không hợp lệ cho danh sách liên kết đôi.");
            break;
        }
        break;

    default:
        printWarning("Chức năng sắp xếp chưa được hiện thực cho cấu trúc dữ liệu này.");
        break;
    }

    return success;
}

// Hàm xử lý nhập dữ liệu từ file CSV
bool handleInputFromCSV(const char *filePath,
                        int dataStructureType,
                        ArrayStudentList &arrayList,
                        NodeSLL *&singlyLinkedList,
                        NodeSLL *&circularLinkedList,
                        NodeDLL *&doublyLinkedListHead,
                        NodeDLL *&doublyLinkedListTail,
                        NodeBST *&binarySearchTree)
{
    cout << "Đang thử đọc từ file: " << filePath << endl;
    if (readFromCSVFile(filePath, arrayList))
    {
        printSuccess("Đã đọc dữ liệu từ file CSV thành công.");

        // Chuyển dữ liệu từ arrayList sang cấu trúc dữ liệu đã chọn
        if (dataStructureType != ARRAY_LIST)
        {
            for (int i = 0; i < arrayList.count; i++)
            {
                addStudentToDataStructure(arrayList.students[i], dataStructureType,
                                          arrayList, singlyLinkedList, circularLinkedList,
                                          doublyLinkedListHead, doublyLinkedListTail, binarySearchTree);
            }
        }
        return true;
    }
    else
    {
        string errorMsg = "Không thể đọc dữ liệu từ file CSV: " + string(filePath);
        printError(errorMsg.c_str());
        return false;
    }
}

// Hàm nhập mã sinh viên từ bàn phím
bool inputStudentID(char *studentID)
{
    string tempInput;
    bool isValid;

    do
    {
        cout << "Nhập mã sinh viên (nhập 00 để hủy): ";
        getline(cin, tempInput);
        tempInput = trim(tempInput); // Trim input

        // Kiểm tra hủy bỏ
        if (tempInput == "00")
        {
            if (confirmCancel())
            {
                studentID[0] = '\0'; // Đánh dấu là đã hủy bỏ
                return false;
            }
            continue;
        }

        isValid = validateAndShowStudentID(tempInput);
        if (isValid)
        {
            strcpy(studentID, tempInput.c_str());
        }
    } while (!isValid);

    return true;
}

// Hàm nhập thông tin sinh viên từ bàn phím
bool inputStudent(Student &student)
{

    string tempInput;
    bool isValid;

    // Nhập mã sinh viên (chỉ nhập nếu chưa có)
    if (student.studentID[0] == '\0' || strlen(student.studentID) == 0)
    {
        do
        {
            cout << "Nhập mã sinh viên: ";
            getline(cin, tempInput);
            tempInput = trim(tempInput); // Trim input

            // Kiểm tra hủy bỏ
            if (tempInput == "00")
            {
                if (confirmCancel())
                {
                    student.studentID[0] = '\0'; // Đánh dấu là đã hủy bỏ
                    return false;
                }
                continue;
            }

            isValid = validateAndShowStudentID(tempInput);
            if (isValid)
            {
                strcpy(student.studentID, tempInput.c_str());
            }
        } while (!isValid);
    }

    // Nhập họ và tên đệm
    do
    {
        cout << "Nhập họ và tên đệm: ";
        getline(cin, tempInput);
        tempInput = trim(tempInput); // Trim input

        // Kiểm tra hủy bỏ
        if (tempInput == "00")
        {
            if (confirmCancel())
            {
                student.studentID[0] = '\0'; // Đánh dấu là đã hủy bỏ
                return false;
            }
            continue;
        }

        isValid = validateAndShowName(tempInput);
        if (isValid)
        {
            strcpy(student.firstName, tempInput.c_str());
        }
    } while (!isValid);

    // Nhập tên
    do
    {
        cout << "Nhập tên: ";
        getline(cin, tempInput);
        tempInput = trim(tempInput); // Trim input

        // Kiểm tra hủy bỏ
        if (tempInput == "00")
        {
            if (confirmCancel())
            {
                student.studentID[0] = '\0'; // Đánh dấu là đã hủy bỏ
                return false;
            }
            continue;
        }

        isValid = validateAndShowName(tempInput);
        if (isValid)
        {
            strcpy(student.lastName, tempInput.c_str());
        }
    } while (!isValid);

    // Nhập lớp
    do
    {
        cout << "Nhập lớp: ";
        getline(cin, tempInput);
        tempInput = trim(tempInput); // Trim input

        // Kiểm tra hủy bỏ
        if (tempInput == "00")
        {
            if (confirmCancel())
            {
                student.studentID[0] = '\0'; // Đánh dấu là đã hủy bỏ
                return false;
            }
            continue;
        }

        isValid = validateAndShowClassName(tempInput);
        if (isValid)
        {
            strcpy(student.studentClass, tempInput.c_str());
        }
    } while (!isValid);

    // Nhập điểm số
    float score;
    string scoreInput;
    do
    {
        cout << "Nhập điểm (0-10): ";
        cin >> scoreInput;

        // Kiểm tra hủy bỏ (phân biệt với giá trị điểm 0)
        if (scoreInput == "00")
        {
            if (confirmCancel())
            {
                student.studentID[0] = '\0'; // Đánh dấu là đã hủy bỏ
                return false;
            }
            continue;
        }

        // Chuyển đổi chuỗi thành số float
        try
        {
            score = stof(scoreInput);
            isValid = validateAndShowScore(score);
            if (isValid)
            {
                student.score = score;
            }
        }
        catch (const exception &e)
        {
            printError("Điểm phải là một số thực.");
            isValid = false;
        }
    } while (!isValid);

    // Clear input buffer for next input
    clearInputBuffer();

    cout << "\n"
         << GREEN << "✓ Đã nhập thông tin sinh viên thành công!" << RESET << endl;
    displayStudentDetailed(student);

    return true;
}

// Hàm để khởi tạo tất cả các cấu trúc dữ liệu
void initAllDataStructures(ArrayStudentList &arrayList,
                           NodeSLL *&singlyLinkedList,
                           NodeSLL *&circularLinkedList,
                           NodeDLL *&doublyLinkedListHead,
                           NodeDLL *&doublyLinkedListTail,
                           NodeBST *&binarySearchTree)
{
    initArrayList(arrayList);
    initSLL(singlyLinkedList);
    initCLL(circularLinkedList);
    initDLL(doublyLinkedListHead, doublyLinkedListTail);
    initBST(binarySearchTree);
}

// Hàm lấy thông tin sinh viên từ cấu trúc dữ liệu
bool getStudentFromDataStructure(const char *studentID, int dataStructureType,
                                 const ArrayStudentList &arrayList,
                                 NodeSLL *singlyLinkedList,
                                 NodeSLL *circularLinkedList,
                                 NodeDLL *doublyLinkedListHead,
                                 Student &outStudent)
{
    switch (dataStructureType)
    {
    case ARRAY_LIST:
    {
        int index = searchInArrayList(arrayList, studentID);
        if (index != -1)
        {
            outStudent = arrayList.students[index];
            return true;
        }
    }
    break;
    case SINGLY_LINKED_LIST:
    {
        NodeSLL *node = searchInSLL(singlyLinkedList, studentID);
        if (node != NULL)
        {
            outStudent = node->info;
            return true;
        }
    }
    break;
    case CIRCULAR_LINKED_LIST:
    {
        NodeSLL *node = searchInCLL(circularLinkedList, studentID);
        if (node != NULL)
        {
            outStudent = node->info;
            return true;
        }
    }
    break;
    case DOUBLY_LINKED_LIST:
    {
        NodeDLL *node = searchInDLL(doublyLinkedListHead, studentID);
        if (node != NULL)
        {
            outStudent = node->info;
            return true;
        }
    }
    break;
    default:
        return false;
    }
    return false;
}

// Hàm nhập thông tin sinh viên từ bàn phím cho việc cập nhật
bool inputStudentForUpdate(Student &student)
{
    string tempInput;
    bool isValid;

    clearScreen();
    printHeader("CẬP NHẬT THÔNG TIN SINH VIÊN");
    printInfo("Thông tin hiện tại của sinh viên:");
    displayStudentDetailed(student);

    cout << "\n"
         << YELLOW << "Hướng dẫn:" << RESET << endl;
    cout << "- Nhập thông tin mới để thay đổi" << endl;
    cout << "- Nhấn Enter để giữ nguyên thông tin cũ" << endl;
    cout << "- Nhập \"00\" để hủy bỏ" << endl;
    cout << "----------------------------------------" << endl;

    // Nhập họ và tên đệm
    cout << "Họ và tên đệm hiện tại: " << CYAN << student.firstName << RESET << endl;
    cout << "Nhập họ và tên đệm mới (Enter để giữ nguyên): ";
    getline(cin, tempInput);
    tempInput = trim(tempInput);

    // Kiểm tra hủy bỏ
    if (tempInput == "00")
    {
        if (confirmCancel())
        {
            return false;
        }
    }
    else if (!tempInput.empty())
    {
        isValid = validateAndShowName(tempInput);
        if (isValid)
        {
            strcpy(student.firstName, tempInput.c_str());
        }
        else
        {
            printError("Họ và tên đệm không hợp lệ. Giữ nguyên giá trị cũ.");
        }
    }

    // Nhập tên
    cout << "\nTên hiện tại: " << CYAN << student.lastName << RESET << endl;
    cout << "Nhập tên mới (Enter để giữ nguyên): ";
    getline(cin, tempInput);
    tempInput = trim(tempInput);

    // Kiểm tra hủy bỏ
    if (tempInput == "00")
    {
        if (confirmCancel())
        {
            return false;
        }
    }
    else if (!tempInput.empty())
    {
        isValid = validateAndShowName(tempInput);
        if (isValid)
        {
            strcpy(student.lastName, tempInput.c_str());
        }
        else
        {
            printError("Tên không hợp lệ. Giữ nguyên giá trị cũ.");
        }
    }

    // Nhập lớp
    cout << "\nLớp hiện tại: " << CYAN << student.studentClass << RESET << endl;
    cout << "Nhập lớp mới (Enter để giữ nguyên): ";
    getline(cin, tempInput);
    tempInput = trim(tempInput);

    // Kiểm tra hủy bỏ
    if (tempInput == "00")
    {
        if (confirmCancel())
        {
            return false;
        }
    }
    else if (!tempInput.empty())
    {
        isValid = validateAndShowClassName(tempInput);
        if (isValid)
        {
            strcpy(student.studentClass, tempInput.c_str());
        }
        else
        {
            printError("Tên lớp không hợp lệ. Giữ nguyên giá trị cũ.");
        }
    }

    // Nhập điểm số
    cout << "\nĐiểm hiện tại: " << CYAN << student.score << RESET << endl;
    cout << "Nhập điểm mới (0-10, Enter để giữ nguyên): ";
    getline(cin, tempInput);
    tempInput = trim(tempInput);

    // Kiểm tra hủy bỏ
    if (tempInput == "00")
    {
        if (confirmCancel())
        {
            return false;
        }
    }
    else if (!tempInput.empty())
    {
        try
        {
            float score = stof(tempInput);
            isValid = validateAndShowScore(score);
            if (isValid)
            {
                student.score = score;
            }
            else
            {
                printError("Điểm không hợp lệ. Giữ nguyên giá trị cũ.");
            }
        }
        catch (const exception &e)
        {
            printError("Điểm phải là một số thực. Giữ nguyên giá trị cũ.");
        }
    }

    cout << "\n"
         << GREEN << "✓ Thông tin sinh viên sau khi cập nhật:" << RESET << endl;
    displayStudentDetailed(student);

    return true;
}

// Hàm xóa node trong BST theo key (điểm số)
bool deleteNodeFromBSTByKey(NodeBST *&binarySearchTree)
{
    // Kiểm tra BST có rỗng không
    if (binarySearchTree == NULL)
    {
        printError("Cây BST rỗng! Không có node nào để xóa.");
        return false;
    }

    float key;
    cout << YELLOW << "Nhập điểm số của node cần xóa: " << RESET;

    // Kiểm tra input hợp lệ
    while (!(cin >> key) || key < 0.0 || key > 10.0)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        printError("Điểm số không hợp lệ! Vui lòng nhập lại (0.0 - 10.0): ");
    }
    cin.ignore(); // Xóa ký tự newline còn lại

    // Kiểm tra xem node có tồn tại không
    NodeBST *foundNode = searchInBST(binarySearchTree, key);
    if (foundNode == NULL)
    {
        cout << YELLOW << "⚠️  Không tìm thấy node có điểm số " << key << " trong cây BST!" << RESET << endl;
        return false;
    }

    // Hiển thị thông tin node sẽ bị xóa
    cout << CYAN << "\nThông tin node sẽ bị xóa:" << RESET << endl;
    displayBSTNode(foundNode);

    // Xác nhận xóa
    char confirm;
    cout << YELLOW << "\nBạn có chắc chắn muốn xóa node này? (y/n): " << RESET;
    cin >> confirm;
    cin.ignore();

    if (confirm == 'y' || confirm == 'Y')
    {
        deleteFromBST(binarySearchTree, key);
        return true;
    }
    else
    {
        printInfo("Đã hủy thao tác xóa.");
        return false;
    }
}

// ========== Các hàm helper cho BST ==========

// Hàm thêm sinh viên vào BST
void addStudentToBST(const Student &student, NodeBST *&binarySearchTree)
{
    insertToBST(binarySearchTree, student);
}

// Hàm xóa sinh viên khỏi BST theo mã sinh viên
void deleteStudentFromBST(const char *studentID, NodeBST *&binarySearchTree)
{
    clearScreen();
    printHeader("XÓA SINH VIÊN KHỎI CÂY BST");

    // Kiểm tra BST có rỗng không
    if (binarySearchTree == NULL)
    {
        printError("Cây BST rỗng! Không có sinh viên nào để xóa.");
        return;
    }

    // Tìm sinh viên trong BST
    Student foundStudent;
    if (!getStudentFromBST(studentID, binarySearchTree, foundStudent))
    {
        printError(("Không tìm thấy sinh viên có mã " + string(studentID) + " trong cây BST.").c_str());
        return;
    }

    // Hiển thị thông tin sinh viên sẽ bị xóa
    cout << CYAN << "\nThông tin sinh viên sẽ bị xóa:" << RESET << endl;
    displayStudentDetailed(foundStudent);

    // Xác nhận xóa
    char confirm;
    cout << YELLOW << "\nBạn có chắc chắn muốn xóa sinh viên này? (y/n): " << RESET;
    cin >> confirm;
    clearInputBuffer();

    if (confirm == 'y' || confirm == 'Y')
    {
        // Tìm node chứa sinh viên này
        NodeBST *nodeToUpdate = searchInBST(binarySearchTree, foundStudent.score);
        if (nodeToUpdate != NULL && nodeToUpdate->count > 0)
        {
            // Tìm vị trí sinh viên trong mảng students của node
            int indexToRemove = -1;
            for (int i = 0; i < nodeToUpdate->count; i++)
            {
                if (strcmp(nodeToUpdate->students[i].studentID, studentID) == 0)
                {
                    indexToRemove = i;
                    break;
                }
            }

            if (indexToRemove != -1)
            {
                // Xóa sinh viên khỏi mảng bằng cách dịch chuyển các phần tử
                for (int i = indexToRemove; i < nodeToUpdate->count - 1; i++)
                {
                    nodeToUpdate->students[i] = nodeToUpdate->students[i + 1];
                }
                nodeToUpdate->count--;

                // Nếu node không còn sinh viên nào, xóa node khỏi BST
                if (nodeToUpdate->count == 0)
                {
                    deleteFromBST(binarySearchTree, foundStudent.score);
                    printSuccess("Đã xóa sinh viên và node khỏi cây BST thành công.");
                }
                else
                {
                    printSuccess("Đã xóa sinh viên khỏi cây BST thành công.");
                }
            }
        }
    }
    else
    {
        printInfo("Đã hủy thao tác xóa.");
    }
}

// Hàm lấy thông tin sinh viên từ BST theo mã sinh viên
bool getStudentFromBST(const char *studentID, NodeBST *binarySearchTree, Student &foundStudent)
{
    if (binarySearchTree == NULL)
    {
        return false;
    }

    // Duyệt cây BST để tìm sinh viên
    if (getStudentFromBST(studentID, binarySearchTree->left, foundStudent))
    {
        return true;
    }

    // Kiểm tra node hiện tại
    for (int i = 0; i < binarySearchTree->count; i++)
    {
        if (strcmp(binarySearchTree->students[i].studentID, studentID) == 0)
        {
            foundStudent = binarySearchTree->students[i];
            return true;
        }
    }

    // Duyệt cây con phải
    return getStudentFromBST(studentID, binarySearchTree->right, foundStudent);
}

// Hàm cập nhật sinh viên trong BST
void updateStudentInBST(const Student &student, NodeBST *&binarySearchTree)
{
    // Tìm sinh viên cũ
    Student oldStudent;
    if (!getStudentFromBST(student.studentID, binarySearchTree, oldStudent))
    {
        printError("Không tìm thấy sinh viên để cập nhật trong cây BST.");
        return;
    }

    // Nếu điểm số thay đổi, cần xóa sinh viên khỏi vị trí cũ và thêm vào vị trí mới
    if (oldStudent.score != student.score)
    {
        // Xóa sinh viên khỏi vị trí cũ
        NodeBST *oldNode = searchInBST(binarySearchTree, oldStudent.score);
        if (oldNode != NULL)
        {
            // Tìm vị trí sinh viên trong mảng students
            int indexToRemove = -1;
            for (int i = 0; i < oldNode->count; i++)
            {
                if (strcmp(oldNode->students[i].studentID, student.studentID) == 0)
                {
                    indexToRemove = i;
                    break;
                }
            }

            if (indexToRemove != -1)
            {
                // Xóa sinh viên khỏi mảng
                for (int i = indexToRemove; i < oldNode->count - 1; i++)
                {
                    oldNode->students[i] = oldNode->students[i + 1];
                }
                oldNode->count--;

                // Nếu node không còn sinh viên nào, xóa node
                if (oldNode->count == 0)
                {
                    deleteFromBST(binarySearchTree, oldStudent.score);
                }
            }
        }

        // Thêm sinh viên với điểm số mới
        insertToBST(binarySearchTree, student);
        printSuccess("Đã cập nhật sinh viên trong cây BST thành công.");
    }
    else
    {
        // Chỉ cập nhật thông tin khác (không thay đổi điểm số)
        NodeBST *node = searchInBST(binarySearchTree, student.score);
        if (node != NULL)
        {
            for (int i = 0; i < node->count; i++)
            {
                if (strcmp(node->students[i].studentID, student.studentID) == 0)
                {
                    node->students[i] = student;
                    printSuccess("Đã cập nhật thông tin sinh viên trong cây BST thành công.");
                    return;
                }
            }
        }
        printError("Không thể cập nhật sinh viên trong cây BST.");
    }
}



// Hàm hiển thị cây BST
void displayBST(NodeBST *binarySearchTree)
{
    clearScreen();
    printHeader("HIỂN THỊ CÂY TÌM KIẾM NHỊ PHÂN");

    if (binarySearchTree == NULL)
    {
        printWarning("Cây BST rỗng!");
        return;
    }

    cout << BOLD << CYAN << "\n=== CÂY TÌM KIẾM NHỊ PHÂN ===" << RESET << endl;

    // Sử dụng các hàm duyệt có đo thời gian
    inorderTraversalBSTWithTimer(binarySearchTree);
    preorderTraversalBSTWithTimer(binarySearchTree);
    postorderTraversalBSTWithTimer(binarySearchTree);
}

// ========== Các hàm chuyển đổi dữ liệu giữa các cấu trúc ==========

// Hàm chuyển đổi dữ liệu từ các cấu trúc khác sang BST
void convertDataStructureToBST(int sourceDataStructureType,
                               const ArrayStudentList &arrayList,
                               NodeSLL *singlyLinkedList,
                               NodeSLL *circularLinkedList,
                               NodeDLL *doublyLinkedListHead,
                               NodeBST *&binarySearchTree)
{
    // Khởi tạo BST rỗng
    initBST(binarySearchTree);

    switch (sourceDataStructureType)
    {
    case ARRAY_LIST:
        // Chuyển đổi từ Array List sang BST
        for (int i = 0; i < arrayList.count; i++)
        {
            insertToBST(binarySearchTree, arrayList.students[i]);
        }
        printSuccess(("Đã chuyển " + to_string(arrayList.count) + " sinh viên từ danh sách mảng sang BST.").c_str());
        break;

    case SINGLY_LINKED_LIST:
        // Chuyển đổi từ Singly Linked List sang BST
        {
            NodeSLL *current = singlyLinkedList;
            int count = 0;
            while (current != NULL)
            {
                insertToBST(binarySearchTree, current->info);
                current = current->next;
                count++;
            }
            printSuccess(("Đã chuyển " + to_string(count) + " sinh viên từ danh sách liên kết đơn sang BST.").c_str());
        }
        break;

    case CIRCULAR_LINKED_LIST:
        // Chuyển đổi từ Circular Linked List sang BST
        {
            if (circularLinkedList != NULL)
            {
                NodeSLL *current = circularLinkedList;
                int count = 0;
                do
                {
                    insertToBST(binarySearchTree, current->info);
                    current = current->next;
                    count++;
                } while (current != circularLinkedList);
                printSuccess(("Đã chuyển " + to_string(count) + " sinh viên từ danh sách liên kết vòng sang BST.").c_str());
            }
        }
        break;

    case DOUBLY_LINKED_LIST:
        // Chuyển đổi từ Doubly Linked List sang BST
        {
            NodeDLL *current = doublyLinkedListHead;
            int count = 0;
            while (current != NULL)
            {
                insertToBST(binarySearchTree, current->info);
                current = current->next;
                count++;
            }
            printSuccess(("Đã chuyển " + to_string(count) + " sinh viên từ danh sách liên kết đôi sang BST.").c_str());
        }
        break;

    default:
        printError("Cấu trúc dữ liệu nguồn không hợp lệ.");
        break;
    }
}

// Hàm helper để duyệt BST và thêm sinh viên vào Array List
void traverseBSTAndAddToArray(NodeBST *node, ArrayStudentList &arrayList)
{
    if (node == NULL)
        return;

    // Duyệt cây con trái
    traverseBSTAndAddToArray(node->left, arrayList);

    // Thêm tất cả sinh viên trong node hiện tại vào Array List
    for (int i = 0; i < node->count; i++)
    {
        if (arrayList.count < MAX_STUDENTS)
        {
            arrayList.students[arrayList.count] = node->students[i];
            arrayList.count++;
        }
        else
        {
            printWarning("Danh sách mảng đã đầy! Không thể chuyển thêm sinh viên.");
            return;
        }
    }

    // Duyệt cây con phải
    traverseBSTAndAddToArray(node->right, arrayList);
}

// Hàm chuyển đổi dữ liệu từ BST sang Array List
void convertBSTToArrayList(NodeBST *binarySearchTree, ArrayStudentList &arrayList)
{
    // Khởi tạo Array List rỗng
    initArrayList(arrayList);

    if (binarySearchTree == NULL)
    {
        printInfo("BST rỗng, không có dữ liệu để chuyển đổi.");
        return;
    }

    // Duyệt BST và thêm vào Array List
    traverseBSTAndAddToArray(binarySearchTree, arrayList);

    printSuccess(("Đã chuyển " + to_string(arrayList.count) + " sinh viên từ BST sang danh sách mảng.").c_str());
}

// Hàm chọn cấu trúc dữ liệu với xử lý chuyển đổi BST
int selectDataStructureWithBSTHandling(int currentDataStructureType,
                                       ArrayStudentList &arrayList,
                                       NodeSLL *singlyLinkedList,
                                       NodeSLL *circularLinkedList,
                                       NodeDLL *doublyLinkedListHead,
                                       NodeBST *&binarySearchTree)
{
    int choice = selectDataStructure();

    // Nếu chọn BST (choice == 5)
    if (choice == BINARY_SEARCH_TREE)
    {
        // Kiểm tra xem có dữ liệu trong cấu trúc hiện tại không
        bool hasData = !isDataStructureEmpty(currentDataStructureType, arrayList,
                                             singlyLinkedList, circularLinkedList,
                                             doublyLinkedListHead, binarySearchTree);

        if (hasData && currentDataStructureType != BINARY_SEARCH_TREE)
        {
            printInfo("Đang chuyển đổi dữ liệu từ cấu trúc hiện tại sang BST...");

            // Chuyển đổi dữ liệu từ cấu trúc hiện tại sang BST
            convertDataStructureToBST(currentDataStructureType, arrayList,
                                      singlyLinkedList, circularLinkedList,
                                      doublyLinkedListHead, binarySearchTree);

            printInfo("Chuyển sang chế độ BST. Bạn có thể sử dụng các chức năng BST chuyên biệt.");
            cout << "\nNhấn Enter để tiếp tục...";
            cin.get();
        }
        else if (!hasData)
        {
            printInfo("Chuyển sang chế độ BST với dữ liệu rỗng.");
            cout << "\nNhấn Enter để tiếp tục...";
            cin.get();
        }

        // Gọi hàm thực hiện các thao tác BST và lấy loại cấu trúc dữ liệu mới
        // Forward declaration cần thiết để gọi từ operations.cpp
        extern int performBSTOperations(NodeBST * &binarySearchTree, ArrayStudentList & arrayList);
        return performBSTOperations(binarySearchTree, arrayList);
    }

    return choice;
}

// ========== Các hàm mới: Xóa toàn bộ và lưu file ==========

// Hàm xóa toàn bộ dữ liệu trong cấu trúc dữ liệu hiện tại
bool clearAllData(int dataStructureType,
                  ArrayStudentList &arrayList,
                  NodeSLL *&singlyLinkedList,
                  NodeSLL *&circularLinkedList,
                  NodeDLL *&doublyLinkedListHead,
                  NodeDLL *&doublyLinkedListTail,
                  NodeBST *&binarySearchTree)
{
    clearScreen();
    printHeader("XÓA TOÀN BỘ DANH SÁCH SINH VIÊN");

    // Kiểm tra xem có dữ liệu để xóa không
    bool hasData = !isDataStructureEmpty(dataStructureType, arrayList, singlyLinkedList,
                                         circularLinkedList, doublyLinkedListHead, binarySearchTree);

    if (!hasData)
    {
        printWarning("Danh sách sinh viên đang rỗng. Không có gì để xóa.");
        return false;
    }

    // Hiển thị cảnh báo
    cout << RED << "⚠ CẢNH BÁO: Bạn sắp xóa toàn bộ danh sách sinh viên!" << RESET << endl;
    cout << "Thao tác này không thể hoàn tác." << endl;
    cout << "Cấu trúc dữ liệu hiện tại: " << CYAN << getDataStructureName(dataStructureType) << RESET << endl;

    // Xin xác nhận từ người dùng
    char confirm;
    cout << "\nBạn có chắc chắn muốn xóa toàn bộ danh sách? (y/N): ";
    cin >> confirm;
    clearInputBuffer();

    if (confirm != 'y' && confirm != 'Y')
    {
        printInfo("Đã hủy thao tác xóa toàn bộ danh sách.");
        return false;
    }

    // Xác nhận lần 2
    cout << RED << "Xác nhận lần cuối - Nhập 'XOA' để tiếp tục: " << RESET;
    string finalConfirm;
    getline(cin, finalConfirm);

    if (finalConfirm != "XOA")
    {
        printInfo("Đã hủy thao tác xóa toàn bộ danh sách.");
        return false;
    }

    // Thực hiện xóa dữ liệu
    bool success = false;

    switch (dataStructureType)
    {
    case ARRAY_LIST:
        initArrayList(arrayList);
        success = true;
        break;

    case SINGLY_LINKED_LIST:
        if (singlyLinkedList != NULL)
        {
            freeSLL(singlyLinkedList);
            singlyLinkedList = NULL;
            success = true;
        }
        break;

    case CIRCULAR_LINKED_LIST:
        if (circularLinkedList != NULL)
        {
            freeCLL(circularLinkedList);
            circularLinkedList = NULL;
            success = true;
        }
        break;

    case DOUBLY_LINKED_LIST:
        if (doublyLinkedListHead != NULL)
        {
            freeDLL(doublyLinkedListHead, doublyLinkedListTail);
            doublyLinkedListHead = NULL;
            doublyLinkedListTail = NULL;
            success = true;
        }
        break;

    case BINARY_SEARCH_TREE:
        if (binarySearchTree != NULL)
        {
            freeBST(binarySearchTree);
            binarySearchTree = NULL;
            success = true;
        }
        break;

    default:
        printError("Cấu trúc dữ liệu không hợp lệ.");
        return false;
    }

    if (success)
    {
        printSuccess("Đã xóa toàn bộ danh sách sinh viên thành công!");
    }
    else
    {
        printError("Có lỗi xảy ra khi xóa danh sách.");
    }

    return success;
}

// Hàm lưu danh sách sinh viên ra file CSV
bool saveToCSVFile(const char *filename, int dataStructureType,
                   const ArrayStudentList &arrayList,
                   NodeSLL *singlyLinkedList,
                   NodeSLL *circularLinkedList,
                   NodeDLL *doublyLinkedListHead,
                   NodeBST *binarySearchTree)
{
    // Kiểm tra xem có dữ liệu để lưu không
    bool hasData = !isDataStructureEmpty(dataStructureType, arrayList, singlyLinkedList,
                                         circularLinkedList, doublyLinkedListHead, binarySearchTree);

    if (!hasData)
    {
        printWarning("Danh sách sinh viên đang rỗng. Không có gì để lưu.");
        return false;
    }

    // Tạo một ArrayStudentList tạm để chuyển đổi dữ liệu
    ArrayStudentList tempList;
    initArrayList(tempList);

    // Chuyển đổi dữ liệu từ cấu trúc hiện tại sang ArrayStudentList
    switch (dataStructureType)
    {
    case ARRAY_LIST:
        // Sao chép trực tiếp
        tempList = arrayList;
        break;

    case SINGLY_LINKED_LIST:
    {
        NodeSLL *current = singlyLinkedList;
        while (current != NULL && tempList.count < MAX_STUDENTS)
        {
            tempList.students[tempList.count] = current->info;
            tempList.count++;
            current = current->next;
        }
    }
    break;

    case CIRCULAR_LINKED_LIST:
    {
        if (circularLinkedList != NULL)
        {
            NodeSLL *current = circularLinkedList;
            do
            {
                if (tempList.count < MAX_STUDENTS)
                {
                    tempList.students[tempList.count] = current->info;
                    tempList.count++;
                    current = current->next;
                }
                else
                {
                    break;
                }
            } while (current != circularLinkedList);
        }
    }
    break;

    case DOUBLY_LINKED_LIST:
    {
        NodeDLL *current = doublyLinkedListHead;
        while (current != NULL && tempList.count < MAX_STUDENTS)
        {
            tempList.students[tempList.count] = current->info;
            tempList.count++;
            current = current->next;
        }
    }
    break;

    case BINARY_SEARCH_TREE:
        // Sử dụng hàm có sẵn để chuyển đổi BST sang ArrayList
        traverseBSTAndAddToArray(binarySearchTree, tempList);
        break;

    default:
        printError("Cấu trúc dữ liệu không hợp lệ.");
        return false;
    }

    // Ghi dữ liệu ra file CSV
    if (writeToCSVFile(filename, tempList))
    {
        printSuccess(("Đã lưu " + to_string(tempList.count) + " sinh viên ra file: " + string(filename)).c_str());
        return true;
    }
    else
    {
        printError(("Không thể lưu dữ liệu ra file: " + string(filename)).c_str());
        return false;
    }
}

// ========== Các hàm helper cho thống kê theo lớp ==========

// Hàm lấy danh sách các lớp duy nhất từ Array List
int getUniqueClassesArray(const ArrayStudentList &arrayList, char classes[][MAX_CLASS_LENGTH])
{
    int classCount = 0;
    for (int i = 0; i < arrayList.count; i++)
    {
        bool found = false;
        // Kiểm tra xem lớp đã tồn tại trong danh sách chưa
        for (int j = 0; j < classCount; j++)
        {
            if (strcmp(classes[j], arrayList.students[i].studentClass) == 0)
            {
                found = true;
                break;
            }
        }
        // Nếu chưa tồn tại thì thêm vào danh sách
        if (!found)
        {
            strcpy(classes[classCount], arrayList.students[i].studentClass);
            classCount++;
        }
    }
    return classCount;
}

// Hàm lấy danh sách các lớp duy nhất từ Singly Linked List
int getUniqueClassesSLL(NodeSLL *singlyLinkedList, char classes[][MAX_CLASS_LENGTH])
{
    int classCount = 0;
    NodeSLL *current = singlyLinkedList;
    
    while (current != NULL)
    {
        bool found = false;
        // Kiểm tra xem lớp đã tồn tại trong danh sách chưa
        for (int j = 0; j < classCount; j++)
        {
            if (strcmp(classes[j], current->info.studentClass) == 0)
            {
                found = true;
                break;
            }
        }
        // Nếu chưa tồn tại thì thêm vào danh sách
        if (!found)
        {
            strcpy(classes[classCount], current->info.studentClass);
            classCount++;
        }
        current = current->next;
    }
    return classCount;
}

// Hàm lấy danh sách các lớp duy nhất từ Circular Linked List
int getUniqueClassesCLL(NodeSLL *circularLinkedList, char classes[][MAX_CLASS_LENGTH])
{
    if (circularLinkedList == NULL) return 0;
    
    int classCount = 0;
    NodeSLL *current = circularLinkedList;
    
    do
    {
        bool found = false;
        // Kiểm tra xem lớp đã tồn tại trong danh sách chưa
        for (int j = 0; j < classCount; j++)
        {
            if (strcmp(classes[j], current->info.studentClass) == 0)
            {
                found = true;
                break;
            }
        }
        // Nếu chưa tồn tại thì thêm vào danh sách
        if (!found)
        {
            strcpy(classes[classCount], current->info.studentClass);
            classCount++;
        }
        current = current->next;
    } while (current != circularLinkedList);
    
    return classCount;
}

// Hàm lấy danh sách các lớp duy nhất từ Doubly Linked List
int getUniqueClassesDLL(NodeDLL *doublyLinkedListHead, char classes[][MAX_CLASS_LENGTH])
{
    int classCount = 0;
    NodeDLL *current = doublyLinkedListHead;
    
    while (current != NULL)
    {
        bool found = false;
        // Kiểm tra xem lớp đã tồn tại trong danh sách chưa
        for (int j = 0; j < classCount; j++)
        {
            if (strcmp(classes[j], current->info.studentClass) == 0)
            {
                found = true;
                break;
            }
        }
        // Nếu chưa tồn tại thì thêm vào danh sách
        if (!found)
        {
            strcpy(classes[classCount], current->info.studentClass);
            classCount++;
        }
        current = current->next;
    }
    return classCount;
}

// Hàm tính toán thống kê cho một lớp từ Array List
void calculateClassStatisticsArray(const ArrayStudentList &arrayList, const char *className, ClassStatistics &stats)
{
    strcpy(stats.className, className);
    stats.totalStudents = 0;
    stats.highestScore = -1;
    stats.lowestScore = 11;
    float totalScore = 0;
    
    for (int i = 0; i < arrayList.count; i++)
    {
        if (strcmp(arrayList.students[i].studentClass, className) == 0)
        {
            stats.totalStudents++;
            totalScore += arrayList.students[i].score;
            
            if (arrayList.students[i].score > stats.highestScore)
                stats.highestScore = arrayList.students[i].score;
            if (arrayList.students[i].score < stats.lowestScore)
                stats.lowestScore = arrayList.students[i].score;
        }
    }
    
    stats.averageScore = (stats.totalStudents > 0) ? (totalScore / stats.totalStudents) : 0;
}

// Hàm tính toán thống kê cho một lớp từ Singly Linked List
void calculateClassStatisticsSLL(NodeSLL *singlyLinkedList, const char *className, ClassStatistics &stats)
{
    strcpy(stats.className, className);
    stats.totalStudents = 0;
    stats.highestScore = -1;
    stats.lowestScore = 11;
    float totalScore = 0;
    
    NodeSLL *current = singlyLinkedList;
    while (current != NULL)
    {
        if (strcmp(current->info.studentClass, className) == 0)
        {
            stats.totalStudents++;
            totalScore += current->info.score;
            
            if (current->info.score > stats.highestScore)
                stats.highestScore = current->info.score;
            if (current->info.score < stats.lowestScore)
                stats.lowestScore = current->info.score;
        }
        current = current->next;
    }
    
    stats.averageScore = (stats.totalStudents > 0) ? (totalScore / stats.totalStudents) : 0;
}

// Hàm tính toán thống kê cho một lớp từ Circular Linked List
void calculateClassStatisticsCLL(NodeSLL *circularLinkedList, const char *className, ClassStatistics &stats)
{
    strcpy(stats.className, className);
    stats.totalStudents = 0;
    stats.highestScore = -1;
    stats.lowestScore = 11;
    float totalScore = 0;
    
    if (circularLinkedList == NULL) 
    {
        stats.averageScore = 0;
        return;
    }
    
    NodeSLL *current = circularLinkedList;
    do
    {
        if (strcmp(current->info.studentClass, className) == 0)
        {
            stats.totalStudents++;
            totalScore += current->info.score;
            
            if (current->info.score > stats.highestScore)
                stats.highestScore = current->info.score;
            if (current->info.score < stats.lowestScore)
                stats.lowestScore = current->info.score;
        }
        current = current->next;
    } while (current != circularLinkedList);
    
    stats.averageScore = (stats.totalStudents > 0) ? (totalScore / stats.totalStudents) : 0;
}

// Hàm tính toán thống kê cho một lớp từ Doubly Linked List
void calculateClassStatisticsDLL(NodeDLL *doublyLinkedListHead, const char *className, ClassStatistics &stats)
{
    strcpy(stats.className, className);
    stats.totalStudents = 0;
    stats.highestScore = -1;
    stats.lowestScore = 11;
    float totalScore = 0;
    
    NodeDLL *current = doublyLinkedListHead;
    while (current != NULL)
    {
        if (strcmp(current->info.studentClass, className) == 0)
        {
            stats.totalStudents++;
            totalScore += current->info.score;
            
            if (current->info.score > stats.highestScore)
                stats.highestScore = current->info.score;
            if (current->info.score < stats.lowestScore)
                stats.lowestScore = current->info.score;
        }
        current = current->next;
    }
    
    stats.averageScore = (stats.totalStudents > 0) ? (totalScore / stats.totalStudents) : 0;
}

// Hàm hiển thị thống kê của một lớp
void displayClassStatistics(const ClassStatistics &stats)
{
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
    cout << "┃                                        THỐNG KÊ LỚP " << setw(15) << left << stats.className << "┃" << endl;
    cout << "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫" << endl;
    cout << "┃ Tổng số sinh viên:   " << setw(10) << stats.totalStudents << "                                                      ┃" << endl;
    cout << "┃ Điểm cao nhất:      " << setw(10) << fixed << setprecision(2) << stats.highestScore << "                                                      ┃" << endl;
    cout << "┃ Điểm thấp nhất:     " << setw(10) << fixed << setprecision(2) << stats.lowestScore << "                                                      ┃" << endl;
    cout << "┃ Điểm trung bình:    " << setw(10) << fixed << setprecision(2) << stats.averageScore << "                                                      ┃" << endl;
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
    cout << endl;
}

// Hàm hiển thị thống kê tất cả các lớp
void displayAllClassStatistics(int dataStructureType,
                               const ArrayStudentList &arrayList,
                               NodeSLL *singlyLinkedList,
                               NodeSLL *circularLinkedList,
                               NodeDLL *doublyLinkedListHead)
{
    char classes[MAX_STUDENTS][MAX_CLASS_LENGTH];
    int classCount = 0;
    
    // Lấy danh sách các lớp duy nhất theo cấu trúc dữ liệu
    switch (dataStructureType)
    {
    case ARRAY_LIST:
        classCount = getUniqueClassesArray(arrayList, classes);
        break;
    case SINGLY_LINKED_LIST:
        classCount = getUniqueClassesSLL(singlyLinkedList, classes);
        break;
    case CIRCULAR_LINKED_LIST:
        classCount = getUniqueClassesCLL(circularLinkedList, classes);
        break;
    case DOUBLY_LINKED_LIST:
        classCount = getUniqueClassesDLL(doublyLinkedListHead, classes);
        break;
    }
    
    if (classCount == 0)
    {
        printWarning("Không có lớp nào để thống kê!");
        return;
    }
    
    printHeader("THỐNG KÊ THEO LỚP");
    
    // Hiển thị thống kê cho từng lớp
    for (int i = 0; i < classCount; i++)
    {
        ClassStatistics stats;
        
        switch (dataStructureType)
        {
        case ARRAY_LIST:
            calculateClassStatisticsArray(arrayList, classes[i], stats);
            break;
        case SINGLY_LINKED_LIST:
            calculateClassStatisticsSLL(singlyLinkedList, classes[i], stats);
            break;
        case CIRCULAR_LINKED_LIST:
            calculateClassStatisticsCLL(circularLinkedList, classes[i], stats);
            break;
        case DOUBLY_LINKED_LIST:
            calculateClassStatisticsDLL(doublyLinkedListHead, classes[i], stats);
            break;
        }
        
        displayClassStatistics(stats);
    }
}
