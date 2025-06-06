#include "../../include/algorithms/array_sorting.h"

// ========== THUẬT TOÁN SẮP XẾP CHO ARRAY LIST ==========

// ========== BUBBLE SORT (Sắp xếp nổi bọt) ==========
/**
 * Thuật toán Bubble Sort cho danh sách mảng sinh viên
 * Ý tưởng: So sánh các cặp phần tử liền kề và hoán đổi nếu chúng không đúng thứ tự
 * Phần tử lớn nhất sẽ "nổi lên" vị trí cuối sau mỗi lần duyệt
 * Độ phức tạp: O(n²) trong tất cả trường hợp
 *
 * @param list: Tham chiếu đến danh sách mảng sinh viên cần sắp xếp
 */
void bubbleSortArrayList(ArrayStudentList &list)
{
    // Duyệt qua tất cả phần tử, mỗi lần duyệt sẽ đưa 1 phần tử lớn nhất về cuối
    for (int i = 0; i < list.count - 1; i++)
    {
        // Duyệt từ đầu đến phần tử chưa được sắp xếp
        // (list.count - i - 1) vì i phần tử cuối đã được sắp xếp
        for (int j = 0; j < list.count - i - 1; j++)
        {
            // So sánh điểm của sinh viên thứ j và j+1
            if (list.students[j].score > list.students[j + 1].score)
            {
                // Hoán đổi vị trí hai sinh viên nếu không đúng thứ tự tăng dần
                Student temp = list.students[j];
                list.students[j] = list.students[j + 1];
                list.students[j + 1] = temp;
            }
        }
    }
}

// ========== INSERTION SORT (Sắp xếp chèn) ==========
/**
 * Thuật toán Insertion Sort cho danh sách mảng sinh viên
 * Ý tưởng: Xây dựng dãy sắp xếp từng phần tử một bằng cách chèn phần tử vào đúng vị trí
 * Giống như sắp xếp bài trong tay - lấy từng lá bài và chèn vào vị trí đúng
 * Độ phức tạp: O(n) tốt nhất (đã sắp xếp), O(n²) xấu nhất
 *
 * @param list: Tham chiếu đến danh sách mảng sinh viên cần sắp xếp
 */
void insertionSortArrayList(ArrayStudentList &list)
{
    // Bắt đầu từ phần tử thứ 2 (index = 1), phần tử đầu coi như đã sắp xếp
    for (int i = 1; i < list.count; i++)
    {
        Student key = list.students[i]; // Phần tử cần chèn vào vị trí đúng
        int j = i - 1;                  // Vị trí cuối của phần đã sắp xếp

        // Dịch chuyển các phần tử lớn hơn key về phía sau
        // để tạo chỗ trống cho key
        while (j >= 0 && list.students[j].score > key.score)
        {
            list.students[j + 1] = list.students[j]; // Dịch chuyển phần tử
            j--;                                     // Tiếp tục xét phần tử trước đó
        }

        // Chèn key vào vị trí đúng
        list.students[j + 1] = key;
    }
}

// ========== SELECTION SORT (Sắp xếp chọn) ==========
/**
 * Thuật toán Selection Sort cho danh sách mảng sinh viên
 * Ý tưởng: Tìm phần tử nhỏ nhất trong phần chưa sắp xếp và đặt vào đầu phần chưa sắp xếp
 * Chia mảng thành 2 phần: đã sắp xếp (đầu) và chưa sắp xếp (sau)
 * Độ phức tạp: O(n²) trong tất cả trường hợp
 *
 * @param list: Tham chiếu đến danh sách mảng sinh viên cần sắp xếp
 */
void selectionSortArrayList(ArrayStudentList &list)
{
    // Duyệt qua từng vị trí của mảng (trừ vị trí cuối)
    for (int i = 0; i < list.count - 1; i++)
    {
        int minIdx = i; // Giả sử phần tử tại vị trí i là nhỏ nhất

        // Tìm phần tử nhỏ nhất trong phần chưa sắp xếp (từ i+1 đến cuối)
        for (int j = i + 1; j < list.count; j++)
        {
            // Nếu tìm thấy phần tử nhỏ hơn, cập nhật chỉ số
            if (list.students[j].score < list.students[minIdx].score)
            {
                minIdx = j;
            }
        }

        // Hoán đổi phần tử nhỏ nhất tìm được với phần tử đầu tiên của phần chưa sắp xếp
        if (minIdx != i) // Chỉ hoán đổi khi cần thiết để tối ưu
        {
            Student temp = list.students[minIdx];
            list.students[minIdx] = list.students[i];
            list.students[i] = temp;
        }
    }
}

