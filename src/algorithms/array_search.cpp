#include "../../include/algorithms/array_search.h"
#include "../../include/algorithms/search_utils.h"
#include "../../include/core/student.h"
#include <cstring>
#include <iostream>
#include <iomanip>

using namespace std;

// ========== THUẬT TOÁN TÌM KIẾM CHO ARRAY LIST ==========

/**
 * @brief Tìm kiếm tuần tự trong danh sách mảng
 *
 * @param list Danh sách mảng sinh viên
 * @param keyword Từ khóa tìm kiếm
 * @param searchCriteria Tiêu chí tìm kiếm
 * @param count Số lượng kết quả tìm được
 * @return Mảng các chỉ số của sinh viên tìm được
 */
int *searchArrayList(const ArrayStudentList &list, const char *keyword, int searchCriteria, int &count)
{
    count = 0;

    // Lần duyệt đầu: đếm số lượng kết quả phù hợp
    for (int i = 0; i < list.count; i++)
    {
        if (matchesSearchCriteria(list.students[i], keyword, searchCriteria))
        {
            count++;
        }
    }

    if (count == 0)
    {
        return nullptr;
    }

    // Cấp phát mảng kết quả
    int *results = new int[count];
    int resultIndex = 0;

    // Lần duyệt thứ hai: thu thập các chỉ số phù hợp
    for (int i = 0; i < list.count; i++)
    {
        if (matchesSearchCriteria(list.students[i], keyword, searchCriteria))
        {
            results[resultIndex++] = i;
        }
    }

    return results;
}

/**
 * @brief Tìm kiếm nhị phân theo điểm số (yêu cầu dữ liệu đã sắp xếp)
 *
 * @param list Danh sách mảng đã sắp xếp theo điểm
 * @param scoreToFind Điểm số cần tìm
 * @return Chỉ số của phần tử tìm được, -1 nếu không tìm thấy
 */
int binarySearchArrayList(const ArrayStudentList &list, float scoreToFind)
{
    int left = 0;
    int right = list.count - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (list.students[mid].score == scoreToFind)
        {
            return mid;
        }
        else if (list.students[mid].score < scoreToFind)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return -1; // Không tìm thấy
}

/**
 * @brief Tìm kiếm nhị phân theo mã sinh viên (yêu cầu dữ liệu đã sắp xếp)
 *
 * @param list Danh sách mảng đã sắp xếp theo mã sinh viên
 * @param studentID Mã sinh viên cần tìm
 * @return Chỉ số của phần tử tìm được, -1 nếu không tìm thấy
 */
int binarySearchArrayListByID(const ArrayStudentList &list, const char *studentID)
{
    int left = 0;
    int right = list.count - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(list.students[mid].studentID, studentID);

        if (cmp == 0)
        {
            return mid;
        }
        else if (cmp < 0)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return -1; // Không tìm thấy
}

/**
 * @brief Hiển thị kết quả tìm kiếm cho danh sách mảng
 *
 * @param list Danh sách mảng sinh viên
 * @param indices Mảng các chỉ số kết quả
 * @param count Số lượng kết quả
 * @param keyword Từ khóa tìm kiếm
 */
void displaySearchResultsArray(const ArrayStudentList &list, int *indices, int count, const char *keyword)
{
    cout << "\n=== KẾT QUẢ TÌM KIẾM (ARRAY LIST) ===" << endl;
    cout << "Từ khóa: \"" << keyword << "\"" << endl;
    cout << "Số kết quả: " << count << endl;
    cout << "=====================================" << endl;

    if (count == 0)
    {
        cout << "Không tìm thấy kết quả nào." << endl;
        return;
    }

    // Hiển thị tiêu đề bảng
    cout << setfill('-') << setw(110) << "-" << setfill(' ') << endl;
    cout << "| " << setw(3) << "STT"
         << " | " << setw(12) << "Mã SV"
         << " | " << setw(20) << "Họ"
         << " | " << setw(20) << "Tên"
         << " | " << setw(15) << "Lớp"
         << " | " << setw(8) << "Điểm"
         << " |" << endl;
    cout << setfill('-') << setw(110) << "-" << setfill(' ') << endl;

    // Hiển thị kết quả
    for (int i = 0; i < count; i++)
    {
        int index = indices[i];
        const Student &student = list.students[index];

        cout << "| " << setw(3) << (i + 1)
             << " | " << setw(12) << student.studentID
             << " | " << setw(20) << student.lastName
             << " | " << setw(20) << student.firstName
             << " | " << setw(15) << student.studentClass
             << " | " << setw(8) << fixed << setprecision(2) << student.score
             << " |" << endl;
    }
    cout << setfill('-') << setw(110) << "-" << setfill(' ') << endl;
}
