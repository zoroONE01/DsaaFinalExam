#ifndef STUDENT_LIBRARY_H
#define STUDENT_LIBRARY_H

// ========== THƯ VIỆN CHÍNH HỆ THỐNG QUẢN LÝ SINH VIÊN PTIT ==========
// Tệp header này bao gồm tất cả các thành phần cần thiết cho quản lý sinh viên

// Core utilities (phải include đầu tiên)
#include "utils/constants.h"            // Các hằng số chung
#include "utils/error_handling.h"       // Xử lý lỗi chuẩn hóa  
#include "utils/memory_utils.h"         // Tiện ích quản lý bộ nhớ
#include "utils/validation.h"           // Thư viện kiểm tra đầu vào
#include "utils/common_utils.h"         // Các hàm tiện ích chung

// UI components
#include "ui/common_ui.h"               // Giao diện người dùng

// Core business logic
#include "core/student.h"               // Định nghĩa cấu trúc Student
#include "core/operations.h"            // Các hàm xử lý chung cho các cấu trúc dữ liệu

// Data structures
#include "data_structures/array_list.h"           // Cài đặt danh sách mảng
#include "data_structures/singly_linked_list.h"   // Cài đặt danh sách liên kết đơn
#include "data_structures/circular_linked_list.h" // Cài đặt danh sách liên kết vòng
#include "data_structures/doubly_linked_list.h"   // Cài đặt danh sách liên kết đôi
#include "data_structures/binary_search_tree.h"   // Cài đặt cây nhị phân tìm kiếm

// Algorithms
#include "algorithms/sorting.h"         // Các thuật toán sắp xếp
#include "algorithms/knights_tour.h"    // Bài toán Mã Đi Tuần

#endif // STUDENT_LIBRARY_H
