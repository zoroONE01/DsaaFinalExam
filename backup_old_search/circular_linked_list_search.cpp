#include "../../include/algorithms/circular_linked_list_search.h"
#include "../../include/algorithms/search_utils.h"
#include "../../include/core/student.h"
#include "../../include/utils/constants.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>

using namespace std;

// ========== THUẬT TOÁN TÌM KIẾM CHO CIRCULAR LINKED LIST ==========

/**
 * @brief Tìm kiếm tuần tự trong danh sách liên kết vòng
 *
 * @param head Con trỏ đầu danh sách liên kết vòng
 * @param keyword Từ khóa tìm kiếm
 * @param searchCriteria Tiêu chí tìm kiếm
 * @param count Số lượng kết quả tìm được
 * @return Con trỏ đầu danh sách mới chứa các kết quả tìm được
 */
NodeSLL *searchCLL(NodeSLL *head, const char *keyword, int searchCriteria, int &count)
{
    count = 0;

    if (!head)
    {
        return nullptr;
    }

    NodeSLL *resultHead = nullptr;
    NodeSLL *resultTail = nullptr;
    NodeSLL *current = head;

    do
    {
        if (studentMatchesCriteria(current->info, keyword, searchCriteria))
        {
            // Tạo node mới cho kết quả
            NodeSLL *newNode = new NodeSLL;
            newNode->info = current->info;
            newNode->next = nullptr;

            if (!resultHead)
            {
                resultHead = resultTail = newNode;
            }
            else
            {
                resultTail->next = newNode;
                resultTail = newNode;
            }
            count++;
        }
        current = current->next;
    } while (current != head);

    return resultHead;
}

/**
 * @brief Hiển thị kết quả tìm kiếm cho danh sách liên kết vòng với tùy chọn nâng cao
 *
 * @param results Con trỏ đầu danh sách kết quả
 * @param count Số lượng kết quả
 * @param keyword Từ khóa tìm kiếm
 * @param searchCriteria Tiêu chí tìm kiếm
 * @param showReversed Có hiển thị họ tên đảo ngược không
 * @param searchTimeMs Thời gian tìm kiếm (ms)
 */
void displaySearchResultsCLLWithOptions(NodeSLL* results, int count, const char* keyword, 
                                        int searchCriteria, bool showReversed, double searchTimeMs)
{
    cout << "\n=== KẾT QUẢ TÌM KIẾM (CIRCULAR LINKED LIST) ===" << endl;
    cout << "Từ khóa: \"" << keyword << "\"" << endl;
    cout << "Số kết quả: " << count << endl;
    cout << "Thời gian tìm kiếm: " << fixed << setprecision(3) << searchTimeMs << " ms" << endl;
    cout << "=====================================" << endl;

    if (count == 0 || !results)
    {
        cout << "Không tìm thấy kết quả nào." << endl;
        return;
    }

    // Hiển thị tiêu đề bảng
    cout << setfill('-') << setw(120) << "-" << setfill(' ') << endl;
    cout << "| " << setw(3) << "STT"
         << " | " << setw(12) << "Mã SV"
         << " | " << setw(20) << "Họ"
         << " | " << setw(20) << "Tên"
         << " | " << setw(15) << "Lớp"
         << " | " << setw(8) << "Điểm";
    
    if (showReversed) {
        cout << " | " << setw(25) << "Họ Tên Đảo Ngược";
    }
    cout << " |" << endl;
    cout << setfill('-') << setw(120) << "-" << setfill(' ') << endl;

    // Hiển thị kết quả
    NodeSLL *current = results;
    int index = 1;

    while (current)
    {
        const Student &student = current->info;

        cout << "| " << setw(3) << index << " | ";
        
        // Hiển thị mã sinh viên với tô sáng nếu cần
        if (searchCriteria == SEARCH_BY_STUDENT_ID) {
            printHighlighted(student.studentID, keyword, searchCriteria);
            cout << string(12 - strlen(student.studentID), ' ');
        } else {
            cout << setw(12) << student.studentID;
        }
        cout << " | ";
        
        // Hiển thị họ với tô sáng nếu cần
        if (searchCriteria == SEARCH_BY_LAST_NAME) {
            printHighlighted(student.lastName, keyword, searchCriteria);
            cout << string(20 - strlen(student.lastName), ' ');
        } else {
            cout << setw(20) << student.lastName;
        }
        cout << " | ";
        
        // Hiển thị tên với tô sáng nếu cần
        if (searchCriteria == SEARCH_BY_FIRST_NAME) {
            printHighlighted(student.firstName, keyword, searchCriteria);
            cout << string(20 - strlen(student.firstName), ' ');
        } else {
            cout << setw(20) << student.firstName;
        }
        cout << " | ";
        
        // Hiển thị lớp với tô sáng nếu cần
        if (searchCriteria == SEARCH_BY_CLASS) {
            printHighlighted(student.studentClass, keyword, searchCriteria);
            cout << string(15 - strlen(student.studentClass), ' ');
        } else {
            cout << setw(15) << student.studentClass;
        }
        cout << " | ";
        
        // Hiển thị điểm với tô sáng nếu cần
        if (searchCriteria == SEARCH_BY_SCORE) {
            printRedBold(to_string(student.score).substr(0, 4).c_str());
            cout << string(8 - to_string(student.score).substr(0, 4).length(), ' ');
        } else {
            cout << setw(8) << fixed << setprecision(2) << student.score;
        }
        
        // Hiển thị họ tên đảo ngược nếu được yêu cầu
        if (showReversed) {
            cout << " | ";
            char* reversedName = reverseFullName(student.firstName, student.lastName);
            if (reversedName) {
                cout << setw(25) << reversedName;
                delete[] reversedName;
            } else {
                cout << setw(25) << "";
            }
        }
        
        cout << " |" << endl;
        current = current->next;
        index++;
    }
    cout << setfill('-') << setw(120) << "-" << setfill(' ') << endl;
}

/**
 * @brief Tìm kiếm trong danh sách liên kết vòng với tùy chọn nâng cao
 *
 * @param head Con trỏ đầu danh sách liên kết vòng
 * @param keyword Từ khóa tìm kiếm
 * @param searchCriteria Tiêu chí tìm kiếm
 * @param count Số lượng kết quả tìm được
 * @param searchTimeMs Thời gian tìm kiếm (ms)
 * @return Con trỏ đầu danh sách mới chứa các kết quả tìm được
 */
NodeSLL* searchCLLWithOptions(NodeSLL* head, const char* keyword, int searchCriteria, 
                             int &count, double &searchTimeMs)
{
    SearchTimer timer = startTimer();
    
    // Sử dụng sequential search cho linked list
    NodeSLL* results = searchCLL(head, keyword, searchCriteria, count);
    
    stopTimer(timer);
    searchTimeMs = getElapsedTimeMs(timer);
    
    return results;
}
