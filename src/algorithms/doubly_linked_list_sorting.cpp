#include "../../include/algorithms/doubly_linked_list_sorting.h"
#include "../../include/algorithms/array_sorting.h" // For heapSortArrayList

// ========== THUẬT TOÁN SẮP XẾP CHO DOUBLY LINKED LIST ==========

/**
 * Thuật toán Bubble Sort cho Doubly Linked List
 *
 * Nguyên lý:
 * - So sánh từng cặp node liền kề và hoán đổi nếu thứ tự không đúng
 * - Sau mỗi lượt duyệt, phần tử lớn nhất "nổi" lên cuối danh sách
 * - Lặp lại cho đến khi không còn hoán đổi nào xảy ra
 *
 * Ưu điểm: Đơn giản, ổn định (stable sorting)
 * Nhược điểm: Hiệu suất thấp với danh sách lớn
 * Độ phức tạp: O(n²) cho trường hợp xấu nhất, O(n) cho trường hợp tốt nhất
 *
 * @param head: Con trỏ tham chiếu đến node đầu danh sách
 * @param tail: Con trỏ tham chiếu đến node cuối danh sách
 * @param sortCriteria: Tiêu chí sắp xếp (SORT_BY_STUDENT_ID, SORT_BY_NAME, SORT_BY_SCORE)
 */
void bubbleSortDLL(NodeDLL *&head, NodeDLL *&tail, int sortCriteria)
{
    // Kiểm tra danh sách rỗng hoặc chỉ có 1 phần tử
    if (head == NULL || head->next == NULL)
        return;

    bool swapped;         // Cờ đánh dấu có hoán đổi trong lượt duyệt
    NodeDLL *ptr1;        // Con trỏ duyệt danh sách
    NodeDLL *lptr = NULL; // Con trỏ đánh dấu vùng đã sắp xếp

    do
    {
        swapped = false; // Khởi tạo cờ hoán đổi
        ptr1 = head;     // Bắt đầu từ node đầu

        // Duyệt từ đầu đến vùng đã sắp xếp
        while (ptr1->next != lptr)
        {
            // So sánh hai node liền kề theo tiêu chí được chọn
            if (!compareStudents(ptr1->info, ptr1->next->info, sortCriteria))
            {
                // Hoán đổi dữ liệu sinh viên giữa hai node
                Student temp = ptr1->info;
                ptr1->info = ptr1->next->info;
                ptr1->next->info = temp;
                swapped = true; // Đánh dấu đã có hoán đổi
            }
            ptr1 = ptr1->next;
        }
        // Cập nhật vùng đã sắp xếp (thu hẹp phạm vi duyệt)
        lptr = ptr1;
    } while (swapped); // Tiếp tục nếu còn hoán đổi
}

/**
 * Thuật toán Insertion Sort cho Doubly Linked List
 *
 * Nguyên lý:
 * - Xây dựng dần danh sách đã sắp xếp từ trái sang phải
 * - Với mỗi phần tử, tìm vị trí thích hợp trong phần đã sắp xếp
 * - Di chuyển node đến vị trí đúng bằng cách thao tác con trỏ
 *
 * Ưu điểm: Hiệu quả với danh sách nhỏ hoặc gần như đã sắp xếp
 * Nhược điểm: Hiệu suất giảm với danh sách lớn và ngẫu nhiên
 * Độ phức tạp: O(n²) cho trường hợp xấu nhất, O(n) cho trường hợp tốt nhất
 *
 * @param head: Con trỏ tham chiếu đến node đầu danh sách
 * @param tail: Con trỏ tham chiếu đến node cuối danh sách
 * @param sortCriteria: Tiêu chí sắp xếp (SORT_BY_STUDENT_ID, SORT_BY_NAME, SORT_BY_SCORE)
 */
