#include "../../include/utils/utils.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <limits>
#include <iomanip>

using namespace std;

// Hàm phụ trợ để kiểm tra ký tự không phải khoảng trắng
bool notSpace(unsigned char ch)
{
    return !isspace(ch);
}

// Hàm xóa khoảng trắng thừa ở hai đầu chuỗi
string trim(const string &str)
{
    string s = str;
    // Xóa khoảng trắng ở đầu
    s.erase(s.begin(), find_if(s.begin(), s.end(), notSpace));

    // Xóa khoảng trắng ở cuối
    s.erase(find_if(s.rbegin(), s.rend(), notSpace).base(), s.end());

    return s;
}

// Tính độ rộng hiển thị thực tế của chuỗi UTF-8
int visualWidth(const string &str)
{
    int width = 0;

    // Duyệt qua từng byte trong chuỗi
    for (size_t i = 0; i < str.length(); i++)
    {
        unsigned char c = str[i];

        // Kiểm tra byte đầu tiên của mã UTF-8
        if ((c & 0x80) == 0)
        {
            // Ký tự ASCII (0xxxxxxx) - độ rộng 1
            width++;
        }
        else if ((c & 0xE0) == 0xC0)
        {
            // Chuỗi 2 byte (110xxxxx 10xxxxxx) - độ rộng 1
            i++; // Bỏ qua byte tiếp theo
            width++;
        }
        else if ((c & 0xF0) == 0xE0)
        {
            // Chuỗi 3 byte (1110xxxx 10xxxxxx 10xxxxxx) - độ rộng 2
            i += 2; // Bỏ qua 2 byte tiếp theo
            width++;
        }
        else if ((c & 0xF8) == 0xF0)
        {
            // Chuỗi 4 byte (11110xxx 10xxxxxx 10xxxxxx 10xxxxxx) - độ rộng 2
            i += 3; // Bỏ qua 3 byte tiếp theo
            width++;
        }
    }

    return width;
}

// Hàm chuyển đổi chuỗi thành chữ hoa
string toUpperCase(const string &str)
{
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// Hàm chuyển đổi chuỗi thành chữ thường
string toLowerCase(const string &str)
{
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Hàm xóa buffer đầu vào
void clearInputBuffer()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Hiển thị thông tin một sinh viên
void displayStudent(const Student &student)
{
    cout << left << setw(10) << student.studentID
         << setw(20) << student.firstName
         << setw(20) << student.lastName
         << setw(15) << student.studentClass
         << setw(5) << student.score << endl;
}
