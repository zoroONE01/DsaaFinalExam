#include "../../include/algorithms/search_utils.h"
#include "../../include/core/student.h"
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>
#include <chrono>

using namespace std;

/**
 * @brief Thực hiện so sánh chuỗi không phân biệt hoa thường
 *
 * @param str1 Chuỗi đầu tiên
 * @param str2 Chuỗi thứ hai
 * @return true nếu hai chuỗi giống nhau (không phân biệt hoa thường)
 */
bool compareStringsIgnoreCase(const char *str1, const char *str2)
{
    if (!str1 || !str2)
        return false;

    while (*str1 && *str2)
    {
        if (tolower(*str1) != tolower(*str2))
        {
            return false;
        }
        str1++;
        str2++;
    }
    return *str1 == *str2;
}

/**
 * @brief Kiểm tra chuỗi con có tồn tại trong chuỗi cha không (không phân biệt hoa thường)
 *
 * @param str Chuỗi cha
 * @param substring Chuỗi con cần tìm
 * @return true nếu tìm thấy chuỗi con
 */
bool containsSubstring(const char *str, const char *substring)
{
    if (!str || !substring)
        return false;
    if (strlen(substring) == 0)
        return true;

    int strLen = strlen(str);
    int subLen = strlen(substring);

    for (int i = 0; i <= strLen - subLen; i++)
    {
        bool match = true;
        for (int j = 0; j < subLen; j++)
        {
            if (tolower(str[i + j]) != tolower(substring[j]))
            {
                match = false;
                break;
            }
        }
        if (match)
            return true;
    }
    return false;
}

/**
 * @brief Kiểm tra sinh viên có khớp với tiêu chí tìm kiếm không
 *
 * @param student Thông tin sinh viên
 * @param keyword Từ khóa tìm kiếm
 * @param searchCriteria Tiêu chí tìm kiếm (1: ID, 2: Tên, 3: Họ, 4: Lớp, 5: Điểm)
 * @return true nếu sinh viên khớp với tiêu chí
 */
bool studentMatchesCriteria(const Student &student, const char *keyword, int searchCriteria)
{
    if (!keyword || strlen(keyword) == 0)
        return true;

    switch (searchCriteria)
    {
    case 1: // Student ID
        return containsSubstring(student.studentID, keyword);
    case 2: // First Name
        return containsSubstring(student.firstName, keyword);
    case 3: // Last Name
        return containsSubstring(student.lastName, keyword);
    case 4: // Class
        return containsSubstring(student.studentClass, keyword);
    case 5: // Score (convert keyword to float and check)
    {
        float searchScore = atof(keyword);
        return (student.score >= searchScore - 0.01 && student.score <= searchScore + 0.01);
    }
    default:
        return false;
    }
}

/**
 * @brief Đảo ngược chuỗi
 *
 * @param str Chuỗi cần đảo ngược
 * @return Con trỏ đến chuỗi đã đảo ngược (cần giải phóng bộ nhớ sau khi sử dụng)
 */
char* reverseString(const char* str)
{
    if (!str) return nullptr;
    
    int len = strlen(str);
    char* reversed = new char[len + 1];
    
    for (int i = 0; i < len; i++) {
        reversed[i] = str[len - 1 - i];
    }
    reversed[len] = '\0';
    
    return reversed;
}

/**
 * @brief Đảo ngược họ và tên đầy đủ
 *
 * @param firstName Tên
 * @param lastName Họ
 * @return Con trỏ đến chuỗi họ tên đã đảo ngược (cần giải phóng bộ nhớ sau khi sử dụng)
 */
char* reverseFullName(const char* firstName, const char* lastName)
{
    if (!firstName || !lastName) return nullptr;
    
    // Tạo chuỗi họ tên đầy đủ
    int totalLen = strlen(firstName) + strlen(lastName) + 2; // +2 cho dấu cách và null terminator
    char* fullName = new char[totalLen];
    strcpy(fullName, lastName);
    strcat(fullName, " ");
    strcat(fullName, firstName);
    
    // Đảo ngược chuỗi họ tên
    char* reversed = reverseString(fullName);
    
    // Giải phóng bộ nhớ tạm
    delete[] fullName;
    
    return reversed;
}

/**
 * @brief In văn bản với màu sắc nổi bật (đỏ và in đậm)
 *
 * @param text Văn bản cần in
 */
void printRedBold(const char* text)
{
    if (text) {
        cout << "\033[1;31m" << text << "\033[0m"; // Red bold text
    }
}

/**
 * @brief Đặt lại màu văn bản về mặc định
 */
void resetTextColor()
{
    cout << "\033[0m";
}

/**
 * @brief In văn bản với phần khớp được tô sáng
 *
 * @param text Văn bản gốc
 * @param keyword Từ khóa cần tô sáng
 * @param searchCriteria Tiêu chí tìm kiếm
 */
void printHighlighted(const char* text, const char* keyword, int searchCriteria)
{
    if (!text || !keyword) {
        cout << (text ? text : "");
        return;
    }
    
    string textStr(text);
    string keywordStr(keyword);
    
    // Chuyển thành chữ thường để so sánh
    string textLower = textStr;
    string keywordLower = keywordStr;
    
    for (size_t i = 0; i < textLower.length(); i++) {
        textLower[i] = tolower(textLower[i]);
    }
    for (size_t i = 0; i < keywordLower.length(); i++) {
        keywordLower[i] = tolower(keywordLower[i]);
    }
    
    // Tìm vị trí của từ khóa trong văn bản
    size_t pos = textLower.find(keywordLower);
    
    if (pos != string::npos) {
        // In phần trước từ khóa
        cout << textStr.substr(0, pos);
        
        // In từ khóa với màu đỏ và in đậm
        cout << "\033[1;31m" << textStr.substr(pos, keywordStr.length()) << "\033[0m";
        
        // In phần sau từ khóa
        cout << textStr.substr(pos + keywordStr.length());
    } else {
        // Nếu không tìm thấy từ khóa, in bình thường
        cout << textStr;
    }
}

/**
 * @brief Bắt đầu đo thời gian
 *
 * @return Đối tượng SearchTimer
 */
SearchTimer startTimer()
{
    SearchTimer timer;
    chrono::high_resolution_clock::time_point now = chrono::high_resolution_clock::now();
    timer.startTime = chrono::duration_cast<chrono::microseconds>(now.time_since_epoch()).count();
    timer.endTime = 0;
    return timer;
}

/**
 * @brief Dừng đo thời gian
 *
 * @param timer Đối tượng SearchTimer
 */
void stopTimer(SearchTimer& timer)
{
    chrono::high_resolution_clock::time_point now = chrono::high_resolution_clock::now();
    timer.endTime = chrono::duration_cast<chrono::microseconds>(now.time_since_epoch()).count();
}

/**
 * @brief Lấy thời gian thực thi tính bằng microseconds
 *
 * @param timer Đối tượng SearchTimer
 * @return Thời gian thực thi (microseconds)
 */
double getElapsedTimeMs(const SearchTimer& timer)
{
    return static_cast<double>(timer.endTime - timer.startTime) / 1000.0;
}

/**
 * @brief Lấy thời gian thực thi tính bằng giây
 *
 * @param timer Đối tượng SearchTimer
 * @return Thời gian thực thi (giây)
 */
double getElapsedTimeSeconds(const SearchTimer& timer)
{
    return static_cast<double>(timer.endTime - timer.startTime) / 1000000.0;
}
