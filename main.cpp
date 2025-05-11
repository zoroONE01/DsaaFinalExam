#include <iostream>
#include <cstring>
#include <limits>
#include <fstream>
#include "libs/student/student_library.h"
#include "libs/knights_tour/knights_tour.h"

using namespace std;

// Hằng số và biến toàn cục
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
    MERGE_SORT = 5
};

// Biến lưu trữ dữ liệu cho từng loại cấu trúc dữ liệu
ArrayStudentList arrayList;
NodeSLL *singlyLinkedList = NULL;
NodeSLL *circularLinkedList = NULL;
NodeDLL *doublyLinkedListHead = NULL;
NodeDLL *doublyLinkedListTail = NULL;
NodeBST *binarySearchTree = NULL;

// Hàm xóa bộ nhớ đệm (buffer) sau khi nhập dữ liệu
void clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Hàm kiểm tra tính hợp lệ của điểm số
bool isValidScore(float score)
{
    return score >= 0 && score <= 10;
}

// Hàm nhập thông tin sinh viên từ bàn phím với kiểm tra lỗi
Student inputStudent()
{
    Student student;

    cout << "Nhập mã sinh viên: ";
    cin >> student.studentID;
    clearInputBuffer();

    cout << "Nhập họ: ";
    cin.getline(student.firstName, sizeof(student.firstName));

    cout << "Nhập tên: ";
    cin.getline(student.lastName, sizeof(student.lastName));

    cout << "Nhập lớp: ";
    cin.getline(student.studentClass, sizeof(student.studentClass));

    float score;
    bool validScore = false;
    while (!validScore)
    {
        cout << "Nhập điểm (0-10): ";
        if (cin >> score)
        {
            if (isValidScore(score))
            {
                student.score = score;
                validScore = true;
            }
            else
            {
                cout << "Lỗi: Điểm phải nằm trong khoảng từ 0 đến 10. Vui lòng nhập lại.\n";
            }
        }
        else
        {
            cout << "Lỗi: Điểm phải là số. Vui lòng nhập lại.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    clearInputBuffer();

    return student;
}

// Hàm nhập mã sinh viên từ bàn phím
void inputStudentID(char *studentID)
{
    cout << "Nhập mã sinh viên: ";
    cin >> studentID;
    clearInputBuffer();
}

// Hàm hiển thị kết quả tìm kiếm
void displaySearchResult(const Student &student, int position)
{
    cout << "Tìm thấy sinh viên tại vị trí " << position << ":\n";
    displayStudent(student);
}

// Hàm hiển thị danh sách sinh viên dựa trên cấu trúc dữ liệu đã chọn
void displayCurrentList(int dataStructureType)
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
        cout << "Danh sách sinh viên theo điểm số (BST Inorder):\n";
        inorderTraversalBST(binarySearchTree);
        break;
    default:
        cout << "Cấu trúc dữ liệu không hợp lệ.\n";
    }
}

// Hàm thêm sinh viên vào cấu trúc dữ liệu đã chọn
void addStudentToDataStructure(const Student &student, int dataStructureType)
{
    switch (dataStructureType)
    {
    case ARRAY_LIST:
        if (addToArrayList(arrayList, student))
        {
            cout << "Đã thêm sinh viên vào danh sách mảng thành công.\n";
        }
        else
        {
            cout << "Lỗi: Không thể thêm sinh viên. Danh sách mảng đã đầy.\n";
        }
        break;
    case SINGLY_LINKED_LIST:
        addToTailSLL(singlyLinkedList, student);
        cout << "Đã thêm sinh viên vào danh sách liên kết đơn thành công.\n";
        break;
    case CIRCULAR_LINKED_LIST:
        addToCLL(circularLinkedList, student);
        cout << "Đã thêm sinh viên vào danh sách liên kết vòng thành công.\n";
        break;
    case DOUBLY_LINKED_LIST:
        addToTailDLL(doublyLinkedListHead, doublyLinkedListTail, student);
        cout << "Đã thêm sinh viên vào danh sách liên kết đôi thành công.\n";
        break;
    case BINARY_SEARCH_TREE:
        insertToBST(binarySearchTree, student);
        cout << "Đã thêm sinh viên vào cây BST thành công.\n";
        break;
    default:
        cout << "Cấu trúc dữ liệu không hợp lệ.\n";
    }
}

