#include "../../include/algorithms/circular_linked_list_sorting.h"
#include "../../include/algorithms/singly_linked_list_sorting.h" // Sử dụng mergeSortSLL
#include <cstring>

// ========== THUẬT TOÁN SẮP XẾP CHO CIRCULAR LINKED LIST ==========

// ========== HÀM TIỆN ÍCH SO SÁNH SINH VIÊN ==========
/**
 * Hàm so sánh hai sinh viên theo tiêu chí được chọn
 * @param a: Sinh viên thứ nhất
 * @param b: Sinh viên thứ hai
 * @param sortCriteria: Tiêu chí sắp xếp (SORT_BY_STUDENT_ID, SORT_BY_NAME, SORT_BY_SCORE)
 * @return true nếu a < b theo tiêu chí đã chọn, false nếu ngược lại
 */
bool compareStudentsCLL(const Student &a, const Student &b, int sortCriteria)
{
    switch (sortCriteria)
    {
    case 1:                                          // SORT_BY_STUDENT_ID
        return strcmp(a.studentID, b.studentID) < 0; // So sánh mã sinh viên
    case 2:                                          // SORT_BY_NAME
        // So sánh theo tên (lastName + firstName)
        {
            int lastNameCmp = strcmp(a.lastName, b.lastName);
            if (lastNameCmp != 0)
                return lastNameCmp < 0;
            return strcmp(a.firstName, b.firstName) < 0;
        }
    case 3:                       // SORT_BY_SCORE
        return a.score < b.score; // So sánh điểm số
    default:
        return a.score < b.score; // Mặc định so sánh theo điểm
    }
}

// ========== BUBBLE SORT (Sắp xếp nổi bọt) ==========
/**
 * Thuật toán Bubble Sort cho danh sách liên kết tròn
 * Ý tưởng: Tương tự Bubble Sort cho linked list đơn nhưng cần xử lý tính chất tròn
 * So sánh các cặp node liền kề và hoán đổi nếu không đúng thứ tự
 * Độ phức tạp: O(n²) trong tất cả trường hợp
 *
 * @param head: Tham chiếu đến con trỏ đầu danh sách liên kết tròn
 * @param sortCriteria: Tiêu chí sắp xếp (1=Mã SV, 2=Tên, 3=Điểm)
 */
void bubbleSortCLL(NodeSLL *&head, int sortCriteria)
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
                // So sánh theo tiêu chí được chọn (đảo ngược để có thứ tự tăng dần)
                if (!compareStudentsCLL(ptr1->info, ptr1->next->info, sortCriteria))
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
 * @param sortCriteria: Tiêu chí sắp xếp (1=Mã SV, 2=Tên, 3=Điểm)
 */
void insertionSortCLL(NodeSLL *&head, int sortCriteria)
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
        while (pos != current && compareStudentsCLL(pos->info, key, sortCriteria))
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
 * @param sortCriteria: Tiêu chí sắp xếp (1=Mã SV, 2=Tên, 3=Điểm)
 */
void selectionSortCLL(NodeSLL *&head, int sortCriteria)
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
            if (compareStudentsCLL(r->info, min->info, sortCriteria))
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
 * @param sortCriteria: Tiêu chí sắp xếp (1=Mã SV, 2=Tên, 3=Điểm)
 */
void mergeSortCLL(NodeSLL *&head, int sortCriteria)
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
    mergeSortSLL(head, sortCriteria);

    // Bước 3: Chuyển lại thành circular linked list
    // Tìm node cuối cùng sau khi sắp xếp
    last = head;
    while (last->next != NULL)
        last = last->next;

    // Nối node cuối với node đầu để tạo vòng tròn
    last->next = head;
}