void insertionSortDLL(NodeDLL *&head, NodeDLL *&tail, int sortCriteria)
{
    // Kiểm tra danh sách rỗng hoặc chỉ có 1 phần tử
    if (head == NULL || head->next == NULL)
        return;

    NodeDLL *current = head->next; // Bắt đầu từ node thứ hai

    while (current != NULL)
    {
        NodeDLL *next = current->next; // Lưu node tiếp theo trước khi di chuyển
        Student key = current->info;   // Lưu thông tin sinh viên cần chèn

        // Tìm vị trí thích hợp trong phần đã sắp xếp
        NodeDLL *pos = head;
        while (pos != current && (compareStudents(pos->info, key, sortCriteria) || 
               (!compareStudents(pos->info, key, sortCriteria) && !compareStudents(key, pos->info, sortCriteria))))
            pos = pos->next;

        // Chỉ di chuyển node nếu cần thiết (tối ưu hóa)
        if (pos != current)
        {
            // BƯỚC 1: Tách current ra khỏi vị trí hiện tại
            if (current->next)
                current->next->prev = current->prev; // Liên kết node sau với node trước
            else
                tail = current->prev; // Cập nhật tail nếu current là node cuối

            current->prev->next = current->next; // Liên kết node trước với node sau

            // BƯỚC 2: Chèn current vào trước pos
            current->prev = pos->prev; // Thiết lập liên kết ngược
            current->next = pos;       // Thiết lập liên kết tiến

            // Cập nhật liên kết của node trước pos (nếu có)
            if (pos->prev)
                pos->prev->next = current;
            else
                head = current; // Cập nhật head nếu chèn vào đầu danh sách

            pos->prev = current; // Cập nhật liên kết ngược của pos
        }
        current = next; // Chuyển đến node tiếp theo
    }
}

/**
 * Thuật toán Selection Sort cho Doubly Linked List
 *
 * Nguyên lý:
 * - Trong mỗi lượt duyệt, tìm phần tử nhỏ nhất trong phần chưa sắp xếp
 * - Hoán đổi phần tử nhỏ nhất với phần tử đầu tiên của phần chưa sắp xếp
 * - Thu hẹp dần phạm vi tìm kiếm cho lượt duyệt tiếp theo
 *
 * Ưu điểm: Số lần hoán đổi ít (tối đa n-1 lần), dễ hiểu và cài đặt
 * Nhược điểm: Không tận dụng được tính chất đã sắp xếp của dữ liệu
 * Độ phức tạp: O(n²) cho mọi trường hợp
 *
 * @param head: Con trỏ tham chiếu đến node đầu danh sách
 * @param tail: Con trỏ tham chiếu đến node cuối danh sách
 * @param sortCriteria: Tiêu chí sắp xếp (SORT_BY_STUDENT_ID, SORT_BY_NAME, SORT_BY_SCORE)
 */
void selectionSortDLL(NodeDLL *&head, NodeDLL *&tail, int sortCriteria)
{
    // Kiểm tra danh sách rỗng hoặc chỉ có 1 phần tử
    if (head == NULL || head->next == NULL)
        return;

    NodeDLL *temp = head; // Con trỏ duyệt phần chưa sắp xếp

    while (temp)
    {
        NodeDLL *min = temp;     // Giả sử node hiện tại có giá trị nhỏ nhất
        NodeDLL *r = temp->next; // Con trỏ tìm kiếm trong phần còn lại

        // Tìm node có giá trị nhỏ nhất trong phần chưa sắp xếp theo tiêu chí được chọn
        while (r)
        {
            if (compareStudents(r->info, min->info, sortCriteria))
                min = r; // Cập nhật node có giá trị nhỏ nhất
            r = r->next;
        }

        // Hoán đổi dữ liệu chỉ khi cần thiết (tối ưu hóa)
        if (min != temp)
        {
            Student tempData = temp->info;
            temp->info = min->info;
            min->info = tempData;
        }

        temp = temp->next; // Chuyển đến vị trí tiếp theo trong phần chưa sắp xếp
    }
}

// ========== HÀM HỖ TRỢ CHO QUICK SORT ==========

