#ifndef CONSTANTS_H
#define CONSTANTS_H

// ========== Hằng số chung cho hệ thống quản lý sinh viên ==========

// Giới hạn kích thước dữ liệu
const int MAX_STUDENTS = 100;         // Số lượng sinh viên tối đa trong mảng
const int MAX_STUDENT_ID_LENGTH = 20; // Độ dài tối đa mã sinh viên
const int MAX_NAME_LENGTH = 50;       // Độ dài tối đa họ/tên
const int MAX_CLASS_LENGTH = 20;      // Độ dài tối đa tên lớp

// Giới hạn điểm số
const float MIN_SCORE = 0.0f;  // Điểm số tối thiểu
const float MAX_SCORE = 10.0f; // Điểm số tối đa

// Phân loại điểm số
const float EXCELLENT_THRESHOLD = 8.0f; // Ngưỡng điểm xuất sắc
const float GOOD_THRESHOLD = 6.5f;      // Ngưỡng điểm khá
const float AVERAGE_THRESHOLD = 5.0f;   // Ngưỡng điểm trung bình

// Hằng số cho display
const int DISPLAY_WIDTH_ID = 12;    // Độ rộng hiển thị mã SV
const int DISPLAY_WIDTH_NAME = 15;  // Độ rộng hiển thị họ/tên
const int DISPLAY_WIDTH_CLASS = 18; // Độ rộng hiển thị lớp
const int DISPLAY_WIDTH_SCORE = 9;  // Độ rộng hiển thị điểm

// Mã hủy bỏ nhập liệu
extern const char *CANCEL_INPUT_CODE;

// ========== Hằng số cho tìm kiếm sinh viên ==========

// Các tiêu chí tìm kiếm (phải khớp với SortCriteria để hỗ trợ binary search)
const int SEARCH_BY_STUDENT_ID = 1; // Tìm kiếm theo mã sinh viên (khớp với SORT_BY_STUDENT_ID)
const int SEARCH_BY_FIRST_NAME = 2; // Tìm kiếm theo tên
const int SEARCH_BY_LAST_NAME = 3;  // Tìm kiếm theo họ
const int SEARCH_BY_CLASS = 4;      // Tìm kiếm theo lớp
const int SEARCH_BY_SCORE = 5;      // Tìm kiếm theo điểm (NOTE: không khớp với SORT_BY_SCORE = 3)

// Các hằng số cho tương thích binary search
const int SEARCH_BY_NAME = 2;          // Tìm kiếm theo họ tên (khớp với SORT_BY_NAME)
const int SEARCH_SCORE_FOR_BINARY = 3; // Tìm kiếm theo điểm cho binary search (khớp với SORT_BY_SCORE)

// Tùy chọn hiển thị kết quả tìm kiếm
const int DISPLAY_NORMAL_NAME = 0;   // Hiển thị tên bình thường
const int DISPLAY_REVERSED_NAME = 1; // Hiển thị tên đảo ngược

// Màu sắc cho hiển thị kết quả
const char *const RED_COLOR = "\033[31m";  // Màu đỏ
const char *const BOLD_TEXT = "\033[1m";   // In đậm
const char *const RESET_COLOR = "\033[0m"; // Reset màu

#endif // CONSTANTS_H
