#include "../../include/algorithms/circular_linked_list_sorting.h"
#include "../../include/algorithms/singly_linked_list_sorting.h" // Sử dụng mergeSortSLL

// ========== THUẬT TOÁN SẮP XẾP CHO CIRCULAR LINKED LIST ==========

// ========== BUBBLE SORT (Sắp xếp nổi bọt) ==========
/**
 * Thuật toán Bubble Sort cho danh sách liên kết tròn
 * Ý tưởng: Tương tự Bubble Sort cho linked list đơn nhưng cần xử lý tính chất tròn
 * So sánh các cặp node liền kề và hoán đổi nếu không đúng thứ tự
 * Độ phức tạp: O(n²) trong tất cả trường hợp
 *
 * @param head: Tham chiếu đến con trỏ đầu danh sách liên kết tròn
 */
void bubbleSortCLL(NodeSLL *&head)
{
    // Kiểm tra danh sách rỗng hoặc chỉ có 1 phần tử
    if (head == NULL || head->next == head)
        return;

    bool swapped;         // Cờ đánh dấu có hoán đổi trong lần duyệt
    NodeSLL *ptr1;        // Con trỏ duyệt danh sách
    NodeSLL *lptr = NULL; // Con trỏ đến phần tử cuối đã sắp xếp

    do
    {
        swapped = false; // Khởi tạo cờ cho lần duyệt mới
        ptr1 = head;     // Bắt đầu từ đầu danh sách

        do
        {
            // Kiểm tra để không vượt qua phần đã sắp xếp và không quay vòng vô hạn
            if (ptr1->next != head && (lptr == NULL || ptr1->next != lptr))
            {
                // So sánh điểm của node hiện tại với node kế tiếp
                if (ptr1->info.score > ptr1->next->info.score)
                {
                    // Hoán đổi dữ liệu giữa hai node
                    Student temp = ptr1->info;
                    ptr1->info = ptr1->next->info;
                    ptr1->next->info = temp;
                    swapped = true; // Đánh dấu có hoán đổi
                }
            }
            ptr1 = ptr1->next; // Chuyển sang node tiếp theo
        } while (ptr1 != head && ptr1->next != lptr); // Dừng khi quay về đầu hoặc đến phần đã sắp xếp

        lptr = ptr1; // Cập nhật vị trí cuối đã sắp xếp
    } while (swapped); // Tiếp tục nếu vẫn còn hoán đổi
}

// ========== INSERTION SORT (Sắp xếp chèn) ==========
/**
 * Thuật toán Insertion Sort cho danh sách liên kết tròn
 * Ý tưởng: Duyệt qua từng node và chèn vào vị trí đúng trong phần đã sắp xếp
 * Cần xử lý cẩn thận tính chất tròn khi di chuyển và chèn node
 * Độ phức tạp: O(n) tốt nhất, O(n²) xấu nhất
 *
 * @param head: Tham chiếu đến con trỏ đầu danh sách liên kết tròn
 */
void insertionSortCLL(NodeSLL *&head)
{
    // Kiểm tra danh sách rỗng hoặc chỉ có 1 phần tử
    if (head == NULL || head->next == head)
        return;

    NodeSLL *current = head->next; // Bắt đầu từ node thứ 2 (node đầu coi như đã sắp xếp)

    // Duyệt qua từng node trong danh sách (trừ node đầu)
    while (current != head)
    {
        NodeSLL *next = current->next; // Lưu node tiếp theo trước khi thay đổi
        Student key = current->info;   // Dữ liệu của node cần chèn

        // Tìm vị trí thích hợp để chèn current trong phần đã sắp xếp
        NodeSLL *pos = head;
        while (pos != current && pos->info.score <= key.score)
        {
            pos = pos->next;
        }

        // Nếu current không ở đúng vị trí, cần di chuyển
        if (pos != current)
        {
            // Bước 1: Xóa current khỏi vị trí hiện tại
            // Tìm node trước current
            NodeSLL *prev = current;
            while (prev->next != current)
                prev = prev->next;
            prev->next = current->next; // Bỏ qua current

            // Cập nhật head nếu current là head
            if (current == head)
                head = current->next;

            // Bước 2: Chèn current vào vị trí mới (trước pos)
            // Tìm node trước pos
            NodeSLL *prevPos = head;
            while (prevPos->next != pos)
                prevPos = prevPos->next;

            // Chèn current giữa prevPos và pos
            current->next = pos;
            prevPos->next = current;

            // Cập nhật head nếu chèn vào đầu danh sách
            if (pos == head)
                head = current;
        }
        current = next; // Chuyển sang node tiếp theo
    }
}

