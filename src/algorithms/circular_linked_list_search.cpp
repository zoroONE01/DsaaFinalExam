#include "../../include/algorithms/circular_linked_list_search.h"
#include "../../include/algorithms/search_utils.h"
#include "../../include/core/student.h"

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
        if (matchesSearchCriteria(current->info, keyword, searchCriteria))
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
