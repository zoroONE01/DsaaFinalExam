#include "../../include/algorithms/singly_linked_list_sorting.h"
#include <cstring>

// ========== THUẬT TOÁN SẮP XẾP CHO SINGLY LINKED LIST ==========

// ========== HÀM TIỆN ÍCH SO SÁNH SINH VIÊN ==========
/**
 * Hàm so sánh hai sinh viên theo tiêu chí được chọn
 * @param a: Sinh viên thứ nhất
 * @param b: Sinh viên thứ hai  
 * @param sortCriteria: Tiêu chí sắp xếp (SORT_BY_STUDENT_ID, SORT_BY_NAME, SORT_BY_SCORE)
 * @return true nếu a < b theo tiêu chí đã chọn, false nếu ngược lại
 */
bool compareStudentsSLL(const Student &a, const Student &b, int sortCriteria)
{
    switch (sortCriteria)
    {
    case 1: // SORT_BY_STUDENT_ID
        return strcmp(a.studentID, b.studentID) < 0; // So sánh mã sinh viên
    case 2: // SORT_BY_NAME
        // So sánh theo tên (lastName + firstName)
        {
            int lastNameCmp = strcmp(a.lastName, b.lastName);
            if (lastNameCmp != 0)
                return lastNameCmp < 0;
            return strcmp(a.firstName, b.firstName) < 0;
        }
    case 3: // SORT_BY_SCORE
        return a.score < b.score; // So sánh điểm số
    default:
        return a.score < b.score; // Mặc định so sánh theo điểm
    }
}

// ========== THUẬT TOÁN SẮP XẾP CHO SINGLY LINKED LIST ==========

// ========== BUBBLE SORT (Sắp xếp nổi bọt) ==========
/**
 * Thuật toán Bubble Sort cho danh sách liên kết đơn
 * Ý tưởng: So sánh các cặp node liền kề và hoán đổi dữ liệu nếu không đúng thứ tự
 * Sau mỗi lần duyệt, node có giá trị lớn nhất sẽ "nổi" về cuối danh sách
 * Độ phức tạp: O(n²) trong tất cả trường hợp
 *
 * @param head: Tham chiếu đến con trỏ đầu danh sách liên kết đơn
 * @param sortCriteria: Tiêu chí sắp xếp (1=Mã SV, 2=Tên, 3=Điểm)
 */
void bubbleSortSLL(NodeSLL *&head, int sortCriteria)
{
    // Kiểm tra danh sách rỗng hoặc chỉ có 1 phần tử
    if (head == NULL || head->next == NULL)
        return;

    bool swapped;         // Cờ đánh dấu có hoán đổi trong lần duyệt
    NodeSLL *ptr1;        // Con trỏ duyệt danh sách
    NodeSLL *lptr = NULL; // Con trỏ đến phần tử cuối đã sắp xếp

    do
    {
        swapped = false; // Khởi tạo cờ cho lần duyệt mới
        ptr1 = head;     // Bắt đầu từ đầu danh sách

        // Duyệt từ đầu đến phần chưa được sắp xếp
        while (ptr1->next != lptr)
        {
            // So sánh theo tiêu chí được chọn (đảo ngược để có thứ tự tăng dần)
            if (!compareStudentsSLL(ptr1->info, ptr1->next->info, sortCriteria))
            {
                // Hoán đổi dữ liệu giữa hai node (không hoán đổi con trỏ)
                Student temp = ptr1->info;
                ptr1->info = ptr1->next->info;
                ptr1->next->info = temp;
                swapped = true; // Đánh dấu có hoán đổi
            }
            ptr1 = ptr1->next; // Chuyển sang node tiếp theo
        }
        lptr = ptr1; // Cập nhật vị trí cuối đã sắp xếp
    } while (swapped); // Tiếp tục nếu vẫn còn hoán đổi
}

// ========== INSERTION SORT (Sắp xếp chèn) ==========
/**
 * Thuật toán Insertion Sort cho danh sách liên kết đơn
 * Ý tưởng: Xây dựng danh sách đã sắp xếp từng node một bằng cách
 * lấy từng node từ danh sách gốc và chèn vào vị trí đúng trong danh sách mới
 * Độ phức tạp: O(n) tốt nhất, O(n²) xấu nhất
 *
 * @param head: Tham chiếu đến con trỏ đầu danh sách liên kết đơn
 * @param sortCriteria: Tiêu chí sắp xếp (1=Mã SV, 2=Tên, 3=Điểm)
 */