// ========== SELECTION SORT (Sắp xếp chọn) ==========
/**
 * Thuật toán Selection Sort cho danh sách liên kết tròn
 * Ý tưởng: Với mỗi vị trí, tìm phần tử nhỏ nhất trong phần còn lại và hoán đổi
 * Duyệt vòng tròn và xử lý đúng điều kiện dừng
 * Độ phức tạp: O(n²) trong tất cả trường hợp
 *
 * @param head: Tham chiếu đến con trỏ đầu danh sách liên kết tròn
 */
void selectionSortCLL(NodeSLL *&head)
{
    // Kiểm tra danh sách rỗng hoặc chỉ có 1 phần tử
    if (head == NULL || head->next == head)
        return;

    NodeSLL *temp = head; // Node hiện tại cần tìm min cho vị trí này

    // Duyệt qua từng vị trí trong danh sách tròn
    do
    {
        NodeSLL *min = temp;     // Giả sử node hiện tại là nhỏ nhất
        NodeSLL *r = temp->next; // Bắt đầu tìm từ node tiếp theo

        // Tìm node có giá trị nhỏ nhất trong phần còn lại của danh sách tròn
        while (r != head) // Duyệt đến khi quay lại đầu danh sách
        {
            if (min->info.score > r->info.score)
                min = r; // Cập nhật node nhỏ nhất
            r = r->next; // Chuyển sang node tiếp theo
        }

        // Hoán đổi dữ liệu giữa node hiện tại và node nhỏ nhất tìm được
        if (min != temp) // Chỉ hoán đổi khi cần thiết
        {
            Student tempData = temp->info;
            temp->info = min->info;
            min->info = tempData;
        }

        temp = temp->next; // Chuyển sang vị trí tiếp theo
    } while (temp != head); // Dừng khi quay lại đầu danh sách
}

// ========== MERGE SORT (Sắp xếp trộn) ==========
/**
 * Thuật toán Merge Sort cho danh sách liên kết tròn
 * Ý tưởng: Chuyển đổi tạm thời từ circular thành singly linked list,
 * áp dụng merge sort, sau đó chuyển lại thành circular
 * Độ phức tạp: O(n log n) trong tất cả trường hợp
 *
 * @param head: Tham chiếu đến con trỏ đầu danh sách liên kết tròn
 */
void mergeSortCLL(NodeSLL *&head)
{
    // Kiểm tra danh sách rỗng hoặc chỉ có 1 phần tử
    if (head == NULL || head->next == head)
        return;

    // Bước 1: Chuyển từ circular linked list thành singly linked list tạm thời
    // Tìm node cuối cùng
    NodeSLL *last = head;
    while (last->next != head)
        last = last->next;

    // Cắt liên kết tròn bằng cách đặt next của node cuối thành NULL
    last->next = NULL;

    // Bước 2: Áp dụng merge sort cho singly linked list
    mergeSortSLL(head);

    // Bước 3: Chuyển lại thành circular linked list
    // Tìm node cuối cùng sau khi sắp xếp
    last = head;
    while (last->next != NULL)
        last = last->next;

    // Nối node cuối với node đầu để tạo vòng tròn
    last->next = head;
}