// ========== QUICK SORT (Sắp xếp nhanh) ==========
/**
 * Hàm phân vùng (partition) cho thuật toán Quick Sort
 * Ý tưởng: Chọn một phần tử làm pivot, sắp xếp lại mảng sao cho:
 * - Các phần tử nhỏ hơn hoặc bằng pivot nằm bên trái
 * - Các phần tử lớn hơn pivot nằm bên phải
 * - Trả về vị trí cuối cùng của pivot
 *
 * @param list: Tham chiếu đến danh sách mảng sinh viên
 * @param low: Chỉ số đầu của phần mảng cần phân vùng
 * @param high: Chỉ số cuối của phần mảng cần phân vùng (chứa pivot)
 * @return: Vị trí cuối cùng của pivot sau khi phân vùng
 */
int partitionArrayList(ArrayStudentList &list, int low, int high)
{
    float pivot = list.students[high].score; // Chọn phần tử cuối làm pivot
    int i = low - 1;                         // Chỉ số của phần tử nhỏ hơn pivot (khởi tạo = low - 1)

    // Duyệt qua tất cả phần tử từ low đến high-1
    for (int j = low; j < high; j++)
    {
        // Nếu phần tử hiện tại nhỏ hơn hoặc bằng pivot
        if (list.students[j].score <= pivot)
        {
            i++; // Tăng vùng các phần tử nhỏ hơn pivot
            // Hoán đổi phần tử hiện tại vào vùng nhỏ hơn pivot
            Student temp = list.students[i];
            list.students[i] = list.students[j];
            list.students[j] = temp;
        }
    }

    // Đặt pivot vào vị trí đúng (sau tất cả phần tử nhỏ hơn)
    Student temp = list.students[i + 1];
    list.students[i + 1] = list.students[high];
    list.students[high] = temp;

    return i + 1; // Trả về vị trí của pivot
}

/**
 * Hàm hỗ trợ đệ quy cho Quick Sort
 * Áp dụng thuật toán "chia để trị" - chia mảng thành các phần nhỏ hơn và sắp xếp riêng biệt
 *
 * @param list: Tham chiếu đến danh sách mảng sinh viên
 * @param low: Chỉ số đầu của phần mảng cần sắp xếp
 * @param high: Chỉ số cuối của phần mảng cần sắp xếp
 */
void quickSortArrayListHelper(ArrayStudentList &list, int low, int high)
{
    if (low < high) // Điều kiện dừng đệ quy: còn ít nhất 2 phần tử
    {
        // Phân vùng mảng và lấy vị trí pivot
        int pivotIndex = partitionArrayList(list, low, high);

        // Đệ quy sắp xếp phần bên trái pivot (các phần tử nhỏ hơn)
        quickSortArrayListHelper(list, low, pivotIndex - 1);

        // Đệ quy sắp xếp phần bên phải pivot (các phần tử lớn hơn)
        quickSortArrayListHelper(list, pivotIndex + 1, high);
    }
}

/**
 * Thuật toán Quick Sort cho danh sách mảng sinh viên
 * Ý tưởng: Sử dụng chiến lược "chia để trị" với pivot để phân chia và sắp xếp
 * Độ phức tạp: O(n log n) trung bình, O(n²) xấu nhất (khi pivot luôn là min/max)
 *
 * @param list: Tham chiếu đến danh sách mảng sinh viên cần sắp xếp
 */
void quickSortArrayList(ArrayStudentList &list)
{
    // Kiểm tra điều kiện đầu vào
    if (list.count <= 1)
    {
        return; // Danh sách rỗng hoặc có 1 phần tử đã được sắp xếp
    }

    // Gọi hàm đệ quy để sắp xếp toàn bộ mảng
    quickSortArrayListHelper(list, 0, list.count - 1);
}

// ========== HEAP SORT (Sắp xếp vun đống) ==========
/**
 * Hàm heapify để duy trì tính chất max-heap
 * Đảm bảo phần tử tại vị trí i thỏa mãn tính chất heap (cha >= con)
 *
 * @param list: Tham chiếu đến danh sách mảng sinh viên
 * @param n: Kích thước của heap
 * @param i: Chỉ số của node cần heapify
 */
void heapifyArrayList(ArrayStudentList &list, int n, int i)
{
    int largest = i;       // Giả sử node i là lớn nhất
    int left = 2 * i + 1;  // Node con trái
    int right = 2 * i + 2; // Node con phải

    // Nếu node con trái lớn hơn node cha
    if (left < n && list.students[left].score > list.students[largest].score)
        largest = left;

    // Nếu node con phải lớn hơn node lớn nhất hiện tại
    if (right < n && list.students[right].score > list.students[largest].score)
        largest = right;

    // Nếu node lớn nhất không phải là node gốc
    if (largest != i)
    {
        // Hoán đổi node gốc với node lớn nhất
        Student temp = list.students[i];
        list.students[i] = list.students[largest];
        list.students[largest] = temp;

        // Đệ quy heapify phần sub-tree bị ảnh hưởng
        heapifyArrayList(list, n, largest);
    }
}

/**
 * Thuật toán Heap Sort cho danh sách mảng sinh viên
 * Ý tưởng: Xây dựng max-heap, sau đó liên tục lấy phần tử lớn nhất (root) ra
 * Độ phức tạp: O(n log n) trong tất cả trường hợp
 *
 * @param list: Tham chiếu đến danh sách mảng sinh viên cần sắp xếp
 */
