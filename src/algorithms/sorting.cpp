#include "../../include/algorithms/sorting.h"

// --- Sắp xếp nổi bọt cho danh sách mảng ---
void bubbleSortArrayList(ArrayStudentList &list)
{
    for (int i = 0; i < list.count - 1; i++)
    {
        for (int j = 0; j < list.count - i - 1; j++)
        {
            if (list.students[j].score > list.students[j + 1].score)
            {
                // Hoán đổi hai sinh viên
                Student temp = list.students[j];
                list.students[j] = list.students[j + 1];
                list.students[j + 1] = temp;
            }
        }
    }
}

// --- Sắp xếp chèn cho danh sách mảng ---
void insertionSortArrayList(ArrayStudentList &list)
{
    for (int i = 1; i < list.count; i++)
    {
        Student key = list.students[i];
        int j = i - 1;

        while (j >= 0 && list.students[j].score > key.score)
        {
            list.students[j + 1] = list.students[j];
            j--;
        }

        list.students[j + 1] = key;
    }
}

// --- Sắp xếp chọn cho danh sách mảng ---
void selectionSortArrayList(ArrayStudentList &list)
{
    for (int i = 0; i < list.count - 1; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < list.count; j++)
        {
            if (list.students[j].score < list.students[minIdx].score)
            {
                minIdx = j;
            }
        }

        // Hoán đổi phần tử nhỏ nhất với phần tử đầu tiên
        Student temp = list.students[minIdx];
        list.students[minIdx] = list.students[i];
        list.students[i] = temp;
    }
}

// --- QuickSort cho danh sách mảng ---
// Hàm phân vùng (partition) cho thuật toán QuickSort
int partitionArrayList(ArrayStudentList &list, int low, int high)
{
    float pivot = list.students[high].score; // Chọn phần tử cuối làm pivot
    int i = low - 1;                         // Vị trí của phần tử nhỏ hơn

    for (int j = low; j < high; j++)
    {
        // Nếu phần tử hiện tại nhỏ hơn hoặc bằng pivot
        if (list.students[j].score <= pivot)
        {
            i++;
            // Hoán đổi list.students[i] và list.students[j]
            Student temp = list.students[i];
            list.students[i] = list.students[j];
            list.students[j] = temp;
        }
    }

    // Hoán đổi list.students[i+1] và list.students[high] (pivot)
    Student temp = list.students[i + 1];
    list.students[i + 1] = list.students[high];
    list.students[high] = temp;

    return i + 1;
}

// Thuật toán QuickSort
void quickSortArrayList(ArrayStudentList &list, int low, int high)
{
    if (low < high)
    {
        // Tìm vị trí phân vùng
        int pi = partitionArrayList(list, low, high);

        // Sắp xếp các phần tử trước và sau vị trí phân vùng
        quickSortArrayList(list, low, pi - 1);
        quickSortArrayList(list, pi + 1, high);
    }
}

// Hàm gọi QuickSort
void quickSortArrayList(ArrayStudentList &list)
{
    if (list.count <= 1)
    {
        return; // Danh sách đã sắp xếp
    }

    quickSortArrayList(list, 0, list.count - 1);
}

// --- Tìm kiếm nhị phân trong danh sách mảng đã sắp xếp ---
int binarySearchArrayList(const ArrayStudentList &list, float scoreToFind)
{
    int left = 0;
    int right = list.count - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        // Kiểm tra nếu điểm số ở vị trí giữa
        if (list.students[mid].score == scoreToFind)
        {
            return mid;
        }

        // Nếu điểm số cần tìm lớn hơn, tìm trong nửa bên phải
        if (list.students[mid].score < scoreToFind)
        {
            left = mid + 1;
        }
        // Nếu điểm số cần tìm nhỏ hơn, tìm trong nửa bên trái
        else
        {
            right = mid - 1;
        }
    }

    return -1; // Không tìm thấy
}