/**
 * Hàm phân vùng cho thuật toán Quick Sort
 *
 * Nguyên lý:
 * - Chọn phần tử cuối làm pivot (phần tử chốt)
 * - Sắp xếp lại để tất cả phần tử <= pivot ở bên trái
 * - Tất cả phần tử > pivot ở bên phải
 * - Trả về vị trí cuối cùng của pivot
 *
 * @param low: Node đầu của đoạn cần phân vùng
 * @param high: Node cuối của đoạn cần phân vùng (pivot)
 * @param sortCriteria: Tiêu chí sắp xếp (SORT_BY_STUDENT_ID, SORT_BY_NAME, SORT_BY_SCORE)
 * @return: Vị trí cuối cùng của pivot sau khi phân vùng
 */
NodeDLL *partitionDLL(NodeDLL *low, NodeDLL *high, int sortCriteria)
{
    Student pivot = high->info; // Chọn thông tin sinh viên của node cuối làm pivot
    NodeDLL *i = low->prev;     // Con trỏ đánh dấu vùng <= pivot

    // Duyệt từ low đến node trước high
    for (NodeDLL *j = low; j != high; j = j->next)
    {
        // Nếu phần tử hiện tại <= pivot theo tiêu chí được chọn
        if (compareStudents(j->info, pivot, sortCriteria) || 
            (!compareStudents(j->info, pivot, sortCriteria) && !compareStudents(pivot, j->info, sortCriteria)))
        {
            // Di chuyển con trỏ i và hoán đổi
            i = (i == NULL) ? low : i->next;
            Student temp = i->info;
            i->info = j->info;
            j->info = temp;
        }
    }

    // Đặt pivot vào vị trí đúng
    i = (i == NULL) ? low : i->next;
    Student temp = i->info;
    i->info = high->info;
    high->info = temp;

    return i; // Trả về vị trí cuối cùng của pivot
}

/**
 * Hàm đệ quy thực hiện Quick Sort cho Doubly Linked List
 *
 * Nguyên lý chiến lược "Chia để trị":
 * - Phân vùng danh sách thành hai phần quanh pivot
 * - Đệ quy sắp xếp phần bên trái pivot
 * - Đệ quy sắp xếp phần bên phải pivot
 *
 * @param low: Node đầu của đoạn cần sắp xếp
 * @param high: Node cuối của đoạn cần sắp xếp
 * @param sortCriteria: Tiêu chí sắp xếp (SORT_BY_STUDENT_ID, SORT_BY_NAME, SORT_BY_SCORE)
 */
void quickSortDLLHelper(NodeDLL *low, NodeDLL *high, int sortCriteria)
{
    // Điều kiện dừng: đoạn có ít hơn 2 phần tử
    if (high != NULL && low != high && low != high->next)
    {
        // Phân vùng và lấy vị trí pivot
        NodeDLL *pivot = partitionDLL(low, high, sortCriteria);

        // Đệ quy sắp xếp phần bên trái pivot
        quickSortDLLHelper(low, pivot->prev, sortCriteria);

        // Đệ quy sắp xếp phần bên phải pivot
        quickSortDLLHelper(pivot->next, high, sortCriteria);
    }
}

/**
 * Thuật toán Quick Sort cho Doubly Linked List
 *
 * Nguyên lý:
 * - Sử dụng chiến lược "Chia để trị" (Divide and Conquer)
 * - Chọn một phần tử làm pivot và phân vùng dữ liệu
 * - Đệ quy sắp xếp các phần đã phân chia
 *
 * Ưu điểm: Hiệu suất cao trung bình, sắp xếp tại chỗ (in-place)
 * Nhược điểm: Hiệu suất giảm trong trường hợp xấu nhất (dữ liệu đã sắp xếp)
 * Độ phức tạp: O(n log n) trung bình, O(n²) trường hợp xấu nhất
 *
 * @param head: Con trỏ tham chiếu đến node đầu danh sách
 * @param tail: Con trỏ tham chiếu đến node cuối danh sách
 * @param sortCriteria: Tiêu chí sắp xếp (SORT_BY_STUDENT_ID, SORT_BY_NAME, SORT_BY_SCORE)
 */
