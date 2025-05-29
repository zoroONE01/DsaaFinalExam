#!/bin/zsh
# Build script để biên dịch và chạy chương trình quản lý sinh viên
# Script này giúp sinh viên dễ dàng biên dịch và chạy chương trình mà không cần hiểu Makefile

# Màu sắc cho output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
BOLD='\033[1m'
NC='\033[0m' # No Color

# Banner
print_banner() {
    echo "${BLUE}${BOLD}"
    echo "╔════════════════════════════════════════════╗"
    echo "║         HỆ THỐNG QUẢN LÝ SINH VIÊN         ║"
    echo "╚════════════════════════════════════════════╝${NC}"
}

# Hiển thị menu
show_menu() {
    echo "${YELLOW}${BOLD}"
    echo "Các lựa chọn:"
    echo "  1. Biên dịch chương trình"
    echo "  2. Chạy chương trình"
    echo "  3. Biên dịch và chạy chương trình"
    echo "  4. Dọn dẹp các file đã biên dịch"
    echo "  5. Giải thích cấu trúc dự án"
    echo "  0. Thoát${NC}"
    echo ""
    echo -n "Nhập lựa chọn của bạn: "
}

# Biên dịch chương trình
build() {
    echo "${BLUE}Đang biên dịch chương trình...${NC}"
    make
    if [ $? -eq 0 ]; then
        echo "${GREEN}${BOLD}✓ Biên dịch thành công!${NC}"
    else
        echo "${RED}${BOLD}✗ Biên dịch thất bại!${NC}"
        return 1
    fi
}

# Chạy chương trình
run() {
    if [ ! -f "student_management" ]; then
        echo "${YELLOW}${BOLD}! Chương trình chưa được biên dịch. Đang biên dịch...${NC}"
        build
        if [ $? -ne 0 ]; then
            return 1
        fi
    fi
    
    echo "${BLUE}Đang chạy chương trình...${NC}"
    echo "${YELLOW}${BOLD}----------------------------------------${NC}"
    ./student_management
}

# Dọn dẹp
clean() {
    echo "${BLUE}Đang dọn dẹp các file đã biên dịch...${NC}"
    make clean
    echo "${GREEN}${BOLD}✓ Đã dọn dẹp!${NC}"
}

# Giải thích cấu trúc dự án
explain_structure() {
    echo "${BLUE}${BOLD}CẤU TRÚC DỰ ÁN${NC}"
    echo "${BOLD}include/${NC} - Chứa tất cả các file header (.h)"
    echo "  ${BOLD}data_structures/${NC} - Định nghĩa các cấu trúc dữ liệu (mảng, danh sách liên kết, ...)"
    echo "  ${BOLD}algorithms/${NC} - Định nghĩa các thuật toán (sắp xếp, tìm kiếm, ...)"
    echo "  ${BOLD}ui/${NC} - Định nghĩa giao diện người dùng"
    echo "  ${BOLD}utils/${NC} - Định nghĩa các tiện ích"
    echo ""
    echo "${BOLD}src/${NC} - Chứa tất cả các file thực thi (.cpp)"
    echo "  ${BOLD}data_structures/${NC} - Cài đặt các cấu trúc dữ liệu"
    echo "  ${BOLD}algorithms/${NC} - Cài đặt các thuật toán"
    echo "  ${BOLD}ui/${NC} - Cài đặt giao diện người dùng"
    echo "  ${BOLD}utils/${NC} - Cài đặt các tiện ích"
    echo ""
    echo "${BOLD}data/${NC} - Chứa các file dữ liệu (CSV, ...)"
    echo "${BOLD}main.cpp${NC} - File chính của chương trình"
    echo "${BOLD}Makefile${NC} - File cấu hình biên dịch"
    echo ""
    echo "Để chỉnh sửa code, sinh viên có thể mở file tương ứng trong thư mục include/ và src/"
}

# Main
print_banner
echo ""

if [ "$1" = "build" ]; then
    build
    exit 0
elif [ "$1" = "run" ]; then
    run
    exit 0
elif [ "$1" = "clean" ]; then
    clean
    exit 0
elif [ "$1" = "explain" ]; then
    explain_structure
    exit 0
elif [ "$1" = "all" ]; then
    build && run
    exit 0
fi

while true; do
    show_menu
    read choice
    echo ""
    
    case $choice in
        1)
            build
            ;;
        2)
            run
            ;;
        3)
            build && run
            ;;
        4)
            clean
            ;;
        5)
            explain_structure
            ;;
        0)
            echo "${GREEN}Cảm ơn bạn đã sử dụng chương trình!${NC}"
            exit 0
            ;;
        *)
            echo "${RED}Lựa chọn không hợp lệ!${NC}"
            ;;
    esac
    
    echo ""
    echo -n "Nhấn Enter để tiếp tục..."
    read
    clear
    print_banner
    echo ""
done