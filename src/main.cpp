#include <iostream>
#include <cstring>
#include <limits>
#include <fstream>
#include <chrono>
#include "../include/student_library.h"

using namespace std;

// Biến lưu trữ dữ liệu cho từng loại cấu trúc dữ liệu

// Biến lưu trữ danh sách mảng
ArrayStudentList arrayList;

// Biến lưu trữ đầu và đuôi của danh sách liên kết đơn
NodeSLL *singlyLinkedList = NULL;

// Biến lưu trữ đầu của danh sách liên kết vòng
NodeSLL *circularLinkedList = NULL;

// Biến lưu trữ đầu và đuôi của danh sách liên kết đôi
NodeDLL *doublyLinkedListHead = NULL;
NodeDLL *doublyLinkedListTail = NULL;

// Biến lưu trữ cây tìm kiếm nhị phân
NodeBST *binarySearchTree = NULL;

// Biến lưu trữ trạng thái sắp xếp hiện tại
int currentSortCriteria = -1; // -1 means not sorted
bool isSorted = false;

void displayBSTMenu()
{
    clearScreen();
    printHeader("MENU CÂY TÌM KIẾM NHỊ PHÂN");
    cout << "1. Thêm nút vào cây" << endl;
    cout << "2. Xóa nút khỏi cây (theo điểm số)" << endl;
    cout << "3. Cập nhật nút trong cây" << endl;
    cout << "4. Hiển thị cây (dạng danh sách liên kết)" << endl;
    cout << "5. Nhập dữ liệu từ file CSV" << endl;
    cout << "6. Quay lại menu chính" << endl;
    cout << "0. Thoát" << endl;
}

