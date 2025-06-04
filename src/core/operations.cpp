#include "../../include/core/operations.h"
#include "../../include/utils/validation.h"
#include "../../include/utils/common_utils.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

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
                     NodeDLL *doublyLinkedListHead)
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
    default:
        return false; // Mặc định là không tồn tại
    }
}

// Hàm kiểm tra trùng mã sinh viên và hiển thị thông báo lỗi
bool validateAndShowDuplicateStudentID(const string &studentID, int dataStructureType,
                                       const ArrayStudentList &arrayList,
                                       NodeSLL *singlyLinkedList,
                                       NodeSLL *circularLinkedList,
                                       NodeDLL *doublyLinkedListHead)
{
    if (isStudentExists(studentID.c_str(), dataStructureType, arrayList,
                        singlyLinkedList, circularLinkedList, doublyLinkedListHead))
    {
        printError(("Mã sinh viên " + studentID + " đã tồn tại!").c_str());
        return false;
    }
    return true;
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
        printWarning("Chức năng xóa chưa được hiện thực cho cây tìm kiếm nhị phân.");
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
            displayBSTTree(binarySearchTree);

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

// Hàm tìm kiếm sinh viên trong cấu trúc dữ liệu đã chọn
void searchStudentInDataStructure(const char *studentID, int dataStructureType,
                                  const ArrayStudentList &arrayList,
                                  NodeSLL *singlyLinkedList,
                                  NodeSLL *circularLinkedList,
                                  NodeDLL *doublyLinkedListHead)
{
    bool found = false;

    switch (dataStructureType)
    {
    case ARRAY_LIST:
    {
        int index = searchInArrayList(arrayList, studentID);
        if (index != -1)
        {
            printSuccess("Tìm thấy sinh viên trong danh sách mảng:");
            displayStudentDetailed(arrayList.students[index]);
            found = true;
        }
    }
    break;
    case SINGLY_LINKED_LIST:
    {
        NodeSLL *node = searchInSLL(singlyLinkedList, studentID);
        if (node != NULL)
        {
            printSuccess("Tìm thấy sinh viên trong danh sách liên kết đơn:");
            displayStudentDetailed(node->info);
            found = true;
        }
    }
    break;
    case CIRCULAR_LINKED_LIST:
    {
        NodeSLL *node = searchInCLL(circularLinkedList, studentID);
        if (node != NULL)
        {
            printSuccess("Tìm thấy sinh viên trong danh sách liên kết vòng:");
            displayStudentDetailed(node->info);
            found = true;
        }
    }
    break;
    case DOUBLY_LINKED_LIST:
    {
        NodeDLL *node = searchInDLL(doublyLinkedListHead, studentID);
        if (node != NULL)
        {
            printSuccess("Tìm thấy sinh viên trong danh sách liên kết đôi:");
            displayStudentDetailed(node->info);
            found = true;
        }
    }
    break;
    case BINARY_SEARCH_TREE:
        printWarning("Chức năng tìm kiếm theo mã sinh viên chưa được hiện thực cho cây tìm kiếm nhị phân.");
        return;
    default:
        printError("Cấu trúc dữ liệu không hợp lệ.");
        return;
    }

    if (!found)
    {
        printError(("Không tìm thấy sinh viên có mã: " + string(studentID)).c_str());
    }
}

// Hàm thực hiện thống kê sinh viên
void performStatistics(int dataStructureType, const ArrayStudentList &arrayList)
{
    if (dataStructureType != ARRAY_LIST)
    {
        printWarning("Chức năng thống kê chỉ được hiện thực cho danh sách mảng.");
        return;
    }

    if (arrayList.count == 0)
    {
        printWarning("Danh sách sinh viên rỗng. Không có thống kê.");
        return;
    }

    float highest = findHighestScore(arrayList);
    float lowest = findLowestScore(arrayList);
    float average = calculateAverageScore(arrayList);

    printHeader("THỐNG KÊ ĐIỂM SINH VIÊN");
    cout << "Số lượng sinh viên: " << arrayList.count << "\n";
    cout << GREEN << "Điểm cao nhất: " << highest << RESET << "\n";
    cout << RED << "Điểm thấp nhất: " << lowest << RESET << "\n";
    cout << BLUE << "Điểm trung bình: " << average << RESET << "\n";

    cout << CYAN << "\nSinh viên có điểm cao nhất:\n"
         << RESET;
    printDivider();
    for (int i = 0; i < arrayList.count; i++)
    {
        if (arrayList.students[i].score == highest)
        {
            displayStudent(arrayList.students[i]);
            printDivider();
        }
    }

    cout << CYAN << "\nSinh viên có điểm thấp nhất:\n"
         << RESET;
    printDivider();
    for (int i = 0; i < arrayList.count; i++)
    {
        if (arrayList.students[i].score == lowest)
        {
            displayStudent(arrayList.students[i]);
            printDivider();
        }
    }
}

// Hàm sắp xếp danh sách sinh viên theo điểm số sử dụng thuật toán được chọn
bool sortStudentList(int dataStructureType, int sortAlgorithm,
                     ArrayStudentList &arrayList,
                     NodeDLL *&doublyLinkedListHead)
{
    bool success = false;

    switch (dataStructureType)
    {
    case ARRAY_LIST:
        switch (sortAlgorithm)
        {
        case BUBBLE_SORT:
            bubbleSortArrayList(arrayList);
            printSuccess("Đã sắp xếp danh sách mảng bằng thuật toán Bubble Sort.");
            success = true;
            break;
        case INSERTION_SORT:
            insertionSortArrayList(arrayList);
            printSuccess("Đã sắp xếp danh sách mảng bằng thuật toán Insertion Sort.");
            success = true;
            break;
        case SELECTION_SORT:
            selectionSortArrayList(arrayList);
            printSuccess("Đã sắp xếp danh sách mảng bằng thuật toán Selection Sort.");
            success = true;
            break;
        case QUICK_SORT:
            quickSortArrayList(arrayList, 0, arrayList.count - 1);
            printSuccess("Đã sắp xếp danh sách mảng bằng thuật toán Quick Sort.");
            success = true;
            break;
        default:
            printError("Thuật toán sắp xếp không hợp lệ cho danh sách mảng.");
            break;
        }
        break;
    case DOUBLY_LINKED_LIST:
        if (sortAlgorithm == MERGE_SORT)
        {
            mergeSortDLL(&doublyLinkedListHead);
            printSuccess("Đã sắp xếp danh sách liên kết đôi bằng thuật toán Merge Sort.");
            success = true;
        }
        else
        {
            printWarning("Chỉ hỗ trợ thuật toán Merge Sort cho danh sách liên kết đôi.");
        }
        break;
    default:
        printWarning("Chức năng sắp xếp chưa được hiện thực cho cấu trúc dữ liệu này.");
        break;
    }

    return success;
}

// Hàm xử lý nhập dữ liệu từ file CSV
bool handleInputFromCSV(const char* filePath,
                        int dataStructureType,
                        ArrayStudentList &arrayList,
                        NodeSLL *&singlyLinkedList,
                        NodeSLL *&circularLinkedList,
                        NodeDLL *&doublyLinkedListHead,
                        NodeDLL *&doublyLinkedListTail,
                        NodeBST *&binarySearchTree)
{
    cout << "Đang thử đọc từ file: " << filePath << endl;    if (readFromCSVFile(filePath, arrayList))
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
    clearScreen();
    printHeader("NHẬP THÔNG TIN SINH VIÊN");
    cout << "Lưu ý: Nhập '00' để hủy bỏ nhập liệu\n"
         << endl;

    string tempInput;
    bool isValid;

    // Nhập mã sinh viên
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