// Hàm xóa sinh viên khỏi cấu trúc dữ liệu đã chọn
void deleteStudentFromDataStructure(const char *studentID, int dataStructureType)
{
    bool success = false;

    switch (dataStructureType)
    {
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
        cout << "Chức năng xóa không được hỗ trợ trực tiếp cho BST.\n";
        return;
    default:
        cout << "Cấu trúc dữ liệu không hợp lệ.\n";
        return;
    }

    if (success)
    {
        cout << "Đã xóa sinh viên có mã " << studentID << " thành công.\n";
    }
    else
    {
        cout << "Không tìm thấy sinh viên có mã " << studentID << ".\n";
    }
}

// Hàm cập nhật sinh viên trong cấu trúc dữ liệu đã chọn
void updateStudentInDataStructure(const Student &student, int dataStructureType)
{
    bool success = false;

    switch (dataStructureType)
    {
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
        cout << "Chức năng cập nhật không được hỗ trợ trực tiếp cho BST.\n";
        return;
    default:
        cout << "Cấu trúc dữ liệu không hợp lệ.\n";
        return;
    }

    if (success)
    {
        cout << "Đã cập nhật thông tin sinh viên có mã " << student.studentID << " thành công.\n";
    }
    else
    {
        cout << "Không tìm thấy sinh viên có mã " << student.studentID << ".\n";
    }
}

// Hàm tìm kiếm sinh viên trong cấu trúc dữ liệu đã chọn
void searchStudentInDataStructure(const char *studentID, int dataStructureType)
{
    switch (dataStructureType)
    {
    case ARRAY_LIST:
    {
        int position = searchInArrayList(arrayList, studentID);
        if (position != -1)
        {
            cout << "Tìm thấy sinh viên tại vị trí " << position + 1 << ":\n";
            displayStudent(arrayList.students[position]);
        }
        else
        {
            cout << "Không tìm thấy sinh viên có mã " << studentID << ".\n";
        }
        break;
    }
    case SINGLY_LINKED_LIST:
    {
        NodeSLL *result = searchInSLL(singlyLinkedList, studentID);
        if (result != NULL)
        {
            cout << "Tìm thấy sinh viên:\n";
            displayStudent(result->info);
        }
        else
        {
            cout << "Không tìm thấy sinh viên có mã " << studentID << ".\n";
        }
        break;
    }
    case CIRCULAR_LINKED_LIST:
    {
        NodeSLL *result = searchInCLL(circularLinkedList, studentID);
        if (result != NULL)
        {
            cout << "Tìm thấy sinh viên:\n";
            displayStudent(result->info);
        }
        else
        {
            cout << "Không tìm thấy sinh viên có mã " << studentID << ".\n";
        }
        break;
    }
    case DOUBLY_LINKED_LIST:
    {
        NodeDLL *result = searchInDLL(doublyLinkedListHead, studentID);
        if (result != NULL)
        {
            cout << "Tìm thấy sinh viên:\n";
            displayStudent(result->info);
        }
        else
        {
            cout << "Không tìm thấy sinh viên có mã " << studentID << ".\n";
        }
        break;
    }
    case BINARY_SEARCH_TREE:
        cout << "Tìm kiếm theo mã sinh viên không được hỗ trợ trực tiếp cho BST.\n";
        break;
    default:
        cout << "Cấu trúc dữ liệu không hợp lệ.\n";
    }
}

// Hàm thực hiện thống kê sinh viên trên cấu trúc dữ liệu mảng
void performStatistics(int dataStructureType)
{
    if (dataStructureType != ARRAY_LIST)
    {
        cout << "Chức năng thống kê chỉ được hiện thực cho danh sách mảng.\n";
        return;
    }

    if (arrayList.count == 0)
    {
        cout << "Danh sách sinh viên rỗng. Không có thống kê.\n";
        return;
    }

    float highest = findHighestScore(arrayList);
    float lowest = findLowestScore(arrayList);
    float average = calculateAverageScore(arrayList);

    cout << "===== Thống kê điểm sinh viên =====\n";
    cout << "Số lượng sinh viên: " << arrayList.count << "\n";
    cout << "Điểm cao nhất: " << highest << "\n";
    cout << "Điểm thấp nhất: " << lowest << "\n";
    cout << "Điểm trung bình: " << average << "\n";

    cout << "\nSinh viên có điểm cao nhất:\n";
    for (int i = 0; i < arrayList.count; i++)
    {
        if (arrayList.students[i].score == highest)
        {
            displayStudent(arrayList.students[i]);
            cout << "-------------------\n";
        }
    }

    cout << "\nSinh viên có điểm thấp nhất:\n";
    for (int i = 0; i < arrayList.count; i++)
    {
        if (arrayList.students[i].score == lowest)
        {
            displayStudent(arrayList.students[i]);
            cout << "-------------------\n";
        }
    }
}

