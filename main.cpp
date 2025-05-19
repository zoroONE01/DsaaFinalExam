#include <iostream>
#include <cstring>
#include <limits>
#include <fstream>
#include "libs/student/student_library.h"
#include "libs/knights_tour/knights_tour.h"
#include "libs/ui/common_ui.h" // Thư viện UI

using namespace std;

// Biến lưu trữ dữ liệu cho từng loại cấu trúc dữ liệu
ArrayStudentList arrayList;
NodeSLL *singlyLinkedList = NULL;
NodeSLL *circularLinkedList = NULL;
NodeDLL *doublyLinkedListHead = NULL;
NodeDLL *doublyLinkedListTail = NULL;
NodeBST *binarySearchTree = NULL;

int main()
{
    // Khởi tạo các cấu trúc dữ liệu
    initAllDataStructures(arrayList, singlyLinkedList, circularLinkedList, doublyLinkedListHead, doublyLinkedListTail, binarySearchTree);

    int dataStructureType = ARRAY_LIST; // Mặc định sử dụng danh sách mảng
    int choice;

    do
    {
        displayMainMenu(dataStructureType);

        if (!(cin >> choice))
        {
            printError("Lựa chọn không hợp lệ. Vui lòng nhập lại.");
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
            handleInputFromCSV(dataStructureType, arrayList, singlyLinkedList, circularLinkedList,
                               doublyLinkedListHead, doublyLinkedListTail, binarySearchTree);
            break;
        case 3:
        {
            Student student;
            if (inputStudent(student))
            {
                addStudentToDataStructure(student, dataStructureType, arrayList, singlyLinkedList,
                                          circularLinkedList, doublyLinkedListHead, doublyLinkedListTail,
                                          binarySearchTree);
            }
            break;
        }
        case 4:
        {
            char studentID[20];
            if (inputStudentID(studentID))
            {
                deleteStudentFromDataStructure(studentID, dataStructureType, arrayList, singlyLinkedList,
                                               circularLinkedList, doublyLinkedListHead, doublyLinkedListTail);
            }
            break;
        }
        case 5:
        {
            char studentID[20];
            if (inputStudentID(studentID))
            {
                // Kiểm tra xem sinh viên có tồn tại không
                bool exists = isStudentExists(studentID, dataStructureType, arrayList, singlyLinkedList,
                                              circularLinkedList, doublyLinkedListHead);

                if (exists)
                {
                    cout << "Nhập thông tin mới cho sinh viên:\n";
                    Student updateStudent;
                    if (inputStudent(updateStudent))
                    {
                        strcpy(updateStudent.studentID, studentID); // Giữ nguyên mã sinh viên
                        updateStudentInDataStructure(updateStudent, dataStructureType, arrayList, singlyLinkedList,
                                                     circularLinkedList, doublyLinkedListHead);
                    }
                }
                else
                {
                    printError(("Không tìm thấy sinh viên có mã " + string(studentID) + ".").c_str());
                }
            }
            break;
        }
        case 6:
            displayCurrentList(dataStructureType, arrayList, singlyLinkedList, circularLinkedList,
                               doublyLinkedListHead, binarySearchTree);
            break;
        case 7:
        {
            char studentID[20];
            if (inputStudentID(studentID))
            {
                searchStudentInDataStructure(studentID, dataStructureType, arrayList, singlyLinkedList,
                                             circularLinkedList, doublyLinkedListHead);
            }
            break;
        }
        case 8:
            performStatistics(dataStructureType, arrayList);
            break;
        case 9:
        {
            int sortAlgorithm = selectSortAlgorithm(dataStructureType);
            if (sortAlgorithm != -1)
            {
                sortStudentList(dataStructureType, sortAlgorithm, arrayList, doublyLinkedListHead);
            }
            break;
        }
        case 10:
            clearScreen();
            printHeader("BÀI TOÁN MÃ ĐI TUẦN");
            knightsTour();
            break;
        case 0:
            exitProgram(singlyLinkedList, circularLinkedList, doublyLinkedListHead,
                        doublyLinkedListTail, binarySearchTree);
            break;
        default:
            printError("Lựa chọn không hợp lệ. Vui lòng nhập lại.");
        }

        // Nếu không phải menu lựa chọn hoặc trợ giúp, chờ người dùng nhấn Enter để tiếp tục
        if (choice != 0 && choice != 1)
        {
            cout << "\nNhấn Enter để tiếp tục...";
            cin.get();
        }
    } while (choice != 0);

    return 0;
}