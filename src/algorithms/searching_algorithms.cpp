#include "../../include/algorithms/searching_algorithms.h"
#include <cstring>

// Tìm kiếm tuần tự (Sequential Search) trong mảng
int sequentialSearch(const ArrayStudentList &list, const char *studentID)
{
    for (int i = 0; i < list.count; i++)
    {
        if (strcmp(list.students[i].studentID, studentID) == 0)
        {
            return i; // Trả về vị trí tìm thấy
        }
    }
    return -1; // Không tìm thấy
}

// Tìm kiếm nhị phân (Binary Search) trong mảng đã sắp xếp
// Lưu ý: Mảng phải được sắp xếp theo mã sinh viên trước khi gọi hàm này
int binarySearch(const ArrayStudentList &list, const char *studentID, int left, int right)
{
    if (right >= left)
    {
        int mid = left + (right - left) / 2;

        // Nếu phần tử nằm ở giữa
        if (strcmp(list.students[mid].studentID, studentID) == 0)
            return mid;

        // Nếu phần tử nhỏ hơn mid, tìm trong mảng con bên trái
        if (strcmp(list.students[mid].studentID, studentID) > 0)
            return binarySearch(list, studentID, left, mid - 1);

        // Nếu phần tử lớn hơn mid, tìm trong mảng con bên phải
        return binarySearch(list, studentID, mid + 1, right);
    }

    // Không tìm thấy
    return -1;
}

// Tìm kiếm tuần tự trong danh sách liên kết đơn
NodeSLL *sequentialSearchSLL(NodeSLL *head, const char *studentID)
{
    NodeSLL *current = head;
    while (current != NULL)
    {
        if (strcmp(current->info.studentID, studentID) == 0)
        {
            return current; // Trả về node tìm thấy
        }
        current = current->next;
    }
    return NULL; // Không tìm thấy
}

// Tìm kiếm tuần tự trong danh sách liên kết vòng
NodeSLL *sequentialSearchCLL(NodeSLL *head, const char *studentID)
{
    if (head == NULL)
    {
        return NULL;
    }

    NodeSLL *current = head;
    do
    {
        if (strcmp(current->info.studentID, studentID) == 0)
        {
            return current; // Trả về node tìm thấy
        }
        current = current->next;
    } while (current != head);

    return NULL; // Không tìm thấy
}

// Tìm kiếm tuần tự trong danh sách liên kết đôi
NodeDLL *sequentialSearchDLL(NodeDLL *head, const char *studentID)
{
    NodeDLL *current = head;
    while (current != NULL)
    {
        if (strcmp(current->info.studentID, studentID) == 0)
        {
            return current; // Trả về node tìm thấy
        }
        current = current->next;
    }
    return NULL; // Không tìm thấy
}
