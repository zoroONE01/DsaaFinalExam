#include "../../include/algorithms/singly_linked_list_sorting.h"

// ========== THUẬT TOÁN SẮP XẾP CHO SINGLY LINKED LIST ==========

// Bubble Sort cho Singly Linked List
void bubbleSortSLL(NodeSLL *&head)
{
    if (head == NULL || head->next == NULL)
        return;

    bool swapped;
    NodeSLL *ptr1;
    NodeSLL *lptr = NULL;

    do
    {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (ptr1->info.score > ptr1->next->info.score)
            {
                // Hoán đổi dữ liệu
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

// Insertion Sort cho Singly Linked List
void insertionSortSLL(NodeSLL *&head)
{
    if (head == NULL || head->next == NULL)
        return;

    NodeSLL *sorted = NULL;
    NodeSLL *current = head;

    while (current != NULL)
    {
        NodeSLL *next = current->next;
        
        // Chèn current vào danh sách đã sắp xếp
        if (sorted == NULL || sorted->info.score > current->info.score)
        {
            current->next = sorted;
            sorted = current;
        }
        else
        {
            NodeSLL *temp = sorted;
            while (temp->next != NULL && temp->next->info.score < current->info.score)
            {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    head = sorted;
}

// Selection Sort cho Singly Linked List
void selectionSortSLL(NodeSLL *&head)
{
    if (head == NULL || head->next == NULL)
        return;

    NodeSLL *temp = head;

    while (temp)
    {
        NodeSLL *min = temp;
        NodeSLL *r = temp->next;

        // Tìm node có giá trị nhỏ nhất
        while (r)
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
    }
}

// ========== HÀM HỖ TRỢ CHO MERGE SORT ==========

// Hàm hợp nhất hai danh sách đã sắp xếp
NodeSLL* mergeSortedSLL(NodeSLL* a, NodeSLL* b)
{
    if (a == NULL) return b;
    if (b == NULL) return a;

    NodeSLL* result = NULL;

    if (a->info.score <= b->info.score)
    {
        result = a;
        result->next = mergeSortedSLL(a->next, b);
    }
    else
    {
        result = b;
        result->next = mergeSortedSLL(a, b->next);
    }
    return result;
}

// Hàm tách danh sách thành hai nửa
void splitSLL(NodeSLL* source, NodeSLL** frontRef, NodeSLL** backRef)
{
    NodeSLL* fast;
    NodeSLL* slow;
    slow = source;
    fast = source->next;

    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

// Merge Sort cho Singly Linked List
void mergeSortSLL(NodeSLL *&head)
{
    if (head == NULL || head->next == NULL)
        return;

    NodeSLL* a;
    NodeSLL* b;

    splitSLL(head, &a, &b);

    mergeSortSLL(a);
    mergeSortSLL(b);

    head = mergeSortedSLL(a, b);
}
