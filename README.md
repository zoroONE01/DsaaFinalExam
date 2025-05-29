# Hệ Thống Quản Lý Sinh Viên

Dự án Cấu trúc dữ liệu và Giải thuật - PTIT

## Giới thiệu

Đây là dự án quản lý sinh viên được phát triển theo yêu cầu của môn học Cấu trúc dữ liệu và Giải thuật tại PTIT. Chương trình cho phép quản lý danh sách sinh viên với nhiều cấu trúc dữ liệu khác nhau và áp dụng các thuật toán đã học trong môn học.

## Cấu trúc dự án

Dự án được tổ chức theo cấu trúc sau:

```
student_management/
├── include/                  # Thư mục chứa các file header (.h)
│   ├── algorithms/           # Định nghĩa các thuật toán
│   │   ├── knights_tour.h    # Thuật toán mã đi tuần
│   │   ├── searching_algorithms.h  # Các thuật toán tìm kiếm
│   │   └── sorting_algorithms.h    # Các thuật toán sắp xếp
│   ├── data_structures/      # Định nghĩa các cấu trúc dữ liệu
│   │   ├── array_list.h      # Danh sách mảng
│   │   ├── binary_search_tree.h    # Cây nhị phân tìm kiếm
│   │   ├── circular_linked_list.h  # Danh sách liên kết vòng
│   │   ├── doubly_linked_list.h    # Danh sách liên kết đôi
│   │   └── singly_linked_list.h    # Danh sách liên kết đơn
│   ├── ui/                   # Định nghĩa giao diện người dùng
│   │   ├── ui_common.h       # Các hàm giao diện chung
│   │   └── ui_constants.h    # Hằng số và màu sắc giao diện
│   ├── utils/                # Định nghĩa các tiện ích
│   │   ├── common_operations.h     # Các thao tác chung
│   │   ├── constants.h       # Các hằng số
│   │   ├── student.h         # Cấu trúc sinh viên
│   │   ├── utils.h           # Tiện ích chung
│   │   └── validation.h      # Kiểm tra đầu vào
│   └── student_management.h  # File header chính
├── src/                      # Thư mục chứa các file thực thi (.cpp)
│   ├── algorithms/           # Cài đặt các thuật toán
│   ├── data_structures/      # Cài đặt các cấu trúc dữ liệu
│   ├── ui/                   # Cài đặt giao diện người dùng
│   └── utils/                # Cài đặt các tiện ích
├── data/                     # Thư mục chứa dữ liệu
│   └── students.csv          # File dữ liệu sinh viên
├── main.cpp                  # File chính của chương trình
├── Makefile                  # File cấu hình biên dịch
└── build.sh                  # Script giúp sinh viên biên dịch và chạy chương trình
```

## Cấu trúc dữ liệu được cài đặt

1. **Danh sách mảng** (Array List) - Lưu trữ sinh viên trong mảng tĩnh
2. **Danh sách liên kết đơn** (Singly Linked List) - Mỗi node lưu trữ một sinh viên và con trỏ đến node tiếp theo
3. **Danh sách liên kết vòng** (Circular Linked List) - Danh sách liên kết đơn nhưng node cuối trỏ về node đầu
4. **Danh sách liên kết đôi** (Doubly Linked List) - Mỗi node có con trỏ đến node trước và node sau
5. **Cây tìm kiếm nhị phân** (Binary Search Tree) - Sắp xếp sinh viên theo điểm số

## Thuật toán được cài đặt

1. **Thuật toán sắp xếp**:
   - Bubble Sort
   - Insertion Sort
   - Selection Sort
   - Quick Sort
   - Merge Sort

2. **Thuật toán tìm kiếm**:
   - Tìm kiếm tuần tự (Sequential Search)
   - Tìm kiếm nhị phân (Binary Search)

3. **Bài toán nâng cao**:
   - Mã Đi Tuần (Knight's Tour)

## Cách sử dụng

### Biên dịch và chạy chương trình

Để biên dịch và chạy chương trình, bạn có thể sử dụng script `build.sh`:

```bash
# Cấp quyền thực thi cho script
chmod +x build.sh

# Chạy script
./build.sh
```

Hoặc sử dụng Makefile:

```bash
# Biên dịch
make

# Chạy chương trình
./student_management
```

### Sử dụng chương trình

Khi chạy chương trình, bạn sẽ thấy menu chính với các tính năng:

1. **Chọn cấu trúc dữ liệu**: Cho phép chọn cấu trúc dữ liệu để sử dụng
2. **Nhập dữ liệu từ file CSV**: Nhập dữ liệu sinh viên từ file
3. **Thêm sinh viên mới**: Nhập thông tin sinh viên mới từ bàn phím
4. **Xóa sinh viên theo mã**: Xóa sinh viên dựa trên mã sinh viên
5. **Cập nhật sinh viên theo mã**: Cập nhật thông tin sinh viên
6. **Hiển thị danh sách sinh viên**: Hiển thị danh sách sinh viên
7. **Tìm kiếm sinh viên theo mã**: Tìm kiếm sinh viên theo mã sinh viên
8. **Thống kê sinh viên**: Hiển thị các thống kê về sinh viên
9. **Sắp xếp sinh viên**: Sắp xếp danh sách sinh viên theo điểm số
10. **Bài toán Mã Đi Tuần**: Giải bài toán Mã Đi Tuần

## Yêu cầu hệ thống

- Hệ điều hành: macOS/Linux/Windows
- Trình biên dịch: g++ hoặc clang++ (hỗ trợ chuẩn C++11)
- Công cụ xây dựng: make

## Lưu ý cho sinh viên

- Dự án này giúp bạn hiểu cách cài đặt và sử dụng các cấu trúc dữ liệu và thuật toán cơ bản.
- Tất cả cài đặt được thực hiện theo phong cách lập trình thủ tục (procedural programming) để phù hợp với môn học CTDL&GT.
- Sinh viên có thể nghiên cứu mã nguồn để hiểu rõ hơn về các cấu trúc dữ liệu và thuật toán.

## Tác giả

- PTIT - Môn Cấu trúc dữ liệu và Giải thuật
