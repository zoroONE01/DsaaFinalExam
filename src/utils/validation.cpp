#include "../../include/utils/validation.h"
#include "../../include/utils/student.h"
#include "../../include/data_structures/array_list.h"
#include "../../include/data_structures/singly_linked_list.h"
#include "../../include/data_structures/circular_linked_list.h"
#include "../../include/data_structures/doubly_linked_list.h"
#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

// Hàm validate mã sinh viên
bool validateStudentID(const string &studentID)
{
    // Kiểm tra độ dài mã sinh viên (ví dụ: từ 5 đến 10 ký tự)
    if (studentID.length() < 5 || studentID.length() > 10)
    {
        return false;
    }

    // Kiểm tra các ký tự hợp lệ (ví dụ: chỉ chấp nhận chữ và số)
    for (char c : studentID)
    {
        if (!isalnum(c))
        {
            return false;
        }
    }

    return true;
}

// Hàm validate họ tên sinh viên
bool validateName(const string &name)
{
    // Kiểm tra độ dài họ tên
    if (name.empty() || name.length() > 50)
    {
        return false;
    }

    // Kiểm tra các ký tự hợp lệ (chữ cái, dấu cách, dấu chấm)
    for (char c : name)
    {
        if (!isalpha(c) && c != ' ' && c != '.')
        {
            return false;
        }
    }

    return true;
}

// Hàm validate lớp học
bool validateClass(const string &className)
{
    // Kiểm tra độ dài mã lớp
    if (className.empty() || className.length() > 20)
    {
        return false;
    }

    // Kiểm tra các ký tự hợp lệ (chữ cái, số, dấu gạch ngang)
    for (char c : className)
    {
        if (!isalnum(c) && c != '-')
        {
            return false;
        }
    }

    return true;
}

// Hàm validate điểm số
bool validateScore(const string &scoreStr, float &score)
{
    try
    {
        // Chuyển đổi chuỗi thành số thực
        score = stof(scoreStr);

        // Kiểm tra phạm vi điểm hợp lệ (0-10)
        if (score < 0.0 || score > 10.0)
        {
            return false;
        }

        return true;
    }
    catch (const exception &e)
    {
        return false;
    }
}

// Kiểm tra và hiển thị thông báo về mã sinh viên
bool validateAndShowStudentID(const string &studentID)
{
    if (!validateStudentID(studentID))
    {
        cout << "Mã sinh viên không hợp lệ. Mã sinh viên phải có từ 5-10 ký tự và chỉ chứa chữ và số." << endl;
        return false;
    }
    return true;
}

// Kiểm tra trùng lặp mã sinh viên trong các cấu trúc dữ liệu
bool validateAndShowDuplicateStudentID(
    const string &studentID,
    int dataStructureType,
    const struct ArrayStudentList &arrayList,
    struct NodeSLL *singlyLinkedList,
    struct NodeSLL *circularLinkedList,
    struct NodeDLL *doublyLinkedListHead)
{
    // Kiểm tra mảng sinh viên
    if (dataStructureType != 1)
    { // Không kiểm tra trùng lặp đối với cấu trúc dữ liệu đang sử dụng
        for (int i = 0; i < arrayList.count; i++)
        {
            if (strcmp(arrayList.students[i].studentID, studentID.c_str()) == 0)
            {
                cout << "Mã sinh viên đã tồn tại trong danh sách mảng!" << endl;
                return false;
            }
        }
    }

    // Kiểm tra danh sách liên kết đơn
    if (dataStructureType != 2)
    {
        NodeSLL *current = singlyLinkedList;
        while (current != NULL)
        {
            if (strcmp(current->info.studentID, studentID.c_str()) == 0)
            {
                cout << "Mã sinh viên đã tồn tại trong danh sách liên kết đơn!" << endl;
                return false;
            }
            current = current->next;
        }
    }

    // Kiểm tra danh sách liên kết vòng
    if (dataStructureType != 3 && circularLinkedList != NULL)
    {
        NodeSLL *current = circularLinkedList;
        do
        {
            if (strcmp(current->info.studentID, studentID.c_str()) == 0)
            {
                cout << "Mã sinh viên đã tồn tại trong danh sách liên kết vòng!" << endl;
                return false;
            }
            current = current->next;
        } while (current != circularLinkedList);
    }

    // Kiểm tra danh sách liên kết đôi
    if (dataStructureType != 4)
    {
        NodeDLL *current = doublyLinkedListHead;
        while (current != NULL)
        {
            if (strcmp(current->info.studentID, studentID.c_str()) == 0)
            {
                cout << "Mã sinh viên đã tồn tại trong danh sách liên kết đôi!" << endl;
                return false;
            }
            current = current->next;
        }
    }

    return true;
}
