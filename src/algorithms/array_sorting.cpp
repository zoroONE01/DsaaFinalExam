#include "../../include/algorithms/array_sorting.h"

// ========== THUẬT TOÁN SẮP XẾP CHO ARRAY LIST ==========

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