// Hàm sắp xếp danh sách sinh viên theo điểm số sử dụng thuật toán được chọn
void sortStudentList(int dataStructureType, int sortAlgorithm)
{
    if (dataStructureType == ARRAY_LIST)
    {
        switch (sortAlgorithm)
        {
        case BUBBLE_SORT:
            bubbleSortArrayList(arrayList);
            cout << "Đã sắp xếp danh sách sử dụng thuật toán Bubble Sort.\n";
            break;
        case INSERTION_SORT:
            insertionSortArrayList(arrayList);
            cout << "Đã sắp xếp danh sách sử dụng thuật toán Insertion Sort.\n";
            break;
        case SELECTION_SORT:
            selectionSortArrayList(arrayList);
            cout << "Đã sắp xếp danh sách sử dụng thuật toán Selection Sort.\n";
            break;
        case QUICK_SORT:
            quickSortArrayList(arrayList);
            cout << "Đã sắp xếp danh sách sử dụng thuật toán Quick Sort.\n";
            break;
        default:
            cout << "Thuật toán sắp xếp không hợp lệ cho danh sách mảng.\n";
        }
    }
    else if (dataStructureType == DOUBLY_LINKED_LIST && sortAlgorithm == MERGE_SORT)
    {
        mergeSortDLL(&doublyLinkedListHead);
        cout << "Đã sắp xếp danh sách liên kết đôi sử dụng thuật toán Merge Sort.\n";
    }
    else
    {
        cout << "Sắp xếp không được hỗ trợ cho cấu trúc dữ liệu này hoặc thuật toán không phù hợp.\n";
    }
}

// Hàm giải phóng bộ nhớ của tất cả các cấu trúc dữ liệu
void freeAllMemory()
{
    freeSLL(singlyLinkedList);
    freeCLL(circularLinkedList);
    freeDLL(doublyLinkedListHead, doublyLinkedListTail);
    freeBST(binarySearchTree);
}

// Hàm menu chính
void displayMainMenu()
{
    cout << "\n===== HỆ THỐNG QUẢN LÝ SINH VIÊN =====\n";
    cout << "1. Chọn cấu trúc dữ liệu\n";
    cout << "2. Nhập dữ liệu từ file CSV\n";
    cout << "3. Thêm sinh viên mới\n";
    cout << "4. Xóa sinh viên theo mã\n";
    cout << "5. Cập nhật sinh viên theo mã\n";
    cout << "6. Hiển thị danh sách sinh viên\n";
    cout << "7. Tìm kiếm sinh viên theo mã\n";
    cout << "8. Thống kê sinh viên (chỉ cho mảng)\n";
    cout << "9. Sắp xếp sinh viên theo điểm số\n";
    cout << "10. Bài toán Mã Đi Tuần\n";
    cout << "0. Thoát\n";
    cout << "Nhập lựa chọn: ";
}