void insertionSortSLL(NodeSLL *&head, int sortCriteria)
{
    // Kiểm tra danh sách rỗng hoặc chỉ có 1 phần tử
    if (head == NULL || head->next == NULL)
        return;

    NodeSLL *sorted = NULL;  // Đầu danh sách đã sắp xếp (ban đầu rỗng)
    NodeSLL *current = head; // Node hiện tại trong danh sách gốc

    // Duyệt qua tất cả node trong danh sách gốc
    while (current != NULL)
    {
        NodeSLL *next = current->next; // Lưu node tiếp theo trước khi thay đổi

        // Chèn current vào danh sách đã sắp xếp
        // TH1: Danh sách sorted rỗng hoặc current nhỏ hơn phần tử đầu
        if (sorted == NULL || compareStudentsSLL(current->info, sorted->info, sortCriteria))
        {
            current->next = sorted; // Chèn current vào đầu danh sách sorted
            sorted = current;       // Cập nhật đầu danh sách sorted
        }
        else
        {
            // TH2: Tìm vị trí thích hợp trong danh sách sorted để chèn current
            NodeSLL *temp = sorted;

            // Duyệt đến vị trí node có giá trị >= current (hoặc cuối danh sách)
            while (temp->next != NULL && compareStudentsSLL(temp->next->info, current->info, sortCriteria))
            {
                temp = temp->next;
            }

            // Chèn current vào sau node temp
            current->next = temp->next;
            temp->next = current;
        }

        current = next; // Chuyển sang node tiếp theo trong danh sách gốc
    }

    head = sorted; // Cập nhật đầu danh sách thành danh sách đã sắp xếp
}

// ========== SELECTION SORT (Sắp xếp chọn) ==========
/**
 * Thuật toán Selection Sort cho danh sách liên kết đơn
 * Ý tưởng: Với mỗi vị trí trong danh sách, tìm phần tử nhỏ nhất trong phần còn lại
 * và hoán đổi với phần tử tại vị trí hiện tại
 * Độ phức tạp: O(n²) trong tất cả trường hợp
 *
 * @param head: Tham chiếu đến con trỏ đầu danh sách liên kết đơn
 * @param sortCriteria: Tiêu chí sắp xếp (1=Mã SV, 2=Tên, 3=Điểm)
 */
void selectionSortSLL(NodeSLL *&head, int sortCriteria)
{
    // Kiểm tra danh sách rỗng hoặc chỉ có 1 phần tử
    if (head == NULL || head->next == NULL)
        return;

    NodeSLL *temp = head; // Node hiện tại cần tìm min cho vị trí này

    // Duyệt qua từng vị trí trong danh sách
    while (temp)
    {
        NodeSLL *min = temp;     // Giả sử node hiện tại là nhỏ nhất
        NodeSLL *r = temp->next; // Bắt đầu tìm từ node tiếp theo

        // Tìm node có giá trị nhỏ nhất trong phần còn lại của danh sách
        while (r)
        {
            if (compareStudentsSLL(r->info, min->info, sortCriteria))
                min = r; // Cập nhật node nhỏ nhất
            r = r->next; // Chuyển sang node tiếp theo
        }

        // Hoán đổi dữ liệu giữa node hiện tại và node nhỏ nhất tìm được
        // (không hoán đổi con trỏ để tránh phức tạp hóa)
        if (min != temp) // Chỉ hoán đổi khi cần thiết
        {
            Student tempData = temp->info;
            temp->info = min->info;
            min->info = tempData;
        }

        temp = temp->next; // Chuyển sang vị trí tiếp theo
    }
}

// ========== MERGE SORT (Sắp xếp trộn) ==========
// ========== CÁC HÀM HỖ TRỢ ==========

