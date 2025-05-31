#include "../../include/utils/common_operations.h"
#include "../../include/utils/validation.h"
#include "../../include/utils/utils.h"
#include "../../include/utils/student_input.h"
#include "../../include/algorithms/sorting_algorithms.h"
#include "../../include/algorithms/searching_algorithms.h"
#include "../../include/ui/ui_common.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>
#include <iomanip>

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
    case 1: // Mảng
        return arrayList.count == 0;
    case 2: // Danh sách liên kết đơn
        return singlyLinkedList == NULL;
    case 3: // Danh sách liên kết vòng
        return circularLinkedList == NULL;
    case 4: // Danh sách liên kết đôi
        return doublyLinkedListHead == NULL;
    case 5: // Cây nhị phân tìm kiếm
        return binarySearchTree == NULL;
    default:
        return true;
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
    case 1: // Mảng
        for (int i = 0; i < arrayList.count; i++)
        {
            if (strcmp(arrayList.students[i].studentID, studentID) == 0)
            {
                return true;
            }
        }
        break;
    case 2: // Danh sách liên kết đơn
        return findInSLL(singlyLinkedList, studentID) != NULL;
    case 3: // Danh sách liên kết vòng
        return findInCLL(circularLinkedList, studentID) != NULL;
    case 4: // Danh sách liên kết đôi
        return findInDLL(doublyLinkedListHead, studentID) != NULL;
    default:
        break;
    }
    return false;
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
    switch (dataStructureType)
    {
    case 1: // Mảng
        return addToArrayList(arrayList, student);
    case 2: // Danh sách liên kết đơn
        addToHeadSLL(singlyLinkedList, student);
        return true;
    case 3: // Danh sách liên kết vòng
        addToHeadCLL(circularLinkedList, student);
        return true;
    case 4: // Danh sách liên kết đôi
        addToHeadDLL(doublyLinkedListHead, doublyLinkedListTail, student);
        return true;
    case 5: // Cây nhị phân tìm kiếm
        insertStudentBST(binarySearchTree, student);
        return true;
    default:
        return false;
    }
}

// Hàm xóa sinh viên khỏi cấu trúc dữ liệu đã chọn
bool deleteStudentFromDataStructure(const char *studentID, int dataStructureType,
                                    ArrayStudentList &arrayList,
                                    NodeSLL *&singlyLinkedList,
                                    NodeSLL *&circularLinkedList,
                                    NodeDLL *&doublyLinkedListHead,
                                    NodeDLL *&doublyLinkedListTail)
{
    switch (dataStructureType)
    {
    case 1: // Mảng
        return deleteFromArrayList(arrayList, studentID);
    case 2: // Danh sách liên kết đơn
        return deleteFromSLL(singlyLinkedList, studentID);
    case 3: // Danh sách liên kết vòng
        return deleteFromCLL(circularLinkedList, studentID);
    case 4: // Danh sách liên kết đôi
        return deleteFromDLL(doublyLinkedListHead, doublyLinkedListTail, studentID);
    default:
        return false;
    }
}

// Hàm cập nhật sinh viên trong cấu trúc dữ liệu đã chọn
bool updateStudentInDataStructure(const Student &student, int dataStructureType,
                                  ArrayStudentList &arrayList,
                                  NodeSLL *&singlyLinkedList,
                                  NodeSLL *&circularLinkedList,
                                  NodeDLL *&doublyLinkedListHead)
{
    switch (dataStructureType)
    {
    case 1: // Mảng
        return updateInArrayList(arrayList, student);
    case 2: // Danh sách liên kết đơn
        return updateInSLL(singlyLinkedList, student);
    case 3: // Danh sách liên kết vòng
        return updateInCLL(circularLinkedList, student);
    case 4: // Danh sách liên kết đôi
        return updateInDLL(doublyLinkedListHead, student);
    default:
        return false;
    }
}

