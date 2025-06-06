#include "../../include/algorithms/doubly_linked_list_sorting.h"
#include "../../include/algorithms/array_sorting.h" // For heapSortArrayList

// ========== THUẬT TOÁN SẮP XẾP CHO DOUBLY LINKED LIST ==========

// Bubble Sort cho Doubly Linked List
void bubbleSortDLL(NodeDLL *&head, NodeDLL *&tail)
{
    if (head == NULL || head->next == NULL)
        return;

    bool swapped;
    NodeDLL *ptr1;
    NodeDLL *lptr = NULL;

    do
    {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (ptr1->info.score > ptr1->next->info.score)
            {
                Student temp = ptr1->info;
                ptr1->info = ptr1->next->info;
                ptr1->next->info = temp;
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Insertion Sort cho Doubly Linked List
void insertionSortDLL(NodeDLL *&head, NodeDLL *&tail)
{
    if (head == NULL || head->next == NULL)
        return;

    NodeDLL *current = head->next;

    while (current != NULL)
    {
        NodeDLL *next = current->next;
        Student key = current->info;

        NodeDLL *pos = head;
        while (pos != current && pos->info.score <= key.score)
            pos = pos->next;

        if (pos != current)
        {
            // Xóa current khỏi vị trí hiện tại
            if (current->next)
                current->next->prev = current->prev;
            else
                tail = current->prev;
            
            current->prev->next = current->next;

            // Chèn current vào trước pos
            current->prev = pos->prev;
            current->next = pos;

            if (pos->prev)
                pos->prev->next = current;
            else
                head = current;
            
            pos->prev = current;
        }
        current = next;
    }
}

// Selection Sort cho Doubly Linked List
void selectionSortDLL(NodeDLL *&head, NodeDLL *&tail)
{
    if (head == NULL || head->next == NULL)
        return;

    NodeDLL *temp = head;

    while (temp)
    {
        NodeDLL *min = temp;
        NodeDLL *r = temp->next;

        while (r)
        {
            if (min->info.score > r->info.score)
                min = r;
            r = r->next;
        }

        Student tempData = temp->info;
        temp->info = min->info;
        min->info = tempData;
        
        temp = temp->next;
    }
}

// ========== HÀM HỖ TRỢ CHO QUICK SORT ==========

// Hàm phân vùng cho Quick Sort
NodeDLL* partitionDLL(NodeDLL* low, NodeDLL* high)
{
    float pivot = high->info.score;
    NodeDLL* i = low->prev;

    for (NodeDLL* j = low; j != high; j = j->next)
    {
        if (j->info.score <= pivot)
        {
            i = (i == NULL) ? low : i->next;
            Student temp = i->info;
            i->info = j->info;
            j->info = temp;
        }
    }
    i = (i == NULL) ? low : i->next;
    Student temp = i->info;
    i->info = high->info;
    high->info = temp;
    return i;
}

// Hàm helper cho Quick Sort
void quickSortDLLHelper(NodeDLL* low, NodeDLL* high)
{
    if (high != NULL && low != high && low != high->next)
    {
        NodeDLL* pivot = partitionDLL(low, high);
        quickSortDLLHelper(low, pivot->prev);
        quickSortDLLHelper(pivot->next, high);
    }
}

// Quick Sort cho Doubly Linked List
void quickSortDLL(NodeDLL *&head, NodeDLL *&tail)
{
    if (head == NULL || head->next == NULL)
        return;
    
    quickSortDLLHelper(head, tail);
}

// Heap Sort cho Doubly Linked List (chuyển đổi qua mảng)
void heapSortDLL(NodeDLL *&head, NodeDLL *&tail)
{
    if (head == NULL || head->next == NULL)
        return;

    // Đếm số phần tử
    int count = 0;
    NodeDLL *temp = head;
    while (temp)
    {
        count++;
        temp = temp->next;
    }

    // Chuyển sang mảng
    ArrayStudentList arrayList;
    arrayList.count = count;
    temp = head;
    for (int i = 0; i < count; i++)
    {
        arrayList.students[i] = temp->info;
        temp = temp->next;
    }

    // Áp dụng heap sort cho mảng
    heapSortArrayList(arrayList);

    // Chuyển kết quả trở lại doubly linked list
    temp = head;
    for (int i = 0; i < count; i++)
    {
        temp->info = arrayList.students[i];
        temp = temp->next;
    }
}

// ========== HÀM HỖ TRỢ CHO MERGE SORT ==========

// Hàm hợp nhất hai danh sách đã sắp xếp
NodeDLL *mergeDLL(NodeDLL *firstHalf, NodeDLL *secondHalf)
{
    if (firstHalf == NULL)
        return secondHalf;
    if (secondHalf == NULL)
        return firstHalf;

    NodeDLL *result = NULL;

    if (firstHalf->info.score <= secondHalf->info.score)
    {
        result = firstHalf;
        result->next = mergeDLL(firstHalf->next, secondHalf);
        if (result->next)
            result->next->prev = result;
    }
    else
    {
        result = secondHalf;
        result->next = mergeDLL(firstHalf, secondHalf->next);
        if (result->next)
            result->next->prev = result;
    }

    return result;
}

// Hàm tách danh sách thành hai nửa
NodeDLL *splitDLL(NodeDLL *head)
{
    NodeDLL *fast = head;
    NodeDLL *slow = head;
    NodeDLL *prev = NULL;

    while (fast && fast->next)
    {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    if (prev)
    {
        prev->next = NULL;
        slow->prev = NULL;
    }

    return slow;
}

// Merge Sort cho Doubly Linked List
void mergeSortDLL(NodeDLL **headRef)
{
    NodeDLL *head = *headRef;
    
    if (head == NULL || head->next == NULL)
        return;

    NodeDLL *second = splitDLL(head);

    mergeSortDLL(&head);
    mergeSortDLL(&second);

    *headRef = mergeDLL(head, second);
}