/**
 * Hàm hợp nhất hai danh sách liên kết đơn đã được sắp xếp thành một danh sách sắp xếp
 *
 * @param a: Con trỏ đến đầu danh sách thứ nhất (đã sắp xếp)
 * @param b: Con trỏ đến đầu danh sách thứ hai (đã sắp xếp)
 * @param sortCriteria: Tiêu chí sắp xếp (1=Mã SV, 2=Tên, 3=Điểm)
 * @return: Con trỏ đến đầu danh sách sau khi hợp nhất
 */
NodeSLL *mergeSortedSLL(NodeSLL *a, NodeSLL *b, int sortCriteria)
{
    // Trường hợp cơ sở: một trong hai danh sách rỗng
    if (a == NULL)
        return b;
    if (b == NULL)
        return a;

    NodeSLL *result = NULL; // Đầu danh sách kết quả

    // So sánh phần tử đầu của hai danh sách và chọn phần tử nhỏ hơn
    if (compareStudentsSLL(a->info, b->info, sortCriteria))
    {
        result = a; // Chọn node từ danh sách a
        // Đệ quy hợp nhất phần còn lại của a với toàn bộ b
        result->next = mergeSortedSLL(a->next, b, sortCriteria);
    }
    else
    {
        result = b; // Chọn node từ danh sách b
        // Đệ quy hợp nhất toàn bộ a với phần còn lại của b
        result->next = mergeSortedSLL(a, b->next, sortCriteria);
    }
    return result;
}

/**
 * Hàm tách danh sách liên kết đơn thành hai nửa bằng nhau (hoặc gần bằng nhau)
 * Sử dụng kỹ thuật "rùa và thỏ": con trỏ chậm di chuyển 1 bước, con trỏ nhanh di chuyển 2 bước
 *
 * @param source: Danh sách gốc cần tách
 * @param frontRef: Con trỏ tới con trỏ đầu của nửa đầu
 * @param backRef: Con trỏ tới con trỏ đầu của nửa sau
 */
void splitSLL(NodeSLL *source, NodeSLL **frontRef, NodeSLL **backRef)
{
    NodeSLL *fast; // Con trỏ di chuyển nhanh (2 bước/lần)
    NodeSLL *slow; // Con trỏ di chuyển chậm (1 bước/lần)

    slow = source;       // Bắt đầu từ đầu danh sách
    fast = source->next; // Con trỏ nhanh bắt đầu từ node thứ 2

    // Di chuyển fast 2 bước và slow 1 bước cho đến khi fast đến cuối
    while (fast != NULL)
    {
        fast = fast->next; // Bước đầu tiên của fast
        if (fast != NULL)
        {
            slow = slow->next; // slow chỉ di chuyển khi fast còn node tiếp theo
            fast = fast->next; // Bước thứ hai của fast
        }
    }

    // Khi fast đến cuối, slow ở giữa danh sách
    *frontRef = source;    // Nửa đầu từ đầu đến slow
    *backRef = slow->next; // Nửa sau từ slow->next đến cuối
    slow->next = NULL;     // Cắt đứt liên kết giữa hai nửa
}

/**
 * Thuật toán Merge Sort cho danh sách liên kết đơn
 * Ý tưởng: Sử dụng chiến lược "chia để trị"
 * - Chia danh sách thành hai nửa
 * - Đệ quy sắp xếp từng nửa
 * - Hợp nhất hai nửa đã sắp xếp
 * Độ phức tạp: O(n log n) trong tất cả trường hợp
 *
 * @param head: Tham chiếu đến con trỏ đầu danh sách liên kết đơn
 * @param sortCriteria: Tiêu chí sắp xếp (1=Mã SV, 2=Tên, 3=Điểm)
 */
void mergeSortSLL(NodeSLL *&head, int sortCriteria)
{
    // Trường hợp cơ sở: danh sách rỗng hoặc chỉ có 1 phần tử
    if (head == NULL || head->next == NULL)
        return;

    NodeSLL *a; // Nửa đầu của danh sách
    NodeSLL *b; // Nửa sau của danh sách

    // Tách danh sách thành hai nửa
    splitSLL(head, &a, &b);

    // Đệ quy sắp xếp từng nửa
    mergeSortSLL(a, sortCriteria);
    mergeSortSLL(b, sortCriteria);

    // Hợp nhất hai nửa đã sắp xếp và cập nhật head
    head = mergeSortedSLL(a, b, sortCriteria);
}