// Hàm menu chọn cấu trúc dữ liệu
int selectDataStructure()
{
    int choice;

    cout << "\n===== CHỌN CẤU TRÚC DỮ LIỆU =====\n";
    cout << "1. Danh sách mảng\n";
    cout << "2. Danh sách liên kết đơn\n";
    cout << "3. Danh sách liên kết vòng\n";
    cout << "4. Danh sách liên kết đôi\n";
    cout << "5. Cây tìm kiếm nhị phân (BST)\n";
    cout << "Nhập lựa chọn: ";

    while (!(cin >> choice) || choice < 1 || choice > 5)
    {
        cout << "Lựa chọn không hợp lệ. Vui lòng nhập lại: ";
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

    cout << "\n===== CHỌN THUẬT TOÁN SẮP XẾP =====\n";

    if (dataStructureType == ARRAY_LIST)
    {
        cout << "1. Bubble Sort\n";
        cout << "2. Insertion Sort\n";
        cout << "3. Selection Sort\n";
        cout << "4. Quick Sort\n";
    }
    else if (dataStructureType == DOUBLY_LINKED_LIST)
    {
        cout << "5. Merge Sort\n";
    }
    else
    {
        cout << "Không có thuật toán sắp xếp được hỗ trợ cho cấu trúc dữ liệu này.\n";
        return -1;
    }

    cout << "Nhập lựa chọn: ";

    while (!(cin >> choice) ||
           (dataStructureType == ARRAY_LIST && (choice < 1 || choice > 4)) ||
           (dataStructureType == DOUBLY_LINKED_LIST && choice != 5))
    {
        cout << "Lựa chọn không hợp lệ. Vui lòng nhập lại: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    clearInputBuffer();
    return choice;
}

// Hàm xử lý nhập dữ liệu từ file CSV
void handleInputFromCSV(int dataStructureType)
{
    char filename[100];

    cout << "Nhập tên file CSV: ";
    cin.getline(filename, sizeof(filename));

    if (dataStructureType == ARRAY_LIST)
    {
        if (readFromCSVFile(filename, arrayList))
        {
            cout << "Đã đọc dữ liệu từ file " << filename << " thành công.\n";
            cout << "Đã đọc " << arrayList.count << " sinh viên.\n";
        }
        else
        {
            cout << "Lỗi: Không thể đọc file " << filename << ".\n";
        }
    }
    else
    {
        // Đọc từ file vào mảng tạm
        ArrayStudentList tempList;
        if (readFromCSVFile(filename, tempList))
        {
            cout << "Đã đọc dữ liệu từ file " << filename << " thành công.\n";

            // Chuyển dữ liệu từ mảng tạm vào cấu trúc dữ liệu được chọn
            for (int i = 0; i < tempList.count; i++)
            {
                addStudentToDataStructure(tempList.students[i], dataStructureType);
            }

            cout << "Đã chuyển " << tempList.count << " sinh viên vào cấu trúc dữ liệu.\n";
        }
        else
        {
            cout << "Lỗi: Không thể đọc file " << filename << ".\n";
        }
    }
}

int main()
{
    // Khởi tạo các cấu trúc dữ liệu
    initArrayList(arrayList);
    initSLL(singlyLinkedList);
    initCLL(circularLinkedList);
    initDLL(doublyLinkedListHead, doublyLinkedListTail);
    initBST(binarySearchTree);

    int dataStructureType = ARRAY_LIST; // Mặc định sử dụng danh sách mảng
    int choice;

    do
    {
        displayMainMenu();

        if (!(cin >> choice))
        {
            cout << "Lựa chọn không hợp lệ. Vui lòng nhập lại.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        clearInputBuffer();

        switch (choice)
        {
        case 1:
            dataStructureType = selectDataStructure();
            break;
        case 2:
            handleInputFromCSV(dataStructureType);
            break;
        case 3:
        {
            Student student = inputStudent();
            addStudentToDataStructure(student, dataStructureType);
            break;
        }
        case 4:
        {
            char studentID[20];
            inputStudentID(studentID);
            deleteStudentFromDataStructure(studentID, dataStructureType);
            break;
        }
        case 5:
        {
            char studentID[20];
            cout << "Nhập mã sinh viên cần cập nhật: ";
            cin >> studentID;
            clearInputBuffer();

            // Kiểm tra xem sinh viên có tồn tại không
            bool exists = false;

            if (dataStructureType == ARRAY_LIST)
            {
                exists = searchInArrayList(arrayList, studentID) != -1;
            }
            else if (dataStructureType == SINGLY_LINKED_LIST)
            {
                exists = searchInSLL(singlyLinkedList, studentID) != NULL;
            }
            else if (dataStructureType == CIRCULAR_LINKED_LIST)
            {
                exists = searchInCLL(circularLinkedList, studentID) != NULL;
            }
            else if (dataStructureType == DOUBLY_LINKED_LIST)
            {
                exists = searchInDLL(doublyLinkedListHead, studentID) != NULL;
            }

            if (exists)
            {
                cout << "Nhập thông tin mới cho sinh viên:\n";
                Student updateStudent = inputStudent();
                strcpy(updateStudent.studentID, studentID); // Giữ nguyên mã sinh viên
                updateStudentInDataStructure(updateStudent, dataStructureType);
            }
            else
            {
                cout << "Không tìm thấy sinh viên có mã " << studentID << ".\n";
            }
            break;
        }
        case 6:
            displayCurrentList(dataStructureType);
            break;
        case 7:
        {
            char studentID[20];
            inputStudentID(studentID);
            searchStudentInDataStructure(studentID, dataStructureType);
            break;
        }
        case 8:
            performStatistics(dataStructureType);
            break;
        case 9:
        {
            int sortAlgorithm = selectSortAlgorithm(dataStructureType);
            if (sortAlgorithm != -1)
            {
                sortStudentList(dataStructureType, sortAlgorithm);
            }
            break;
        }
        case 10:
            cout << "\n===== BÀI TOÁN MÃ ĐI TUẦN =====\n";
            knightsTour();
            break;
        case 0:
            cout << "Đang thoát chương trình...\n";
            freeAllMemory();
            break;
        default:
            cout << "Lựa chọn không hợp lệ. Vui lòng nhập lại.\n";
        }
    } while (choice != 0);

    return 0;
}