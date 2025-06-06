#ifndef CONSTANTS_H
#define CONSTANTS_H

// ========== Hằng số chung cho hệ thống quản lý sinh viên ==========

// Giới hạn kích thước dữ liệu
const int MAX_STUDENTS = 100;           // Số lượng sinh viên tối đa trong mảng
const int MAX_STUDENT_ID_LENGTH = 20;   // Độ dài tối đa mã sinh viên
const int MAX_NAME_LENGTH = 50;         // Độ dài tối đa họ/tên
const int MAX_CLASS_LENGTH = 20;        // Độ dài tối đa tên lớp

// Giới hạn điểm số
const float MIN_SCORE = 0.0f;           // Điểm số tối thiểu
const float MAX_SCORE = 10.0f;          // Điểm số tối đa

// Phân loại điểm số
const float EXCELLENT_THRESHOLD = 8.0f; // Ngưỡng điểm xuất sắc
const float GOOD_THRESHOLD = 6.5f;      // Ngưỡng điểm khá
const float AVERAGE_THRESHOLD = 5.0f;   // Ngưỡng điểm trung bình

// Hằng số cho display
const int DISPLAY_WIDTH_ID = 12;        // Độ rộng hiển thị mã SV
const int DISPLAY_WIDTH_NAME = 15;      // Độ rộng hiển thị họ/tên
const int DISPLAY_WIDTH_CLASS = 18;     // Độ rộng hiển thị lớp
const int DISPLAY_WIDTH_SCORE = 9;      // Độ rộng hiển thị điểm

// Mã hủy bỏ nhập liệu
extern const char* CANCEL_INPUT_CODE;

#endif // CONSTANTS_H