// ========== HEAP SORT cho Array List ==========

// Hàm heapify cho Array List
void heapifyArrayList(ArrayStudentList &list, int n, int i)
{
    int largest = i;       // Khởi tạo largest là root
    int left = 2 * i + 1;  // left child
    int right = 2 * i + 2; // right child

    // Nếu left child lớn hơn root
    if (left < n && list.students[left].score > list.students[largest].score)
        largest = left;

    // Nếu right child lớn hơn largest hiện tại
    if (right < n && list.students[right].score > list.students[largest].score)
        largest = right;

    // Nếu largest không phải root
    if (largest != i)
    {
        Student temp = list.students[i];
        list.students[i] = list.students[largest];
        list.students[largest] = temp;

        // Đệ quy heapify sub-tree bị ảnh hưởng
        heapifyArrayList(list, n, largest);
    }
}

// Thuật toán Heap Sort cho Array List
void heapSortArrayList(ArrayStudentList &list)
{
    int n = list.count;

    // Xây dựng heap (sắp xếp lại mảng)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyArrayList(list, n, i);

    // Trích xuất từng phần tử từ heap
    for (int i = n - 1; i > 0; i--)
    {
        // Di chuyển root hiện tại đến cuối
        Student temp = list.students[0];
        list.students[0] = list.students[i];
        list.students[i] = temp;

        // Gọi heapify cho heap đã giảm kích thước
        heapifyArrayList(list, i, 0);
    }
}

// ========== MERGE SORT cho Array List ==========

// Hàm merge cho Array List
void mergeArrayList(ArrayStudentList &list, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Tạo mảng tạm thời
    Student *leftArray = new Student[n1];
    Student *rightArray = new Student[n2];

    // Sao chép dữ liệu vào mảng tạm thời
    for (int i = 0; i < n1; i++)
        leftArray[i] = list.students[left + i];
    for (int j = 0; j < n2; j++)
        rightArray[j] = list.students[mid + 1 + j];

    // Hợp nhất các mảng tạm thời trở lại list.students[left..right]
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (leftArray[i].score <= rightArray[j].score)
        {
            list.students[k] = leftArray[i];
            i++;
        }
        else
        {
            list.students[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // Sao chép các phần tử còn lại của leftArray[]
    while (i < n1)
    {
        list.students[k] = leftArray[i];
        i++;
        k++;
    }

    // Sao chép các phần tử còn lại của rightArray[]
    while (j < n2)
    {
        list.students[k] = rightArray[j];
        j++;
        k++;
    }

    // Giải phóng bộ nhớ
    delete[] leftArray;
    delete[] rightArray;
}

// Hàm helper cho Merge Sort Array List
void mergeSortArrayListHelper(ArrayStudentList &list, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        // Sắp xếp nửa đầu và nửa sau
        mergeSortArrayListHelper(list, left, mid);
        mergeSortArrayListHelper(list, mid + 1, right);

        // Hợp nhất các nửa đã sắp xếp
        mergeArrayList(list, left, mid, right);
    }
}

// Thuật toán Merge Sort cho Array List
void mergeSortArrayList(ArrayStudentList &list)
{
    if (list.count <= 1)
        return;
    
    mergeSortArrayListHelper(list, 0, list.count - 1);
}

// ========== SORTING ALGORITHMS cho Singly Linked List ==========

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

// Merge Sort cho Singly Linked List
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

// ========== SORTING ALGORITHMS cho Circular Linked List ==========

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

// ========== SORTING ALGORITHMS cho Doubly Linked List ==========

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

// Quick Sort cho Doubly Linked List
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

void quickSortDLLHelper(NodeDLL* low, NodeDLL* high)
{
    if (high != NULL && low != high && low != high->next)
    {
        NodeDLL* pivot = partitionDLL(low, high);
        quickSortDLLHelper(low, pivot->prev);
        quickSortDLLHelper(pivot->next, high);
    }
}

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
