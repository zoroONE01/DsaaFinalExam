#include "../../include/utils/student_input.h"
#include "../../include/utils/validation.h"
#include "../../include/utils/utils.h"
#include "../../include/ui/ui_common.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

// Hàm nhập thông tin sinh viên từ bàn phím
bool inputStudent(Student &student)
{
    string tempInput;
    bool isValid;

    // Thông báo về cách hủy bỏ nhập liệu
    printInfo("Lưu ý: Nhập \"00\" để hủy bỏ và trở về menu chính.");

    // Kiểm tra nếu mã sinh viên đã được nhập trước đó
    if (student.studentID[0] == '\0')
    {
        // Nhập mã sinh viên nếu chưa có
        if (!inputStudentID(student.studentID))
        {
            return false; // Người dùng đã hủy bỏ
        }
    }

    // Nhập họ
    do
    {
        cout << "Nhập họ: ";
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

        if (tempInput.empty())
        {
            printError("Họ không được để trống.");
            isValid = false;
        }
        else
        {
            isValid = true;
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

        if (tempInput.empty())
        {
            printError("Tên không được để trống.");
            isValid = false;
        }
        else
        {
            isValid = true;
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

        if (tempInput.empty())
        {
            printError("Lớp không được để trống.");
            isValid = false;
        }
        else
        {
            isValid = true;
            strcpy(student.studentClass, tempInput.c_str());
        }
    } while (!isValid);

    // Nhập điểm số
    if (!inputStudentScore(student.score))
    {
        student.studentID[0] = '\0'; // Đánh dấu là đã hủy bỏ
        return false;
    }

    return true;
}

// Hàm nhập mã sinh viên từ bàn phím
bool inputStudentID(char *studentID)
{
    string tempInput;
    bool isValid;

    // Thông báo về cách hủy bỏ nhập liệu
    printInfo("Lưu ý: Nhập \"00\" để hủy bỏ và trở về menu chính.");

    do
    {
        cout << "Nhập mã sinh viên: ";
        cin >> tempInput;
        cin.ignore();
        tempInput = trim(tempInput); // Trim input

        // Kiểm tra hủy bỏ
        if (tempInput == "00")
        {
            if (confirmCancel())
            {
                studentID[0] = '\0'; // Đánh dấu là đã hủy bỏ bằng chuỗi rỗng
                return false;
            }
            continue;
        }

        // Kiểm tra tính hợp lệ - giả sử luôn hợp lệ trong ví dụ này
        isValid = true;
        if (isValid)
        {
            strcpy(studentID, tempInput.c_str());
        }
    } while (!isValid);

    return true;
}

// Hàm nhập điểm số sinh viên từ bàn phím
bool inputStudentScore(float &score)
{
    string scoreInput;
    bool isValid;

    do
    {
        cout << "Nhập điểm (0-10): ";
        cin >> scoreInput;

        // Kiểm tra hủy bỏ (phân biệt với giá trị điểm 0)
        if (scoreInput == "00")
        {
            cin.ignore();
            if (confirmCancel())
            {
                return false;
            }
            continue;
        }

        // Chuyển đổi thành số
        try
        {
            score = stof(scoreInput);
            isValid = (score >= 0 && score <= 10);

            if (!isValid)
            {
                printError("Điểm số phải nằm trong khoảng từ 0 đến 10.");
            }
        }
        catch (...)
        {
            isValid = false;
            printError("Điểm số không hợp lệ. Vui lòng nhập một số.");
        }
    } while (!isValid);

    cin.ignore();
    return true;
}

// Hàm đọc dữ liệu sinh viên từ file CSV
bool readStudentsFromCSV(const char *filename, ArrayStudentList &list)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    string line;
    // Bỏ qua dòng tiêu đề nếu có
    getline(file, line);

    // Reset danh sách
    list.count = 0;

    // Đọc từng dòng
    while (getline(file, line) && list.count < MAX_STUDENTS)
    {
        Student student;
        string studentID, firstName, lastName, studentClass, scoreStr;

        // Tách các trường dữ liệu bằng dấu phẩy
        size_t pos = 0;
        string token;

        // Tách mã sinh viên
        pos = line.find(',');
        if (pos == string::npos)
            continue; // Dòng không hợp lệ
        studentID = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Tách họ
        pos = line.find(',');
        if (pos == string::npos)
            continue; // Dòng không hợp lệ
        firstName = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Tách tên
        pos = line.find(',');
        if (pos == string::npos)
            continue; // Dòng không hợp lệ
        lastName = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Tách lớp
        pos = line.find(',');
        if (pos == string::npos)
            continue; // Dòng không hợp lệ
        studentClass = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Phần còn lại là điểm
        scoreStr = line;

        // Chuyển đổi và gán vào struct Student
        strcpy(student.studentID, trim(studentID).c_str());
        strcpy(student.firstName, trim(firstName).c_str());
        strcpy(student.lastName, trim(lastName).c_str());
        strcpy(student.studentClass, trim(studentClass).c_str());

        try
        {
            student.score = stof(trim(scoreStr));
            // Kiểm tra điểm có hợp lệ không
            if (student.score < 0 || student.score > 10)
            {
                continue; // Bỏ qua dòng này nếu điểm không hợp lệ
            }
        }
        catch (...)
        {
            continue; // Bỏ qua dòng này nếu không thể chuyển đổi điểm
        }

        // Thêm sinh viên vào danh sách
        list.students[list.count++] = student;
    }

    file.close();
    return true;
}
