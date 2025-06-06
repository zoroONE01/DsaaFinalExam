#ifndef SEARCH_ALGORITHMS_H
#define SEARCH_ALGORITHMS_H

#include "../data_structures/array_list.h"

using namespace std;

// ========== Thuật toán tìm kiếm ==========

// --- Tìm kiếm trong Array List ---

/**
 * Tìm kiếm nhị phân theo điểm số (yêu cầu dữ liệu đã sắp xếp)
 * @param list: Danh sách mảng sinh viên đã sắp xếp theo điểm số
 * @param scoreToFind: Điểm số cần tìm kiếm
 * @return: Chỉ số của sinh viên có điểm số khớp, -1 nếu không tìm thấy
 */
int binarySearchArrayList(const ArrayStudentList &list, float scoreToFind);

/**
 * Tìm kiếm tuần tự theo mã sinh viên
 * @param list: Danh sách mảng sinh viên (không cần sắp xếp)
 * @param studentID: Mã sinh viên cần tìm kiếm
 * @return: Chỉ số của sinh viên có mã khớp, -1 nếu không tìm thấy
 */
int linearSearchArrayListByID(const ArrayStudentList &list, const char* studentID);

/**
 * Tìm kiếm tuần tự theo điểm số
 * @param list: Danh sách mảng sinh viên
 * @param scoreToFind: Điểm số cần tìm kiếm
 * @return: Chỉ số của sinh viên đầu tiên có điểm số khớp, -1 nếu không tìm thấy
 */
int linearSearchArrayListByScore(const ArrayStudentList &list, float scoreToFind);

#endif // SEARCH_ALGORITHMS_H