int performBSTOperations(NodeBST *&binarySearchTree, ArrayStudentList &arrayList)
{
    int choice;
    do
    {
        displayBSTMenu();

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
        case 1: // Thêm nút vào cây
        {
            clearScreen();
            printHeader("THÊM NÚT VÀO CÂY");
            printInfo("Lưu ý: Nhập \"00\" để hủy bỏ và trở về menu trước.");

            char studentID[MAX_STUDENT_ID_LENGTH];
            // Bước 1: Nhập và kiểm tra mã sinh viên
            string tempID;
            bool isValid;

            // Nhập và kiểm tra mã sinh viên
            do
            {
                cout << "Nhập mã sinh viên: ";
                cin >> tempID;
                clearInputBuffer();
                tempID = trim(tempID);

                // Kiểm tra hủy bỏ
                if (tempID == CANCEL_INPUT_CODE)
                {
                    if (confirmCancel())
                    {
                        break;
                    }
                    continue;
                }

                // Kiểm tra định dạng mã sinh viên
                isValid = validateAndShowStudentID(tempID);

                // Nếu định dạng hợp lệ, kiểm tra trùng lặp
                if (isValid)
                {
                    isValid = validateAndShowDuplicateStudentID(tempID, BINARY_SEARCH_TREE, arrayList, singlyLinkedList,
                                                                circularLinkedList, doublyLinkedListHead, binarySearchTree);
                }
            } while (!isValid);

            // Nếu người dùng chọn hủy bỏ
            if (tempID == CANCEL_INPUT_CODE)
            {
                break;
            }

            // Lưu mã sinh viên hợp lệ
            strcpy(studentID, tempID.c_str());

            // Bước 2: Tiếp tục nhập thông tin chi tiết
            Student student;
            strcpy(student.studentID, studentID); // Đặt mã sinh viên đã nhập

            isValid = inputStudent(student);

            if (isValid)
            {
                // Thêm sinh viên vào cây tìm kiếm nhị phân
                addStudentToBST(student, binarySearchTree);

                printSuccess("Thêm sinh viên thành công vào cây.");
            }
            break;
        }
        case 2: // Xóa nút khỏi cây
        {
            deleteNodeFromBSTByKey(binarySearchTree);
            break;
        }
        case 3: // Cập nhật nút trong cây
        {
            clearScreen();
            printHeader("CẬP NHẬT NÚT TRONG CÂY");
            printInfo("Lưu ý: Nhập \"00\" để hủy bỏ và trở về menu trước.");

            char studentID[MAX_STUDENT_ID_LENGTH];
            if (inputStudentID(studentID))
            {
                Student currentStudent;
                // Lấy thông tin sinh viên hiện tại từ cây
                if (getStudentFromBST(studentID, binarySearchTree, currentStudent))
                {
                    Student updateStudent = currentStudent; // Bắt đầu với thông tin hiện tại

                    if (inputStudentForUpdate(updateStudent))
                    {
                        updateStudentInBST(updateStudent, binarySearchTree);
                    }
                }
                else
                {
                    printError(("Không tìm thấy sinh viên có mã " + string(studentID) + " trong cây.").c_str());
                }
            }
            break;
        }
        case 4: // Hiển thị cây (dạng danh sách liên kết)
            displayBST(binarySearchTree);
            break;
        case 5: // Nhập dữ liệu từ file CSV
        {
            clearScreen();
            printHeader("NHẬP DỮ LIỆU TỪ FILE CSV VÀO CÂY BST");
            printInfo("Lưu ý: Nhập \"00\" để hủy bỏ và trở về menu trước.");

            string filePathStr;
            cout << "\nNhập đường dẫn đến file CSV (nhấn Enter để dùng mặc định 'data/students.csv'): ";

            // Xử lý newline dư thừa nếu có
            if (cin.peek() == '\n')
            {
                cin.ignore();
            }
            getline(cin, filePathStr);
            filePathStr = trim(filePathStr);

            // Kiểm tra hủy bỏ
            if (filePathStr == "00")
            {
                if (confirmCancel())
                {
                    printInfo("Đã hủy thao tác nhập từ file CSV.");
                    break;
                }
                // Nếu không xác nhận hủy, nhập lại
                cout << "\nNhập lại đường dẫn đến file CSV (nhấn Enter để dùng mặc định 'data/students.csv'): ";
                getline(cin, filePathStr);
                filePathStr = trim(filePathStr);
                if (filePathStr == "00")
                {
                    printInfo("Đã hủy thao tác nhập từ file CSV.");
                    break;
                }
            }

            // Sử dụng đường dẫn mặc định nếu để trống
            if (filePathStr.empty())
            {
                filePathStr = "data/students.csv";
            }

            // Gọi hàm nhập dữ liệu từ CSV vào BST
            handleInputFromCSV(filePathStr.c_str(), BINARY_SEARCH_TREE, arrayList,
                               singlyLinkedList, circularLinkedList, doublyLinkedListHead, doublyLinkedListTail, binarySearchTree);
            break;
        }
        case 6: // Quay lại menu chính
        {
            // Chuyển đổi dữ liệu từ BST về Array List
            clearScreen();
            printHeader("CHUYỂN ĐỔI DỮ LIỆU");
            printInfo("Đang chuyển đổi dữ liệu từ cây tìm kiếm nhị phân về danh sách mảng...");

            convertBSTToArrayList(binarySearchTree, arrayList);

            printSuccess("Đã chuyển đổi dữ liệu thành công về danh sách mảng.");
            printInfo("Bạn sẽ được chuyển về menu chính với cấu trúc dữ liệu: Danh sách mảng");

            cout << "\nNhấn Enter để tiếp tục...";
            cin.get();
            return ARRAY_LIST; // Trả về mã của Array List
        }
        case 0:
            exitProgram(singlyLinkedList, circularLinkedList, doublyLinkedListHead,
                        doublyLinkedListTail, binarySearchTree);
            return BINARY_SEARCH_TREE; // Vẫn ở BST khi thoát chương trình
            break;
        default:
            printError("Lựa chọn không hợp lệ. Vui lòng nhập lại.");
        }

        // Nếu không phải menu lựa chọn hoặc trợ giúp, chờ người dùng nhấn Enter để tiếp tục
        if (choice != 0 && choice != 6)
        {
            cout << "\nNhấn Enter để tiếp tục...";
            cin.get();
        }
    } while (choice != 0 && choice != 6);

    return BINARY_SEARCH_TREE; // Mặc định trả về BST nếu không có trường hợp đặc biệt
}

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
        case 1: // Chọn cấu trúc dữ liệu
            dataStructureType = selectDataStructureWithBSTHandling(dataStructureType, arrayList, singlyLinkedList, circularLinkedList, doublyLinkedListHead, binarySearchTree);
            break;
        case 2:
        {
            string filePathStr;
            // Thông báo về cách hủy bỏ nhập liệu
            printInfo("Lưu ý: Nhập \"00\" để hủy bỏ và trở về menu chính.");

            cout << "\nNhập đường dẫn đến file CSV (nhấn Enter để dùng mặc định 'data/students.csv'): ";

            // Handle potential leftover newline from previous cin >> operations
            if (cin.peek() == '\n')
            {
                cin.ignore();
            }
            getline(cin, filePathStr);
            filePathStr = trim(filePathStr); // Trim input

            if (filePathStr == "00")
            {
                if (confirmCancel())
                {
                    printInfo("Đã hủy thao tác nhập từ file CSV.");
                    break;
                }
                // If not confirmed, re-prompt
                cout << "\nNhập lại đường dẫn đến file CSV (nhấn Enter để dùng mặc định 'data/students.csv'): ";
                if (cin.peek() == '\n')
                {
                    cin.ignore();
                }
                getline(cin, filePathStr);
                filePathStr = trim(filePathStr);
                if (filePathStr == "00")
                {
                    printInfo("Đã hủy thao tác nhập từ file CSV.");
                    break;
                }
            }

            if (filePathStr.empty())
            {
                filePathStr = "data/students.csv"; // Default path
            }

            handleInputFromCSV(filePathStr.c_str(), dataStructureType, arrayList, singlyLinkedList, circularLinkedList,
                               doublyLinkedListHead, doublyLinkedListTail, binarySearchTree);

            // Reset sort state after loading new data
            currentSortCriteria = -1;
            isSorted = false;
            break;
        }
        case 3:
        {

            clearScreen();
            printHeader("THÊM SINH VIÊN MỚI");
            printInfo("Lưu ý: Nhập \"00\" để hủy bỏ và trở về menu chính.");

            char studentID[MAX_STUDENT_ID_LENGTH];
            // Bước 1: Nhập và kiểm tra mã sinh viên
            string tempID;
            bool isValid;

            // Nhập và kiểm tra mã sinh viên
            do
            {
                cout << "Nhập mã sinh viên: ";
                cin >> tempID;
                clearInputBuffer();
                tempID = trim(tempID);

                // Kiểm tra hủy bỏ
                if (tempID == CANCEL_INPUT_CODE)
                {
                    if (confirmCancel())
                    {
                        break;
                    }
                    continue;
                }

                // Kiểm tra định dạng mã sinh viên
                isValid = validateAndShowStudentID(tempID);

                // Nếu định dạng hợp lệ, kiểm tra trùng lặp
                if (isValid)
                {
                    isValid = validateAndShowDuplicateStudentID(tempID, dataStructureType, arrayList, singlyLinkedList,
                                                                circularLinkedList, doublyLinkedListHead, binarySearchTree);
                }
            } while (!isValid);

            // Nếu người dùng chọn hủy bỏ
            if (tempID == CANCEL_INPUT_CODE)
            {
                break;
            }

            // Lưu mã sinh viên hợp lệ
            strcpy(studentID, tempID.c_str());

            // Bước 2: Tiếp tục nhập thông tin chi tiết
            Student student;
            strcpy(student.studentID, studentID); // Đặt mã sinh viên đã nhập

            isValid = inputStudent(student);

            if (isValid)
            {
                addStudentToDataStructure(student, dataStructureType, arrayList, singlyLinkedList,
                                          circularLinkedList, doublyLinkedListHead, doublyLinkedListTail,
                                          binarySearchTree);

                // Reset sort state after adding new student
                currentSortCriteria = -1;
                isSorted = false;
            }
            break;
        }
        case 4: // Xóa sinh viên theo mã
        {
            char studentID[MAX_STUDENT_ID_LENGTH];
            if (inputStudentID(studentID))
            {
                deleteStudentFromDataStructure(studentID, dataStructureType, arrayList, singlyLinkedList,
                                               circularLinkedList, doublyLinkedListHead, doublyLinkedListTail);

                // Reset sort state after deleting student
                currentSortCriteria = -1;
                isSorted = false;
            }
            break;
        }
        case 5: // Cập nhật sinh viên theo mã
        {
            clearScreen();
            printHeader("CẬP NHẬT SINH VIÊN");
            printInfo("Lưu ý: Nhập \"00\" để hủy bỏ và trở về menu chính.");

            char studentID[MAX_STUDENT_ID_LENGTH];
            if (inputStudentID(studentID))
            {
                Student currentStudent;
                // Lấy thông tin sinh viên hiện tại từ cấu trúc dữ liệu
                if (getStudentFromDataStructure(studentID, dataStructureType, arrayList, singlyLinkedList,
                                                circularLinkedList, doublyLinkedListHead, currentStudent))
                {
                    Student updateStudent = currentStudent; // Bắt đầu với thông tin hiện tại

                    if (inputStudentForUpdate(updateStudent))
                    {
                        updateStudentInDataStructure(updateStudent, dataStructureType, arrayList, singlyLinkedList,
                                                     circularLinkedList, doublyLinkedListHead);

                        // Reset sort state after updating student
                        currentSortCriteria = -1;
                        isSorted = false;
                    }
                }
                else
                {
                    printError(("Không tìm thấy sinh viên có mã " + string(studentID) + ".").c_str());
                }
            }
            break;
        }
        case 6: // Hiển thị danh sách sinh viên
            displayCurrentList(dataStructureType, arrayList, singlyLinkedList, circularLinkedList,
                               doublyLinkedListHead, binarySearchTree);
            break;
        case 7: // Thống kê sinh viên
            performStatistics(dataStructureType, arrayList, singlyLinkedList, circularLinkedList, doublyLinkedListHead);
            break;
        case 8: // Sắp xếp sinh viên theo tiêu chí
        {
            int sortAlgorithm = selectSortAlgorithm(dataStructureType);
            if (sortAlgorithm != -1)
            {
                int sortCriteria = selectSortCriteria();
                if (sortCriteria != -1)
                {
                    // Đo thời gian thực thi
                    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

                    bool success = sortStudentList(dataStructureType, sortAlgorithm, sortCriteria, arrayList,
                                                   singlyLinkedList, circularLinkedList, doublyLinkedListHead,
                                                   doublyLinkedListTail);

                    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
                    chrono::microseconds duration = chrono::duration_cast<chrono::microseconds>(end - start);

                    if (success)
                    {
                        // Update sort state for enhanced search optimization
                        currentSortCriteria = sortCriteria;
                        isSorted = true;

                        cout << BOLD << GREEN << "\n✓ Thời gian thực thi: " << duration.count() << " microseconds ("
                             << (double)duration.count() / 1000.0 << " ms)" << RESET << endl;
                    }
                }
            }
            break;
        }
        case 9: // Tìm kiếm nâng cao với nhiều tiêu chí
        {
            searchStudentInDataStructure(dataStructureType, arrayList, singlyLinkedList,
                                         circularLinkedList, doublyLinkedListHead,
                                         isSorted ? currentSortCriteria : -1);
            break;
        }
        case 10: // Xóa toàn bộ danh sách
        {
            if (clearAllData(dataStructureType, arrayList, singlyLinkedList, circularLinkedList,
                             doublyLinkedListHead, doublyLinkedListTail, binarySearchTree))
            {
                // Reset sort state after clearing all data
                currentSortCriteria = -1;
                isSorted = false;
            }
            break;
        }
        case 11: // Lưu danh sách ra file CSV
        {
            clearScreen();
            printHeader("LỮU DANH SÁCH RA FILE CSV");
            printInfo("Lưu ý: Nhập \"00\" để hủy bỏ và trở về menu chính.");

            string filePath;
            cout << "\nNhập đường dẫn file CSV để lưu (nhấn Enter để dùng mặc định 'data/export.csv'): ";

            // Handle potential leftover newline
            if (cin.peek() == '\n')
            {
                cin.ignore();
            }
            getline(cin, filePath);
            filePath = trim(filePath);

            // Kiểm tra hủy bỏ
            if (filePath == "00")
            {
                if (confirmCancel())
                {
                    printInfo("Đã hủy thao tác lưu file CSV.");
                    break;
                }
                // Nếu không xác nhận hủy, nhập lại
                cout << "\nNhập lại đường dẫn file CSV để lưu: ";
                getline(cin, filePath);
                filePath = trim(filePath);
                if (filePath == "00")
                {
                    printInfo("Đã hủy thao tác lưu file CSV.");
                    break;
                }
            }

            // Sử dụng đường dẫn mặc định nếu để trống
            if (filePath.empty())
            {
                filePath = "data/export.csv";
            }

            saveToCSVFile(filePath.c_str(), dataStructureType, arrayList, singlyLinkedList,
                          circularLinkedList, doublyLinkedListHead, binarySearchTree);
            break;
        }
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