// Hàm tìm kiếm sinh viên trong cấu trúc dữ liệu đã chọn
void searchStudentInDataStructure(const char *studentID, int dataStructureType,
                                  const ArrayStudentList &arrayList,
                                  NodeSLL *singlyLinkedList,
                                  NodeSLL *circularLinkedList,
                                  NodeDLL *doublyLinkedListHead)
{
    // Hiển thị tiêu đề
    cout << "Kết quả tìm kiếm cho mã sinh viên: " << studentID << endl;
    cout << left << setw(10) << "Mã SV"
         << setw(20) << "Họ"
         << setw(20) << "Tên"
         << setw(15) << "Lớp"
         << setw(5) << "Điểm" << endl;
    cout << string(70, '-') << endl;

    switch (dataStructureType)
    {
    case 1:
    { // Mảng
        int foundIndex = sequentialSearch(arrayList, studentID);
        if (foundIndex != -1)
        {
            displayStudent(arrayList.students[foundIndex]);
        }
        else
        {
            cout << "Không tìm thấy sinh viên với mã " << studentID << endl;
        }
        break;
    }
    case 2:
    { // Danh sách liên kết đơn
        NodeSLL *foundNode = findInSLL(singlyLinkedList, studentID);
        if (foundNode != NULL)
        {
            displayStudent(foundNode->info);
        }
        else
        {
            cout << "Không tìm thấy sinh viên với mã " << studentID << endl;
        }
        break;
    }
    case 3:
    { // Danh sách liên kết vòng
        NodeSLL *foundNode = findInCLL(circularLinkedList, studentID);
        if (foundNode != NULL)
        {
            displayStudent(foundNode->info);
        }
        else
        {
            cout << "Không tìm thấy sinh viên với mã " << studentID << endl;
        }
        break;
    }
    case 4:
    { // Danh sách liên kết đôi
        NodeDLL *foundNode = findInDLL(doublyLinkedListHead, studentID);
        if (foundNode != NULL)
        {
            displayStudent(foundNode->info);
        }
        else
        {
            cout << "Không tìm thấy sinh viên với mã " << studentID << endl;
        }
        break;
    }
    default:
        cout << "Cấu trúc dữ liệu không hợp lệ!" << endl;
        break;
    }
}

// Hàm hiển thị danh sách sinh viên dựa trên cấu trúc dữ liệu đã chọn
void displayCurrentList(int dataStructureType,
                        const ArrayStudentList &arrayList,
                        NodeSLL *singlyLinkedList,
                        NodeSLL *circularLinkedList,
                        NodeDLL *doublyLinkedListHead,
                        NodeBST *binarySearchTree)
{
    switch (dataStructureType)
    {
    case 1: // Mảng
        displayArrayList(arrayList);
        break;
    case 2: // Danh sách liên kết đơn
        displaySLL(singlyLinkedList);
        break;
    case 3: // Danh sách liên kết vòng
        displayCLL(circularLinkedList);
        break;
    case 4: // Danh sách liên kết đôi
        displayDLL(doublyLinkedListHead);
        break;
    case 5: // Cây nhị phân tìm kiếm
        inorderTraversal(binarySearchTree);
        break;
    default:
        cout << "Cấu trúc dữ liệu không hợp lệ!" << endl;
        break;
    }
}

// Hàm thực hiện thống kê sinh viên dựa trên điểm số
void performStatistics(int dataStructureType, const ArrayStudentList &arrayList)
{
    if (dataStructureType == 1 && arrayList.count > 0)
    {
        float minScore = 10.0;
        float maxScore = 0.0;
        float totalScore = 0.0;

        // Tìm điểm thấp nhất, cao nhất và tính tổng điểm
        for (int i = 0; i < arrayList.count; i++)
        {
            float score = arrayList.students[i].score;
            if (score < minScore)
                minScore = score;
            if (score > maxScore)
                maxScore = score;
            totalScore += score;
        }

        float avgScore = totalScore / arrayList.count;

        // Hiển thị dashboard thống kê
        clearScreen();
        printHeader("THỐNG KÊ ĐIỂM SỐ SINH VIÊN");
        displayStatsDashboard(minScore, maxScore, avgScore, arrayList.count);

        // Hiển thị sinh viên có điểm thấp nhất
        cout << endl;
        printSubHeader("SINH VIÊN CÓ ĐIỂM THẤP NHẤT");
        displayStudentTableHeader();
        int minCount = 0;
        for (int i = 0; i < arrayList.count; i++)
        {
            if (arrayList.students[i].score == minScore)
            {
                displayStudentRow(arrayList.students[i], minCount++);
            }
        }
        displayStudentTableFooter();

        // Hiển thị sinh viên có điểm cao nhất
        cout << endl;
        printSubHeader("SINH VIÊN CÓ ĐIỂM CAO NHẤT");
        displayStudentTableHeader();
        int maxCount = 0;
        for (int i = 0; i < arrayList.count; i++)
        {
            if (arrayList.students[i].score == maxScore)
            {
                displayStudentRow(arrayList.students[i], maxCount++);
            }
        }
        displayStudentTableFooter();
    }
    else
    {
        clearScreen();
        printHeader("THỐNG KÊ ĐIỂM SỐ SINH VIÊN");
        displayEmptyMessage("Không có sinh viên để thống kê hoặc cấu trúc dữ liệu không hỗ trợ chức năng này!");
    }
}

// Hàm sắp xếp danh sách sinh viên theo điểm số
bool sortStudentList(int dataStructureType, int sortAlgorithm,
                     ArrayStudentList &arrayList,
                     NodeDLL *&doublyLinkedListHead)
{
    if (dataStructureType == 1)
    { // Mảng
        switch (sortAlgorithm)
        {
        case 1: // Bubble Sort
            bubbleSortArrayList(arrayList);
            break;
        case 2: // Selection Sort
            selectionSortArrayList(arrayList);
            break;
        case 3: // Insertion Sort
            insertionSortArrayList(arrayList);
            break;
        case 4: // Quick Sort
            quickSortArrayList(arrayList);
            break;
        case 5: // Merge Sort
            // mergeSort for array list - not implemented directly in the header
            cout << "Merge Sort for array list not implemented" << endl;
            break;
        default:
            return false;
        }
        return true;
    }
    else if (dataStructureType == 4)
    { // Danh sách liên kết đôi
        // Các thuật toán sắp xếp cho danh sách liên kết đôi
        // Có thể triển khai sau nếu cần
        return false;
    }

    return false;
}

