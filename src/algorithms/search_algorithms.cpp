#include "../../include/algorithms/search_algorithms.h"

// ========== THUẬT TOÁN TÌM KIẾM ==========

// --- Tìm kiếm nhị phân trong danh sách mảng đã sắp xếp theo điểm số ---
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
