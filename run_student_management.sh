#!/bin/bash

# Script để biên dịch và chạy chương trình Student Management System
# Tác giả: Tu Thanh Nguyen

echo "===== HỆ THỐNG QUẢN LÝ SINH VIÊN ====="
echo "Đang biên dịch chương trình..."

# Kiểm tra lỗi biên dịch
g++ main.cpp -o student_management

# Kiểm tra kết quả của lệnh biên dịch
if [ $? -eq 0 ]; then
    echo "Biên dịch thành công!"
    echo "Đang chạy chương trình..."
    echo "------------------------------"
    ./student_management
else
    echo "Lỗi: Biên dịch thất bại!"
fi