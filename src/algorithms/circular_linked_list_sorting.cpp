#include "../../include/algorithms/circular_linked_list_sorting.h"
#include "../../include/algorithms/singly_linked_list_sorting.h" // For mergeSortSLL

// ========== THUẬT TOÁN SẮP XẾP CHO CIRCULAR LINKED LIST ==========

// Bubble Sort cho Circular Linked List
void bubbleSortCLL(NodeSLL *&head)
{
    if (head == NULL || head->next == head)
        return;

    bool swapped;
    NodeSLL *ptr1;
    NodeSLL *lptr = NULL;

    do
    {
        swapped = false;
        ptr1 = head;

        do
        {
            if (ptr1->next != head && (lptr == NULL || ptr1->next != lptr))
            {
                if (ptr1->info.score > ptr1->next->info.score)
                {
                    Student temp = ptr1->info;
                    ptr1->info = ptr1->next->info;
                    ptr1->next->info = temp;
                    swapped = true;
                }
            }
            ptr1 = ptr1->next;
        } while (ptr1 != head && ptr1->next != lptr);
        
        lptr = ptr1;
    } while (swapped);
}

// Insertion Sort cho Circular Linked List
void insertionSortCLL(NodeSLL *&head)
{
    if (head == NULL || head->next == head)
        return;

    NodeSLL *current = head->next;
    
    while (current != head)
    {
        NodeSLL *next = current->next;
        Student key = current->info;
        
        // Tìm vị trí chèn
        NodeSLL *pos = head;
        while (pos != current && pos->info.score <= key.score)
        {
            pos = pos->next;
        }
        
        // Nếu cần chèn
        if (pos != current)
        {
            // Xóa current khỏi vị trí hiện tại
            NodeSLL *prev = current;
            while (prev->next != current)
                prev = prev->next;
            prev->next = current->next;
            
            if (current == head)
                head = current->next;
            
            // Chèn vào vị trí mới
            NodeSLL *prevPos = head;
            while (prevPos->next != pos)
                prevPos = prevPos->next;
            
            current->next = pos;
            prevPos->next = current;
            
            if (pos == head)
                head = current;
        }
        current = next;
    }
}

// Selection Sort cho Circular Linked List
void selectionSortCLL(NodeSLL *&head)
{
    if (head == NULL || head->next == head)
        return;

    NodeSLL *temp = head;
    
    do
    {
        NodeSLL *min = temp;
        NodeSLL *r = temp->next;
        
        // Tìm node có giá trị nhỏ nhất trong phần còn lại
        while (r != head)
        {
            if (min->info.score > r->info.score)
                min = r;
            r = r->next;
        }
        
        // Hoán đổi dữ liệu
        Student tempData = temp->info;
        temp->info = min->info;
        min->info = tempData;
        
        temp = temp->next;
    } while (temp != head);
}

// Merge Sort cho Circular Linked List
void mergeSortCLL(NodeSLL *&head)
{
    if (head == NULL || head->next == head)
        return;

    // Chuyển thành singly linked list tạm thời
    NodeSLL *last = head;
    while (last->next != head)
        last = last->next;
    last->next = NULL;

    // Áp dụng merge sort cho singly linked list
    mergeSortSLL(head);

    // Chuyển lại thành circular
    last = head;
    while (last->next != NULL)
        last = last->next;
    last->next = head;
}
