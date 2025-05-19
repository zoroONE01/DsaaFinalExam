#ifndef COMMON_OPERATIONS_H
#define COMMON_OPERATIONS_H

#include "student_struct.h"
#include "array_list.h"
#include "singly_linked_list.h"
#include "circular_linked_list.h"
#include "doubly_linked_list.h"
#include "binary_search_tree.h"
#include "../ui/common_ui.h"
#include <iostream>

using namespace std;

// Các hằng số cho thuật toán HEAP_SORT (không có trong common_ui.h)
enum AdditionalSortAlgorithms {
    HEAP_SORT = 6
};

// Hàm kiểm tra xem một cấu trúc dữ liệu có rỗng hay không
bool isDataStructureEmpty(int dataStructureType, 
                         const ArrayStudentList &arrayList, 
                         NodeSLL *singlyLinkedList, 
                         NodeSLL *circularLinkedList, 
                         NodeDLL *doublyLinkedListHead,
                         NodeBST *binarySearchTree) {
    switch (dataStructureType) {
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
bool isStudentExists(const char* studentID, int dataStructureType, 
                    const ArrayStudentList &arrayList, 
                    NodeSLL *singlyLinkedList, 
                    NodeSLL *circularLinkedList, 
                    NodeDLL *doublyLinkedListHead) {
    if (dataStructureType == ARRAY_LIST) {
        return searchInArrayList(arrayList, studentID) != -1;
    } else if (dataStructureType == SINGLY_LINKED_LIST) {
        return searchInSLL(singlyLinkedList, studentID) != NULL;
    } else if (dataStructureType == CIRCULAR_LINKED_LIST) {
        return searchInCLL(circularLinkedList, studentID) != NULL;
    } else if (dataStructureType == DOUBLY_LINKED_LIST) {
        return searchInDLL(doublyLinkedListHead, studentID) != NULL;
    }
    return false; // Không hỗ trợ cho BST
}

// Hàm thoát chương trình, giải phóng bộ nhớ
void exitProgram(NodeSLL *&singlyLinkedList, 
                NodeSLL *&circularLinkedList, 
                NodeDLL *&doublyLinkedListHead, 
                NodeDLL *&doublyLinkedListTail, 
                NodeBST *&binarySearchTree) {
    printInfo("Đang thoát chương trình...");
    
    // Giải phóng bộ nhớ
    freeSLL(singlyLinkedList);
    freeCLL(circularLinkedList);
    freeDLL(doublyLinkedListHead, doublyLinkedListTail);
    freeBST(binarySearchTree);
}

// Hàm xác nhận hủy bỏ thao tác nhập liệu
bool confirmCancel() {
    cout << "Bạn có chắc muốn hủy thao tác? (Nhập 0 để hủy, nhập khác để tiếp tục): ";
    string confirm;
    cin >> confirm;
    clearInputBuffer();

    if (confirm == "0") {
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
                              NodeBST *&binarySearchTree) {
    bool success = true;
    
    switch (dataStructureType) {
    case ARRAY_LIST:
        if (addToArrayList(arrayList, student)) {
            printSuccess("Đã thêm sinh viên vào danh sách mảng thành công.");
        } else {
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
        printSuccess("Đã thêm sinh viên vào cây BST thành công.");
        break;
    default:
        printError("Cấu trúc dữ liệu không hợp lệ.");
        success = false;
    }
    
    return success;
}

// Hàm xóa sinh viên khỏi cấu trúc dữ liệu đã chọn
bool deleteStudentFromDataStructure(const char *studentID, int dataStructureType,
                                  ArrayStudentList &arrayList,
                                  NodeSLL *&singlyLinkedList,
                                  NodeSLL *&circularLinkedList,
                                  NodeDLL *&doublyLinkedListHead,
                                  NodeDLL *&doublyLinkedListTail) {
    bool success = false;

    switch (dataStructureType) {
    case ARRAY_LIST:
        success = deleteFromArrayList(arrayList, studentID);
        break;
    case SINGLY_LINKED_LIST:
        success = deleteFromSLL(singlyLinkedList, studentID);
        break;
    case CIRCULAR_LINKED_LIST:
        success = deleteFromCLL(circularLinkedList, studentID);
        break;
    case DOUBLY_LINKED_LIST:
        success = deleteFromDLL(doublyLinkedListHead, doublyLinkedListTail, studentID);
        break;
    case BINARY_SEARCH_TREE:
        // Đối với BST, cần tìm sinh viên trước, sau đó xóa theo điểm số
        printWarning("Chức năng xóa không được hỗ trợ trực tiếp cho BST.");
        return false;
    default:
        printError("Cấu trúc dữ liệu không hợp lệ.");
        return false;
    }

    if (success) {
        printSuccess(("Đã xóa sinh viên có mã " + string(studentID) + " thành công.").c_str());
    } else {
        printError(("Không tìm thấy sinh viên có mã " + string(studentID) + ".").c_str());
    }
    
    return success;
}

// Hàm cập nhật sinh viên trong cấu trúc dữ liệu đã chọn
bool updateStudentInDataStructure(const Student &student, int dataStructureType,
                                 ArrayStudentList &arrayList,
                                 NodeSLL *&singlyLinkedList,
                                 NodeSLL *&circularLinkedList,
                                 NodeDLL *&doublyLinkedListHead) {
    bool success = false;

    switch (dataStructureType) {
    case ARRAY_LIST:
        success = updateInArrayList(arrayList, student);
        break;
    case SINGLY_LINKED_LIST:
        success = updateInSLL(singlyLinkedList, student);
        break;
    case CIRCULAR_LINKED_LIST:
        success = updateInCLL(circularLinkedList, student);
        break;
    case DOUBLY_LINKED_LIST:
        success = updateInDLL(doublyLinkedListHead, student);
        break;
    case BINARY_SEARCH_TREE:
        printWarning("Chức năng cập nhật không được hỗ trợ trực tiếp cho BST.");
        return false;
    default:
        printError("Cấu trúc dữ liệu không hợp lệ.");
        return false;
    }

    if (success) {
        printSuccess(("Đã cập nhật thông tin sinh viên có mã " + string(student.studentID) + " thành công.").c_str());
    } else {
        printError(("Không tìm thấy sinh viên có mã " + string(student.studentID) + ".").c_str());
    }
    
    return success;
}

// Hàm tìm kiếm sinh viên trong cấu trúc dữ liệu đã chọn
void searchStudentInDataStructure(const char *studentID, int dataStructureType,
                                 const ArrayStudentList &arrayList,
                                 NodeSLL *singlyLinkedList,
                                 NodeSLL *circularLinkedList,
                                 NodeDLL *doublyLinkedListHead) {
    switch (dataStructureType) {
    case ARRAY_LIST:
    {
        int position = searchInArrayList(arrayList, studentID);
        if (position != -1) {
            cout << "Tìm thấy sinh viên tại vị trí " << position + 1 << ":\n";
            displayStudent(arrayList.students[position]);
        } else {
            printError(("Không tìm thấy sinh viên có mã " + string(studentID) + ".").c_str());
        }
        break;
    }
    case SINGLY_LINKED_LIST:
    {
        NodeSLL *result = searchInSLL(singlyLinkedList, studentID);
        if (result != NULL) {
            printSuccess("Tìm thấy sinh viên:");
            displayStudent(result->info);
        } else {
            printError(("Không tìm thấy sinh viên có mã " + string(studentID) + ".").c_str());
        }
        break;
    }
    case CIRCULAR_LINKED_LIST:
    {
        NodeSLL *result = searchInCLL(circularLinkedList, studentID);
        if (result != NULL) {
            printSuccess("Tìm thấy sinh viên:");
            displayStudent(result->info);
        } else {
            printError(("Không tìm thấy sinh viên có mã " + string(studentID) + ".").c_str());
        }
        break;
    }
    case DOUBLY_LINKED_LIST:
    {
        NodeDLL *result = searchInDLL(doublyLinkedListHead, studentID);
        if (result != NULL) {
            printSuccess("Tìm thấy sinh viên:");
            displayStudent(result->info);
        } else {
            printError(("Không tìm thấy sinh viên có mã " + string(studentID) + ".").c_str());
        }
        break;
    }
    case BINARY_SEARCH_TREE:
        printWarning("Tìm kiếm theo mã sinh viên không được hỗ trợ trực tiếp cho BST.");
        break;
    default:
        printError("Cấu trúc dữ liệu không hợp lệ.");
    }
}

// Hàm hiển thị danh sách sinh viên dựa trên cấu trúc dữ liệu đã chọn
void displayCurrentList(int dataStructureType,
                       const ArrayStudentList &arrayList,
                       NodeSLL *singlyLinkedList,
                       NodeSLL *circularLinkedList,
                       NodeDLL *doublyLinkedListHead,
                       NodeBST *binarySearchTree) {
    switch (dataStructureType) {
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
        cout << "Danh sách sinh viên theo điểm số (BST Inorder):\n";
        inorderTraversalBST(binarySearchTree);
        break;
    default:
        printError("Cấu trúc dữ liệu không hợp lệ.");
    }
}

// Hàm thực hiện thống kê sinh viên
void performStatistics(int dataStructureType, const ArrayStudentList &arrayList) {
    if (dataStructureType != ARRAY_LIST) {
        printWarning("Chức năng thống kê chỉ được hiện thực cho danh sách mảng.");
        return;
    }

    if (arrayList.count == 0) {
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

    cout << CYAN << "\nSinh viên có điểm cao nhất:\n" << RESET;
    printDivider();
    for (int i = 0; i < arrayList.count; i++) {
        if (arrayList.students[i].score == highest) {
            displayStudent(arrayList.students[i]);
            printDivider();
        }
    }

    cout << CYAN << "\nSinh viên có điểm thấp nhất:\n" << RESET;
    printDivider();
    for (int i = 0; i < arrayList.count; i++) {
        if (arrayList.students[i].score == lowest) {
            displayStudent(arrayList.students[i]);
            printDivider();
        }
    }
}

// Hàm sắp xếp danh sách sinh viên theo điểm số sử dụng thuật toán được chọn
bool sortStudentList(int dataStructureType, int sortAlgorithm,
                     ArrayStudentList &arrayList,
                     NodeDLL *&doublyLinkedListHead) {
    bool success = true;
    
    if (dataStructureType == ARRAY_LIST) {
        switch (sortAlgorithm) {
        case BUBBLE_SORT:
            bubbleSortArrayList(arrayList);
            printSuccess("Đã sắp xếp danh sách sử dụng thuật toán Bubble Sort.");
            break;
        case INSERTION_SORT:
            insertionSortArrayList(arrayList);
            printSuccess("Đã sắp xếp danh sách sử dụng thuật toán Insertion Sort.");
            break;
        case SELECTION_SORT:
            selectionSortArrayList(arrayList);
            printSuccess("Đã sắp xếp danh sách sử dụng thuật toán Selection Sort.");
            break;
        case QUICK_SORT:
            quickSortArrayList(arrayList);
            printSuccess("Đã sắp xếp danh sách sử dụng thuật toán Quick Sort.");
            break;
        default:
            printError("Thuật toán sắp xếp không hợp lệ cho danh sách mảng.");
            success = false;
        }
    } else if (dataStructureType == DOUBLY_LINKED_LIST && sortAlgorithm == MERGE_SORT) {
        mergeSortDLL(&doublyLinkedListHead);
        printSuccess("Đã sắp xếp danh sách liên kết đôi sử dụng thuật toán Merge Sort.");
    } else {
        printWarning("Sắp xếp không được hỗ trợ cho cấu trúc dữ liệu này hoặc thuật toán không phù hợp.");
        success = false;
    }
    
    return success;
}

// Hàm xử lý nhập dữ liệu từ file CSV
bool handleInputFromCSV(int dataStructureType, 
                        ArrayStudentList &arrayList,
                        NodeSLL *&singlyLinkedList,
                        NodeSLL *&circularLinkedList,
                        NodeDLL *&doublyLinkedListHead,
                        NodeDLL *&doublyLinkedListTail,
                        NodeBST *&binarySearchTree) {
    // Mặc định sử dụng tên tệp "students.csv"
    char filename[100] = "students.csv";

    clearScreen();
    printHeader("NHẬP DỮ LIỆU TỪ FILE CSV");

    // Hiển thị thông tin tệp mặc định
    cout << BOLD;
    cout << "┌─────────────────────────────────────────────────────────────┐" << endl;
    cout << "│  Tên tệp mặc định: students.csv                             │" << endl;
    cout << "│  Nhấn Enter để sử dụng tệp mặc định hoặc nhập tên tệp khác  │" << endl;
    cout << "└─────────────────────────────────────────────────────────────┘" << RESET << endl;

    cout << "\nNhập tên tệp CSV [students.csv]: ";

    // Nếu người dùng chỉ nhấn Enter, giữ nguyên tên tệp mặc định
    string input;
    getline(cin, input);
    input = trim(input); // Trim input
    if (!input.empty()) {
        strcpy(filename, input.c_str());
    }

    bool success = true;
    if (dataStructureType == ARRAY_LIST) {
        if (readFromCSVFile(filename, arrayList)) {
            printSuccess("Đã đọc dữ liệu từ file thành công.");
            printInfo(("Đã đọc " + to_string(arrayList.count) + " sinh viên.").c_str());
        } else {
            printError(("Không thể đọc file " + string(filename) + ".").c_str());
            success = false;
        }
    } else {
        // Đọc từ file vào mảng tạm
        ArrayStudentList tempList;
        if (readFromCSVFile(filename, tempList)) {
            printSuccess("Đã đọc dữ liệu từ file thành công.");

            // Chuyển dữ liệu từ mảng tạm vào cấu trúc dữ liệu được chọn
            for (int i = 0; i < tempList.count; i++) {
                addStudentToDataStructure(tempList.students[i], dataStructureType, 
                                         arrayList, singlyLinkedList, circularLinkedList,
                                         doublyLinkedListHead, doublyLinkedListTail,
                                         binarySearchTree);
            }

            printInfo(("Đã chuyển " + to_string(tempList.count) + " sinh viên vào cấu trúc dữ liệu.").c_str());
        } else {
            printError(("Không thể đọc file " + string(filename) + ".").c_str());
            success = false;
        }
    }
    
    return success;
}

// Hàm nhập mã sinh viên từ bàn phím
bool inputStudentID(char *studentID) {
    string tempInput;
    bool isValid;

    // Thông báo về cách hủy bỏ nhập liệu
    printInfo("Lưu ý: Nhập \"00\" để hủy bỏ và trở về menu chính.");

    do {
        cout << "Nhập mã sinh viên: ";
        cin >> tempInput;
        clearInputBuffer();
        tempInput = trim(tempInput); // Trim input

        // Kiểm tra hủy bỏ
        if (tempInput == "00") {
            if (confirmCancel()) {
                studentID[0] = '\0'; // Đánh dấu là đã hủy bỏ bằng chuỗi rỗng
                return false;
            }
            continue;
        }

        isValid = validateAndShowStudentID(tempInput);
        if (isValid) {
            strcpy(studentID, tempInput.c_str());
        }
    } while (!isValid);
    
    return true;
}

// Hàm nhập thông tin sinh viên từ bàn phím
bool inputStudent(Student &student) {
    string tempInput;
    bool isValid;

    // Thông báo về cách hủy bỏ nhập liệu
    printInfo("Lưu ý: Nhập \"00\" để hủy bỏ và trở về menu chính.");

    // Nhập mã sinh viên
    do {
        cout << "Nhập mã sinh viên: ";
        cin >> tempInput;
        clearInputBuffer();
        tempInput = trim(tempInput); // Trim input

        // Kiểm tra hủy bỏ
        if (tempInput == "00") {
            if (confirmCancel()) {
                student.studentID[0] = '\0'; // Đánh dấu là đã hủy bỏ bằng chuỗi rỗng
                return false;
            }
            continue;
        }

        isValid = validateAndShowStudentID(tempInput);
        if (isValid) {
            strcpy(student.studentID, tempInput.c_str());
        }
    } while (!isValid);

    // Nhập họ
    do {
        cout << "Nhập họ: ";
        getline(cin, tempInput);
        tempInput = trim(tempInput); // Trim input

        // Kiểm tra hủy bỏ
        if (tempInput == "00") {
            if (confirmCancel()) {
                student.studentID[0] = '\0'; // Đánh dấu là đã hủy bỏ
                return false;
            }
            continue;
        }

        isValid = validateAndShowName(tempInput);
        if (isValid) {
            strcpy(student.firstName, tempInput.c_str());
        }
    } while (!isValid);

    // Nhập tên
    do {
        cout << "Nhập tên: ";
        getline(cin, tempInput);
        tempInput = trim(tempInput); // Trim input

        // Kiểm tra hủy bỏ
        if (tempInput == "00") {
            if (confirmCancel()) {
                student.studentID[0] = '\0'; // Đánh dấu là đã hủy bỏ
                return false;
            }
            continue;
        }

        isValid = validateAndShowName(tempInput);
        if (isValid) {
            strcpy(student.lastName, tempInput.c_str());
        }
    } while (!isValid);

    // Nhập lớp
    do {
        cout << "Nhập lớp: ";
        getline(cin, tempInput);
        tempInput = trim(tempInput); // Trim input

        // Kiểm tra hủy bỏ
        if (tempInput == "00") {
            if (confirmCancel()) {
                student.studentID[0] = '\0'; // Đánh dấu là đã hủy bỏ
                return false;
            }
            continue;
        }

        isValid = validateAndShowClassName(tempInput);
        if (isValid) {
            strcpy(student.studentClass, tempInput.c_str());
        }
    } while (!isValid);

    // Nhập điểm số
    float score;
    string scoreInput;
    do {
        cout << "Nhập điểm (0-10): ";
        cin >> scoreInput;

        // Kiểm tra hủy bỏ (phân biệt với giá trị điểm 0)
        if (scoreInput == "00") {
            if (confirmCancel()) {
                student.studentID[0] = '\0'; // Đánh dấu là đã hủy bỏ
                clearInputBuffer();
                return false;
            }
            continue;
        }

        // Chuyển đổi thành số
        try {
            score = stof(scoreInput);
            isValid = validateAndShowScore(score);
            if (isValid) {
                student.score = score;
            }
        } catch (...) {
            isValid = false;
            printError("Điểm số không hợp lệ.");
        }
    } while (!isValid);
    clearInputBuffer();

    return true;
}

// Hàm để khởi tạo tất cả các cấu trúc dữ liệu
void initAllDataStructures(ArrayStudentList &arrayList,
                          NodeSLL *&singlyLinkedList,
                          NodeSLL *&circularLinkedList,
                          NodeDLL *&doublyLinkedListHead,
                          NodeDLL *&doublyLinkedListTail,
                          NodeBST *&binarySearchTree) {
    initArrayList(arrayList);
    initSLL(singlyLinkedList);
    initCLL(circularLinkedList);
    initDLL(doublyLinkedListHead, doublyLinkedListTail);
    initBST(binarySearchTree);
}

#endif // COMMON_OPERATIONS_H