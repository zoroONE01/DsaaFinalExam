#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include "array_list.h" 

using namespace std;

// ========== Các thuật toán sắp xếp ==========

// --- Sắp xếp nổi bọt cho danh sách mảng ---
void bubbleSortArrayList(ArrayStudentList &list) {
    for (int i = 0; i < list.count - 1; i++) {
        for (int j = 0; j < list.count - i - 1; j++) {
            if (list.students[j].score > list.students[j + 1].score) {
                // Hoán đổi hai sinh viên
                Student temp = list.students[j];
                list.students[j] = list.students[j + 1];
                list.students[j + 1] = temp;
            }
        }
    }
}

// --- Sắp xếp chèn cho danh sách mảng ---
void insertionSortArrayList(ArrayStudentList &list) {
    for (int i = 1; i < list.count; i++) {
        Student key = list.students[i];
        int j = i - 1;
        
        while (j >= 0 && list.students[j].score > key.score) {
            list.students[j + 1] = list.students[j];
            j--;
        }
        
        list.students[j + 1] = key;
    }
}

// --- Sắp xếp chọn cho danh sách mảng ---
void selectionSortArrayList(ArrayStudentList &list) {
    for (int i = 0; i < list.count - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < list.count; j++) {
            if (list.students[j].score < list.students[minIdx].score) {
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
int partitionArrayList(ArrayStudentList &list, int low, int high) {
    float pivot = list.students[high].score;  // Chọn phần tử cuối làm pivot
    int i = low - 1;  // Vị trí của phần tử nhỏ hơn
    
    for (int j = low; j < high; j++) {
        // Nếu phần tử hiện tại nhỏ hơn hoặc bằng pivot
        if (list.students[j].score <= pivot) {
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
void quickSortArrayList(ArrayStudentList &list, int low, int high) {
    if (low < high) {
        // Tìm vị trí phân vùng
        int pi = partitionArrayList(list, low, high);
        
        // Sắp xếp các phần tử trước và sau vị trí phân vùng
        quickSortArrayList(list, low, pi - 1);
        quickSortArrayList(list, pi + 1, high);
    }
}

// Hàm gọi QuickSort
void quickSortArrayList(ArrayStudentList &list) {
    if (list.count <= 1) {
        return;  // Danh sách đã sắp xếp
    }
    
    quickSortArrayList(list, 0, list.count - 1);
}

// --- Tìm kiếm nhị phân trong danh sách mảng đã sắp xếp ---
int binarySearchArrayList(const ArrayStudentList &list, float scoreToFind) {
    int left = 0;
    int right = list.count - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // Kiểm tra nếu điểm số ở vị trí giữa
        if (list.students[mid].score == scoreToFind) {
            return mid;
        }
        
        // Nếu điểm số cần tìm lớn hơn, tìm trong nửa bên phải
        if (list.students[mid].score < scoreToFind) {
            left = mid + 1;
        }
        // Nếu điểm số cần tìm nhỏ hơn, tìm trong nửa bên trái
        else {
            right = mid - 1;
        }
    }
    
    return -1;  // Không tìm thấy
}

#endif // SORTING_ALGORITHMS_H