void heapSortArrayList(ArrayStudentList &list)
{
    int n = list.count;

    // Bước 1: Xây dựng max-heap từ mảng đầu vào
    // Bắt đầu từ node cha cuối cùng và heapify ngược lên trên
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyArrayList(list, n, i);

    // Bước 2: Trích xuất từng phần tử từ heap
    for (int i = n - 1; i > 0; i--)
    {
        // Di chuyển phần tử lớn nhất (root) về vị trí cuối
        Student temp = list.students[0];
        list.students[0] = list.students[i];
        list.students[i] = temp;

        // Gọi heapify cho heap đã giảm kích thước (loại trừ phần tử vừa sắp xếp)
        heapifyArrayList(list, i, 0);
    }
}

// ========== MERGE SORT (Sắp xếp trộn) ==========
/**
 * Hàm hợp nhất (merge) hai phần mảng đã sắp xếp thành một mảng sắp xếp
 *
 * @param list: Tham chiếu đến danh sách mảng sinh viên
 * @param left: Chỉ số đầu của phần mảng cần hợp nhất
 * @param mid: Chỉ số giữa, chia mảng thành 2 phần [left..mid] và [mid+1..right]
 * @param right: Chỉ số cuối của phần mảng cần hợp nhất
 */
void mergeArrayList(ArrayStudentList &list, int left, int mid, int right)
{
    // Tính kích thước của hai mảng con
    int n1 = mid - left + 1; // Kích thước mảng con trái
    int n2 = right - mid;    // Kích thước mảng con phải

    // Tạo các mảng tạm thời để lưu trữ hai mảng con
    Student *leftArray = new Student[n1];  // Mảng con trái
    Student *rightArray = new Student[n2]; // Mảng con phải

    // Sao chép dữ liệu vào các mảng tạm thời
    for (int i = 0; i < n1; i++)
        leftArray[i] = list.students[left + i];
    for (int j = 0; j < n2; j++)
        rightArray[j] = list.students[mid + 1 + j];

    // Hợp nhất các mảng tạm thời trở lại list.students[left..right]
    int i = 0, j = 0; // Chỉ số duyệt mảng con trái và phải
    int k = left;     // Chỉ số duyệt mảng kết quả

    // So sánh và hợp nhất cho đến khi một trong hai mảng con hết phần tử
    while (i < n1 && j < n2)
    {
        if (leftArray[i].score <= rightArray[j].score)
        {
            list.students[k] = leftArray[i]; // Lấy từ mảng trái
            i++;
        }
        else
        {
            list.students[k] = rightArray[j]; // Lấy từ mảng phải
            j++;
        }
        k++;
    }

    // Sao chép các phần tử còn lại của mảng con trái (nếu có)
    while (i < n1)
    {
        list.students[k] = leftArray[i];
        i++;
        k++;
    }

    // Sao chép các phần tử còn lại của mảng con phải (nếu có)
    while (j < n2)
    {
        list.students[k] = rightArray[j];
        j++;
        k++;
    }

    // Giải phóng bộ nhớ đã cấp phát
    delete[] leftArray;
    delete[] rightArray;
}

/**
 * Hàm hỗ trợ đệ quy cho Merge Sort
 * Chia mảng thành các phần nhỏ hơn và sắp xếp riêng biệt
 *
 * @param list: Tham chiếu đến danh sách mảng sinh viên
 * @param left: Chỉ số đầu của phần mảng cần sắp xếp
 * @param right: Chỉ số cuối của phần mảng cần sắp xếp
 */
void mergeSortArrayListHelper(ArrayStudentList &list, int left, int right)
{
    if (left < right) // Điều kiện dừng đệ quy: còn ít nhất 2 phần tử
    {
        // Tìm điểm giữa để chia mảng thành 2 phần
        int mid = left + (right - left) / 2;

        // Đệ quy sắp xếp nửa đầu
        mergeSortArrayListHelper(list, left, mid);

        // Đệ quy sắp xếp nửa sau
        mergeSortArrayListHelper(list, mid + 1, right);

        // Hợp nhất hai nửa đã được sắp xếp
        mergeArrayList(list, left, mid, right);
    }
}

/**
 * Thuật toán Merge Sort cho danh sách mảng sinh viên
 * Ý tưởng: Sử dụng chiến lược "chia để trị" - chia mảng thành các phần nhỏ,
 * sắp xếp riêng biệt rồi hợp nhất lại
 * Độ phức tạp: O(n log n) trong tất cả trường hợp
 *
 * @param list: Tham chiếu đến danh sách mảng sinh viên cần sắp xếp
 */
void mergeSortArrayList(ArrayStudentList &list)
{
    // Kiểm tra điều kiện đầu vào
    if (list.count <= 1)
        return; // Danh sách rỗng hoặc có 1 phần tử đã được sắp xếp

    // Gọi hàm đệ quy để sắp xếp toàn bộ mảng
    mergeSortArrayListHelper(list, 0, list.count - 1);
}
