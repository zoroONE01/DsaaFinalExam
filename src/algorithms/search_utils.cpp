#include "../../include/algorithms/search_utils.h"
#include "../../include/core/student.h"
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

/**
 * @brief Thực hiện so sánh chuỗi không phân biệt hoa thường
 *
 * @param str1 Chuỗi đầu tiên
 * @param str2 Chuỗi thứ hai
 * @return true nếu hai chuỗi giống nhau (không phân biệt hoa thường)
 */
bool caseInsensitiveMatch(const char *str1, const char *str2)
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
bool caseInsensitiveContains(const char *str, const char *substring)
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
bool matchesSearchCriteria(const Student &student, const char *keyword, int searchCriteria)
{
    if (!keyword || strlen(keyword) == 0)
        return true;

    switch (searchCriteria)
    {
    case 1: // Student ID
        return caseInsensitiveContains(student.studentID, keyword);
    case 2: // First Name
        return caseInsensitiveContains(student.firstName, keyword);
    case 3: // Last Name
        return caseInsensitiveContains(student.lastName, keyword);
    case 4: // Class
        return caseInsensitiveContains(student.studentClass, keyword);
    case 5: // Score (convert keyword to float and check)
    {
        float searchScore = atof(keyword);
        return (student.score >= searchScore - 0.01 && student.score <= searchScore + 0.01);
    }
    default:
        return false;
    }
}
