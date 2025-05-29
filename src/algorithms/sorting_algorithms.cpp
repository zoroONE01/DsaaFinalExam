#include "../../include/algorithms/sorting_algorithms.h"
#include <algorithm>

using namespace std;

// ===== Các thuật toán sắp xếp cho danh sách mảng =====

// Sắp xếp nổi bọt (Bubble Sort)
void bubbleSortArrayList(ArrayStudentList &list)
{
    for (int i = 0; i < list.count - 1; i++)
    {
        for (int j = 0; j < list.count - i - 1; j++)
        {
            if (list.students[j].score > list.students[j + 1].score)
            {
                // Đổi chỗ hai sinh viên
                Student temp = list.students[j];
                list.students[j] = list.students[j + 1];
                list.students[j + 1] = temp;
            }
        }
    }
}

// Sắp xếp chèn (Insertion Sort)
void insertionSortArrayList(ArrayStudentList &list)
{
    for (int i = 1; i < list.count; i++)
    {
        Student key = list.students[i];
        int j = i - 1;

        // Di chuyển các phần tử lớn hơn key về phía sau
        while (j >= 0 && list.students[j].score > key.score)
        {
            list.students[j + 1] = list.students[j];
            j--;
        }
        list.students[j + 1] = key;
    }
}

// Sắp xếp chọn (Selection Sort)
void selectionSortArrayList(ArrayStudentList &list)
{
    for (int i = 0; i < list.count - 1; i++)
    {
        // Tìm phần tử nhỏ nhất trong mảng chưa sắp xếp
        int min_idx = i;
        for (int j = i + 1; j < list.count; j++)
        {
            if (list.students[j].score < list.students[min_idx].score)
            {
                min_idx = j;
            }
        }

        // Đổi chỗ phần tử nhỏ nhất với phần tử đầu tiên
        if (min_idx != i)
        {
            Student temp = list.students[i];
            list.students[i] = list.students[min_idx];
            list.students[min_idx] = temp;
        }
    }
}

// Sắp xếp nhanh (Quick Sort)
void quickSortArrayList(ArrayStudentList &list)
{
    quickSortArrayListHelper(list, 0, list.count - 1);
}

void quickSortArrayListHelper(ArrayStudentList &list, int low, int high)
{
    if (low < high)
    {
        // Phân hoạch mảng và lấy vị trí pivot
        int pi = partitionArrayList(list, low, high);

        // Sắp xếp các phần tử trước và sau pivot
        quickSortArrayListHelper(list, low, pi - 1);
        quickSortArrayListHelper(list, pi + 1, high);
    }
}

int partitionArrayList(ArrayStudentList &list, int low, int high)
{
    float pivot = list.students[high].score; // Chọn pivot là phần tử cuối
    int i = (low - 1);                       // Vị trí của phần tử nhỏ hơn

    for (int j = low; j <= high - 1; j++)
    {
        // Nếu phần tử hiện tại nhỏ hơn pivot
        if (list.students[j].score < pivot)
        {
            i++; // Tăng vị trí của phần tử nhỏ hơn
            Student temp = list.students[i];
            list.students[i] = list.students[j];
            list.students[j] = temp;
        }
    }
    Student temp = list.students[i + 1];
    list.students[i + 1] = list.students[high];
    list.students[high] = temp;
    return (i + 1);
}

// ===== Các thuật toán sắp xếp cho danh sách liên kết đôi =====

// Sắp xếp trộn (Merge Sort)
void mergeSortDLL(NodeDLL **headRef)
{
    NodeDLL *head = *headRef;
    NodeDLL *a;
    NodeDLL *b;

    // Trường hợp cơ sở: danh sách rỗng hoặc chỉ có 1 phần tử
    if ((head == NULL) || (head->next == NULL))
    {
        return;
    }

    // Chia danh sách làm đôi
    splitDLL(head, &a, &b);

    // Sắp xếp đệ quy hai nửa
    mergeSortDLL(&a);
    mergeSortDLL(&b);

    // Trộn hai danh sách đã sắp xếp
    *headRef = sortedMergeDLL(a, b);
}

// Trộn hai danh sách đã sắp xếp
NodeDLL *sortedMergeDLL(NodeDLL *a, NodeDLL *b)
{
    // Trường hợp cơ sở
    if (a == NULL)
        return b;
    if (b == NULL)
        return a;

    // Chọn phần tử nhỏ hơn
    NodeDLL *result = NULL;

    if (a->info.score <= b->info.score)
    {
        result = a;
        result->next = sortedMergeDLL(a->next, b);
        result->next->prev = result;
    }
    else
    {
        result = b;
        result->next = sortedMergeDLL(a, b->next);
        result->next->prev = result;
    }

    result->prev = NULL;
    return result;
}

// Chia danh sách làm đôi
void splitDLL(NodeDLL *source, NodeDLL **frontRef, NodeDLL **backRef)
{
    NodeDLL *fast;
    NodeDLL *slow;
    slow = source;
    fast = source->next;

    // Sử dụng phương pháp "fast and slow pointers"
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // 'slow' là ở giữa danh sách, chia nó thành hai phần
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
    if (*backRef != NULL)
        (*backRef)->prev = NULL;
}