void quickSortDLL(NodeDLL *&head, NodeDLL *&tail, int sortCriteria)
{
    // Kiểm tra danh sách rỗng hoặc chỉ có 1 phần tử
    if (head == NULL || head->next == NULL)
        return;

    // Gọi hàm đệ quy để thực hiện sắp xếp
    quickSortDLLHelper(head, tail, sortCriteria);
}

/**
 * Thuật toán Heap Sort cho Doubly Linked List
 *
 * Nguyên lý:
 * - Do cấu trúc Doubly Linked List không hỗ trợ truy cập ngẫu nhiên
 * - Chuyển đổi tạm thời sang mảng để áp dụng Heap Sort
 * - Sao chép kết quả đã sắp xếp trở lại Doubly Linked List
 *
 * Ưu điểm: Độ phức tạp ổn định O(n log n) cho mọi trường hợp
 * Nhược điểm: Cần thêm bộ nhớ O(n) cho việc chuyển đổi
 * Độ phức tạp: O(n log n) về thời gian, O(n) về không gian
 *
 * Lưu ý: Chỉ sử dụng khi cần hiệu suất ổn định và có đủ bộ nhớ
 *
 * @param head: Con trỏ tham chiếu đến node đầu danh sách
 * @param tail: Con trỏ tham chiếu đến node cuối danh sách
 * @param sortCriteria: Tiêu chí sắp xếp (SORT_BY_STUDENT_ID, SORT_BY_NAME, SORT_BY_SCORE)
 */
void heapSortDLL(NodeDLL *&head, NodeDLL *&tail, int sortCriteria)
{
    // Kiểm tra danh sách rỗng hoặc chỉ có 1 phần tử
    if (head == NULL || head->next == NULL)
        return;

    // BƯỚC 1: Đếm số phần tử trong danh sách
    int count = 0;
    NodeDLL *temp = head;
    while (temp)
    {
        count++;
        temp = temp->next;
    }

    // BƯỚC 2: Chuyển đổi Doubly Linked List sang mảng
    ArrayStudentList arrayList;
    arrayList.count = count;
    temp = head;
    for (int i = 0; i < count; i++)
    {
        arrayList.students[i] = temp->info; // Sao chép dữ liệu sinh viên
        temp = temp->next;
    }

    // BƯỚC 3: Áp dụng thuật toán Heap Sort cho mảng
    heapSortArrayList(arrayList, sortCriteria);

    // BƯỚC 4: Sao chép kết quả đã sắp xếp trở lại Doubly Linked List
    temp = head;
    for (int i = 0; i < count; i++)
    {
        temp->info = arrayList.students[i]; // Cập nhật dữ liệu đã sắp xếp
        temp = temp->next;
    }
}

// ========== HÀM HỖ TRỢ CHO MERGE SORT ==========

/**
 * Hàm hợp nhất hai Doubly Linked List đã được sắp xếp
 *
 * Nguyên lý:
 * - So sánh phần tử đầu của hai danh sách con
 * - Chọn phần tử nhỏ hơn làm kết quả
 * - Đệ quy hợp nhất phần còn lại
 * - Cập nhật các liên kết prev và next cho cấu trúc doubly
 *
 * @param firstHalf: Danh sách con thứ nhất đã sắp xếp
 * @param secondHalf: Danh sách con thứ hai đã sắp xếp
 * @param sortCriteria: Tiêu chí sắp xếp (SORT_BY_STUDENT_ID, SORT_BY_NAME, SORT_BY_SCORE)
 * @return: Node đầu của danh sách đã hợp nhất
 */