// Hàm xử lý nhập dữ liệu từ file CSV
bool handleInputFromCSV(int dataStructureType,
                        ArrayStudentList &arrayList,
                        NodeSLL *&singlyLinkedList,
                        NodeSLL *&circularLinkedList,
                        NodeDLL *&doublyLinkedListHead,
                        NodeDLL *&doublyLinkedListTail,
                        NodeBST *&binarySearchTree)
{
    ifstream file("students.csv");
    if (!file.is_open())
    {
        cout << "Không thể mở file students.csv!" << endl;
        return false;
    }

    string line;
    int successCount = 0;
    int failCount = 0;

    // Đọc và bỏ qua dòng tiêu đề nếu có
    getline(file, line);

    // Đọc từng dòng trong file CSV
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        // Tách thông tin sinh viên từ dòng CSV
        Student student;
        size_t pos = 0;
        string token;
        string delimiter = ",";

        // Mã sinh viên
        pos = line.find(delimiter);
        if (pos == string::npos)
            continue;
        token = line.substr(0, pos);
        strcpy(student.studentID, token.c_str());
        line.erase(0, pos + delimiter.length());

        // Họ
        pos = line.find(delimiter);
        if (pos == string::npos)
            continue;
        token = line.substr(0, pos);
        strcpy(student.firstName, token.c_str());
        line.erase(0, pos + delimiter.length());

        // Tên
        pos = line.find(delimiter);
        if (pos == string::npos)
            continue;
        token = line.substr(0, pos);
        strcpy(student.lastName, token.c_str());
        line.erase(0, pos + delimiter.length());

        // Lớp
        pos = line.find(delimiter);
        if (pos == string::npos)
            continue;
        token = line.substr(0, pos);
        strcpy(student.studentClass, token.c_str());
        line.erase(0, pos + delimiter.length());

        // Điểm số
        try
        {
            student.score = stof(line);
        }
        catch (const exception &e)
        {
            failCount++;
            continue;
        }

        // Thêm sinh viên vào cấu trúc dữ liệu
        if (addStudentToDataStructure(student, dataStructureType, arrayList, singlyLinkedList,
                                      circularLinkedList, doublyLinkedListHead,
                                      doublyLinkedListTail, binarySearchTree))
        {
            successCount++;
        }
        else
        {
            failCount++;
        }
    }

    file.close();

    cout << "Đã nhập " << successCount << " sinh viên thành công từ file CSV." << endl;
    if (failCount > 0)
    {
        cout << "Có " << failCount << " dòng dữ liệu không hợp lệ hoặc trùng lặp." << endl;
    }

    return successCount > 0;
}

// Hàm để khởi tạo tất cả các cấu trúc dữ liệu
void initAllDataStructures(ArrayStudentList &arrayList,
                           NodeSLL *&singlyLinkedList,
                           NodeSLL *&circularLinkedList,
                           NodeDLL *&doublyLinkedListHead,
                           NodeDLL *&doublyLinkedListTail,
                           NodeBST *&binarySearchTree)
{
    // Khởi tạo mảng
    initArrayList(arrayList);

    // Khởi tạo danh sách liên kết đơn
    initSLL(singlyLinkedList);

    // Khởi tạo danh sách liên kết vòng
    initCLL(circularLinkedList);

    // Khởi tạo danh sách liên kết đôi
    initDLL(doublyLinkedListHead, doublyLinkedListTail);

    // Khởi tạo cây nhị phân tìm kiếm (binarySearchTree = NULL)
    binarySearchTree = NULL;
}

// Hàm thoát chương trình, giải phóng bộ nhớ
void exitProgram(NodeSLL *&singlyLinkedList,
                 NodeSLL *&circularLinkedList,
                 NodeDLL *&doublyLinkedListHead,
                 NodeDLL *&doublyLinkedListTail,
                 NodeBST *&binarySearchTree)
{
    // Giải phóng bộ nhớ cho danh sách liên kết đơn
    freeSLL(singlyLinkedList);

    // Giải phóng bộ nhớ cho danh sách liên kết vòng
    freeCLL(circularLinkedList);

    // Giải phóng bộ nhớ cho danh sách liên kết đôi
    freeDLL(doublyLinkedListHead, doublyLinkedListTail);

    // Giải phóng bộ nhớ cho cây nhị phân tìm kiếm
    freeBST(binarySearchTree);

    cout << "Cảm ơn bạn đã sử dụng chương trình!" << endl;
}

// Function moved to ui_common.cpp
