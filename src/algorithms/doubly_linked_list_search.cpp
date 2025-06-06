#include "../../include/algorithms/doubly_linked_list_search.h"
#include "../../include/algorithms/search_utils.h"
#include "../../include/core/student.h"
#include <iostream>
#include <iomanip>

using namespace std;

// ========== THUẬT TOÁN TÌM KIẾM CHO DOUBLY LINKED LIST ==========

/**
 * @brief Tìm kiếm tuần tự trong danh sách liên kết đôi
 *
 * @param head Con trỏ đầu danh sách liên kết đôi
 * @param keyword Từ khóa tìm kiếm
 * @param searchCriteria Tiêu chí tìm kiếm
 * @param count Số lượng kết quả tìm được
 * @return Con trỏ đầu danh sách mới chứa các kết quả tìm được
 */
NodeDLL *searchDLL(NodeDLL *head, const char *keyword, int searchCriteria, int &count)
{
    count = 0;

    if (!head)
    {
        return nullptr;
    }

    NodeDLL *resultHead = nullptr;
    NodeDLL *resultTail = nullptr;
    NodeDLL *current = head;

    while (current)
    {
        if (matchesSearchCriteria(current->info, keyword, searchCriteria))
        {
            // Tạo node mới cho kết quả
            NodeDLL *newNode = new NodeDLL;
            newNode->info = current->info;
            newNode->next = nullptr;
            newNode->prev = nullptr;

            if (!resultHead)
            {
                resultHead = resultTail = newNode;
            }
            else
            {
                resultTail->next = newNode;
                newNode->prev = resultTail;
                resultTail = newNode;
            }
            count++;
        }
        current = current->next;
    }

    return resultHead;
}

/**
 * @brief Hiển thị kết quả tìm kiếm cho danh sách liên kết đôi
 *
 * @param results Con trỏ đầu danh sách kết quả
 * @param count Số lượng kết quả
 * @param keyword Từ khóa tìm kiếm
 */
void displaySearchResultsDLL(NodeDLL *results, int count, const char *keyword)
{
    cout << "\n=== KẾT QUẢ TÌM KIẾM (DOUBLY LINKED LIST) ===" << endl;
    cout << "Từ khóa: \"" << keyword << "\"" << endl;
    cout << "Số kết quả: " << count << endl;
    cout << "=====================================" << endl;

    if (count == 0 || !results)
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
    NodeDLL *current = results;
    int index = 1;

    while (current)
    {
        const Student &student = current->info;

        cout << "| " << setw(3) << index
             << " | " << setw(12) << student.studentID
             << " | " << setw(20) << student.lastName
             << " | " << setw(20) << student.firstName
             << " | " << setw(15) << student.studentClass
             << " | " << setw(8) << fixed << setprecision(2) << student.score
             << " |" << endl;

        current = current->next;
        index++;
    }
    cout << setfill('-') << setw(110) << "-" << setfill(' ') << endl;
}