NodeDLL *mergeDLL(NodeDLL *firstHalf, NodeDLL *secondHalf, int sortCriteria)
{
    // Trường hợp cơ sở: một trong hai danh sách rỗng
    if (firstHalf == NULL)
        return secondHalf;
    if (secondHalf == NULL)
        return firstHalf;

    NodeDLL *result = NULL;

    // So sánh hai node đầu tiên theo tiêu chí được chọn
    if (compareStudents(firstHalf->info, secondHalf->info, sortCriteria) || 
        (!compareStudents(firstHalf->info, secondHalf->info, sortCriteria) && !compareStudents(secondHalf->info, firstHalf->info, sortCriteria)))
    {
        result = firstHalf; // Chọn node từ danh sách thứ nhất
        // Đệ quy hợp nhất phần còn lại
        result->next = mergeDLL(firstHalf->next, secondHalf, sortCriteria);
        // Cập nhật liên kết ngược cho cấu trúc doubly
        if (result->next)
            result->next->prev = result;
    }
    else
    {
        result = secondHalf; // Chọn node từ danh sách thứ hai
        // Đệ quy hợp nhất phần còn lại
        result->next = mergeDLL(firstHalf, secondHalf->next, sortCriteria);
        // Cập nhật liên kết ngược cho cấu trúc doubly
        if (result->next)
            result->next->prev = result;
    }

    return result;
}

/**
 * Hàm tách Doubly Linked List thành hai nửa bằng nhau
 *
 * Nguyên lý "Rùa và Thỏ" (Tortoise and Hare):
 * - Con trỏ slow di chuyển 1 bước mỗi lần
 * - Con trỏ fast di chuyển 2 bước mỗi lần
 * - Khi fast đến cuối, slow ở giữa danh sách
 * - Cắt liên kết tại vị trí giữa để tạo hai danh sách riêng biệt
 *
 * @param head: Node đầu của danh sách cần tách
 * @return: Node đầu của nửa thứ hai
 */
NodeDLL *splitDLL(NodeDLL *head)
{
    NodeDLL *fast = head; // Con trỏ "thỏ" di chuyển nhanh
    NodeDLL *slow = head; // Con trỏ "rùa" di chuyển chậm
    NodeDLL *prev = NULL; // Lưu node trước slow để cắt liên kết

    // Áp dụng thuật toán "Rùa và Thỏ"
    while (fast && fast->next)
    {
        prev = slow;
        slow = slow->next;       // Rùa đi 1 bước
        fast = fast->next->next; // Thỏ đi 2 bước
    }

    // Cắt liên kết tại điểm giữa để tạo hai danh sách riêng biệt
    if (prev)
    {
        prev->next = NULL; // Cắt liên kết tiến
        slow->prev = NULL; // Cắt liên kết ngược
    }

    return slow; // Trả về node đầu của nửa thứ hai
}

/**
 * Thuật toán Merge Sort cho Doubly Linked List
 *
 * Nguyên lý "Chia để trị" (Divide and Conquer):
 * - Chia danh sách thành hai nửa bằng nhau
 * - Đệ quy sắp xếp từng nửa
 * - Hợp nhất hai nửa đã sắp xếp thành kết quả cuối cùng
 *
 * Ưu điểm:
 * - Độ phức tạp ổn định O(n log n) cho mọi trường hợp
 * - Thuật toán ổn định (stable), giữ nguyên thứ tự tương đối
 * - Hiệu quả với dữ liệu lớn
 *
 * Nhược điểm: Cần thêm bộ nhớ cho đệ quy
 * Độ phức tạp: O(n log n) về thời gian, O(log n) về không gian (stack)
 *
 * @param headRef: Con trỏ tham chiếu đến con trỏ node đầu danh sách
 * @param sortCriteria: Tiêu chí sắp xếp (SORT_BY_STUDENT_ID, SORT_BY_NAME, SORT_BY_SCORE)
 */
void mergeSortDLL(NodeDLL **headRef, int sortCriteria)
{
    NodeDLL *head = *headRef;

    // Điều kiện dừng đệ quy: danh sách rỗng hoặc chỉ có 1 phần tử
    if (head == NULL || head->next == NULL)
        return;

    // BƯỚC 1: Chia danh sách thành hai nửa
    NodeDLL *second = splitDLL(head);

    // BƯỚC 2: Đệ quy sắp xếp từng nửa
    mergeSortDLL(&head, sortCriteria);   // Sắp xếp nửa đầu
    mergeSortDLL(&second, sortCriteria); // Sắp xếp nửa sau

    // BƯỚC 3: Hợp nhất hai nửa đã sắp xếp
    *headRef = mergeDLL(head, second, sortCriteria);
}
