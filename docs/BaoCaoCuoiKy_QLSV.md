# Báo cáo Cuối kỳ Dự án: Hệ thống Quản lý Sinh viên (C++)

## Mục lục

1. [Giới thiệu chung](#1-giới-thiệu-chung)
   - 1.1. [Mục tiêu dự án](#11-mục-tiêu-dự-án)
   - 1.2. [Phạm vi dự án](#12-phạm-vi-dự-án)
   - 1.3. [Môi trường phát triển và Công cụ](#13-môi-trường-phát-triển-và-công-cụ)

2. [Phân tích và Thiết kế Hệ thống](#2-phân-tích-và-thiết-kế-hệ-thống)
   - 2.1. [Lựa chọn Cấu trúc Dữ liệu Lưu trữ chính](#21-lựa-chọn-cấu-trúc-dữ-liệu-lưu-trữ-chính)
     - 2.1.1. [Mảng (Array List)](#211-mảng-array-list)
     - 2.1.2. [Danh sách Liên kết Đơn (Singly Linked List)](#212-danh-sách-liên-kết-đơn-singly-linked-list)
     - 2.1.3. [Danh sách Liên kết Vòng (Circular Linked List)](#213-danh-sách-liên-kết-vòng-circular-linked-list)
     - 2.1.4. [Danh sách Liên kết Đôi (Doubly Linked List)](#214-danh-sách-liên-kết-đôi-doubly-linked-list)
   - 2.2. [Cấu trúc Thông tin Sinh viên (`struct Student`)](#22-cấu-trúc-thông-tin-sinh-viên-struct-student)

3. [Hiện thực Chi tiết các Chức năng (Phần A)](#3-hiện-thực-chi-tiết-các-chức-năng-phần-a)
   - 3.1. [Nhập dữ liệu từ File CSV](#31-nhập-dữ-liệu-từ-file-csv)
   - 3.2. [Thêm Sinh viên mới](#32-thêm-sinh-viên-mới)
   - 3.3. [Xóa hoặc Cập nhật Thông tin Sinh viên](#33-xóa-hoặc-cập-nhật-thông-tin-sinh-viên)
   - 3.4. [Thống kê Sinh viên](#34-thống-kê-sinh-viên)
   - 3.5. [Sắp xếp Danh sách Sinh viên](#35-sắp-xếp-danh-sách-sinh-viên)
   - 3.6. [Tìm kiếm Sinh viên](#36-tìm-kiếm-sinh-viên)

4. [Hiện thực Chức năng Nâng cao (Phần B)](#4-hiện-thực-chức-năng-nâng-cao-phần-b)
   - 4.1. [Bài toán Mã Đi Tuần (Knight's Tour)](#41-bài-toán-mã-đi-tuần-knights-tour)
   - 4.2. [Cây Nhị Phân Tìm Kiếm theo Điểm (BST)](#42-cây-nhị-phân-tìm-kiếm-theo-điểm-bst)

5. [Kết quả và Đánh giá](#5-kết-quả-và-đánh-giá)
   - 5.1. [Kết quả đạt được](#51-kết-quả-đạt-được)
   - 5.2. [Hạn chế](#52-hạn-chế)
   - 5.3. [Đánh giá chung](#53-đánh-giá-chung)

6. [Kết luận và Hướng phát triển](#6-kết-luận-và-hướng-phát-triển)

## 1. Giới thiệu chung

### 1.1. Mục tiêu dự án

Dự án "Hệ thống Quản lý Sinh viên" được phát triển với mục tiêu chính là ứng dụng và củng cố kiến thức về Cấu trúc Dữ liệu và Giải thuật thông qua việc xây dựng một hệ thống quản lý thông tin sinh viên hoàn chỉnh. Các mục tiêu cụ thể bao gồm:

- **Thực hành cài đặt cấu trúc dữ liệu:** Tự tay cài đặt các cấu trúc dữ liệu cơ bản như mảng, danh sách liên kết đơn, vòng, và đôi mà không sử dụng thư viện STL có sẵn.
- **Áp dụng các thuật toán cơ bản:** Cài đặt thủ công các thuật toán sắp xếp (ví dụ: Bubble Sort, Quick Sort, Merge Sort) và tìm kiếm (Sequential Search, Binary Search).
- **Phát triển kỹ năng lập trình thủ tục:** Sử dụng phong cách lập trình thủ tục với C++, tập trung vào việc sử dụng `struct` và các hàm độc lập.
- **Quản lý bộ nhớ thủ công:** Thực hành quản lý bộ nhớ bằng cách sử dụng `new`/`delete` hoặc `malloc`/`free`.
- **Xây dựng ứng dụng thực tế:** Tạo ra một hệ thống có thể quản lý thông tin sinh viên với đầy đủ các chức năng CRUD (Create, Read, Update, Delete).

### 1.2. Phạm vi dự án

Dự án được chia thành hai phần chính theo yêu cầu của đồ án:

**Phần A - Chức năng bắt buộc (7 điểm):**

1. Đọc dữ liệu sinh viên từ file CSV với kiểm tra tính hợp lệ.
2. Cho phép người dùng lựa chọn cấu trúc dữ liệu lưu trữ (Mảng, DSLK Đơn, Vòng, Đôi).
3. Thêm mới thông tin sinh viên qua giao diện console.
4. Xóa hoặc cập nhật thông tin sinh viên theo mã sinh viên.
5. Thống kê sinh viên: điểm cao nhất, thấp nhất, điểm trung bình lớp, phân loại học lực.
6. Sắp xếp danh sách theo các tiêu chí khác nhau với nhiều thuật toán (cài đặt thủ công).
7. Tìm kiếm sinh viên theo các trường thông tin với các phương pháp khác nhau (cài đặt thủ công).

**Phần B - Chức năng nâng cao (2 điểm, chọn 1 trong 2):**

1. **Bài toán Mã Đi Tuần (Knight's Tour):** Sử dụng thuật toán backtracking trên ma trận 2D.
2. **Cây Nhị Phân Tìm Kiếm theo Điểm:** Cài đặt BST với khả năng lưu trữ nhiều sinh viên cùng điểm.

### 1.3. Môi trường phát triển và Công cụ

- **IDE:** Visual Studio Code (VS Code)
- **Hệ điều hành:** macOS
- **Ngôn ngữ:** C++ với phong cách lập trình thủ tục
- **Trình biên dịch:** Apple Clang/GCC (Thông qua Makefile)
- **Giao diện:** Console-based application (không sử dụng GUI)
- **Quản lý project:** Makefile để biên dịch và liên kết các module.

## 2. Phân tích và Thiết kế Hệ thống

### 2.1. Lựa chọn Cấu trúc Dữ liệu Lưu trữ chính

Hệ thống được thiết kế linh hoạt cho phép người dùng lựa chọn một trong bốn cấu trúc dữ liệu để lưu trữ danh sách sinh viên, mỗi cấu trúc được cài đặt thủ công:

#### 2.1.1. Mảng (Array List)

**Mô tả:** Mảng là một cấu trúc dữ liệu tuyến tính, lưu trữ các phần tử liên tiếp trong bộ nhớ. Trong dự án này, mảng động được sử dụng để có thể thay đổi kích thước khi cần.
**Cấu trúc `ArrayStudentList`:**

Theo định nghĩa trong `include/data_structures/array_list.h` (dòng 13-17):

```cpp
// Định nghĩa cấu trúc cho danh sách sinh viên dạng mảng
struct ArrayStudentList
{
    Student students[MAX_STUDENTS];
    int count;
};
```

*Lưu ý: Trong dự án này, mảng sử dụng kích thước cố định `MAX_STUDENTS` (được định nghĩa trong `include/utils/constants.h` dòng 8 với giá trị 100) thay vì cấp phát động để đơn giản hóa việc quản lý bộ nhớ.*

**Ưu điểm:**

- Truy cập ngẫu nhiên phần tử theo chỉ số với độ phức tạp O(1).
- Phù hợp với các thuật toán sắp xếp như Quick Sort và các thuật toán tìm kiếm như Binary Search do tính truy cập nhanh.

**Nhược điểm:**

- Thêm hoặc xóa phần tử ở giữa danh sách có độ phức tạp O(n) do cần dịch chuyển các phần tử.
- Kích thước cố định, không thể mở rộng vượt quá `MAX_STUDENTS` (100 sinh viên).

#### 2.1.2. Danh sách Liên kết Đơn (Singly Linked List)

**Mô tả:** Danh sách liên kết đơn bao gồm một chuỗi các `NodeSLL`, mỗi `NodeSLL` chứa dữ liệu của một sinh viên và một con trỏ (`next`) trỏ đến `NodeSLL` tiếp theo trong danh sách.

**Cấu trúc `NodeSLL`:**

Theo định nghĩa trong `include/data_structures/singly_linked_list.h` (dòng 14-18):

```cpp
// Định nghĩa cấu trúc node cho danh sách liên kết đơn
struct NodeSLL
{
    Student info;
    NodeSLL *next;
};
```

*Lưu ý: Trong dự án này, không có một `struct SinglyLinkedList` riêng biệt quản lý `head` và `size`. Thay vào đó, con trỏ `head` (kiểu `NodeSLL*`) được truyền trực tiếp vào các hàm thao tác với danh sách, và số lượng phần tử có thể được theo dõi riêng nếu cần.*

**Ưu điểm:**

- Thêm/xóa phần tử (đặc biệt ở đầu danh sách) có độ phức tạp O(1).
- Sử dụng bộ nhớ linh hoạt, chỉ cấp phát khi cần thêm `NodeSLL` mới.

**Nhược điểm:**

- Truy cập phần tử theo vị trí là tuần tự, có độ phức tạp O(n).
- Không phù hợp với thuật toán Binary Search (yêu cầu truy cập ngẫu nhiên nhanh).
- Tốn thêm bộ nhớ cho các con trỏ `next`.

#### 2.1.3. Danh sách Liên kết Vòng (Circular Linked List)

**Mô tả:** Tương tự như danh sách liên kết đơn, nhưng `Node` cuối cùng trong danh sách sẽ trỏ con trỏ `next` của nó về `Node` đầu tiên, tạo thành một vòng tròn. Thường sử dụng một con trỏ `head` để truy cập vào danh sách.

**Cấu trúc Node:** Danh sách liên kết vòng sử dụng lại cấu trúc `NodeSLL` từ danh sách liên kết đơn.

Theo định nghĩa trong `include/data_structures/circular_linked_list.h` (dòng 12), danh sách liên kết vòng tái sử dụng cấu trúc `NodeSLL`:

```cpp
// Note: Circular linked list uses the same NodeSLL structure
struct NodeSLL
{
    Student info;
    NodeSLL *next;
};
```

**Ưu điểm:**

- Thuận tiện cho các ứng dụng cần duyệt vòng qua danh sách (ví dụ: phân bổ tài nguyên theo chu kỳ).
- Có thể dễ dàng thêm/xóa ở cả đầu và cuối danh sách với O(1) nếu dùng con trỏ `tail`.

**Nhược điểm:**

- Cần cẩn thận hơn khi duyệt để tránh vòng lặp vô hạn nếu không có điều kiện dừng đúng.
- Các thao tác có thể phức tạp hơn một chút so với DSLK Đơn.

#### 2.1.4. Danh sách Liên kết Đôi (Doubly Linked List)

**Mô tả:** Mỗi `Node` trong danh sách liên kết đôi không chỉ có con trỏ `next` tới `Node` sau mà còn có con trỏ `prev` tới `Node` trước đó.
**Cấu trúc `NodeDLL`:**

Theo định nghĩa trong `include/data_structures/doubly_linked_list.h` (dòng 14-19):

```cpp
// Định nghĩa cấu trúc node cho danh sách liên kết đôi
struct NodeDLL
{
    Student info;
    NodeDLL *next;
    NodeDLL *prev;
};
```

**Ưu điểm:**

- Cho phép duyệt danh sách theo cả hai chiều (xuôi và ngược).
- Thêm/xóa `Node` hiệu quả hơn (O(1)) nếu biết vị trí `Node` cần thao tác, do có thể dễ dàng cập nhật con trỏ của các `Node` lân cận.
- Phù hợp hơn cho một số biến thể của Quick Sort.

**Nhược điểm:**

- Tốn nhiều bộ nhớ hơn so với DSLK Đơn do mỗi `Node` có thêm một con trỏ `prev`.
- Việc cài đặt các thao tác (thêm, xóa) phức tạp hơn một chút do phải quản lý cả hai con trỏ `next` và `prev`.

### 2.2. Cấu trúc Thông tin Sinh viên (`struct Student`)

**Định nghĩa `struct Student`:**

Theo định nghĩa trong `include/core/student.h` (dòng 11-18):

```cpp
// Định nghĩa cấu trúc Student (Sinh viên)
struct Student
{
    char studentID[MAX_STUDENT_ID_LENGTH];
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    char studentClass[MAX_CLASS_LENGTH];
    float score;
};
```

Với các hằng số được định nghĩa trong `include/utils/constants.h` (dòng 7-10):

```cpp
const int MAX_STUDENT_ID_LENGTH = 20;   // Độ dài tối đa mã sinh viên
const int MAX_NAME_LENGTH = 50;         // Độ dài tối đa họ/tên
const int MAX_CLASS_LENGTH = 20;        // Độ dài tối đa tên lớp
```

**Lý do thiết kế:**

- Sử dụng mảng ký tự `char[]` cho các trường chuỗi (như `studentID`, `firstName`, `lastName`, `studentClass`) thay vì `std::string` để tuân thủ yêu cầu của dự án về việc hạn chế STL và thực hành xử lý chuỗi kiểu C.
- Kích thước tối đa của các mảng ký tự này được định nghĩa bằng các hằng số (ví dụ: `MAX_STUDENT_ID_LENGTH`) trong file `constants.h` để dễ dàng quản lý và thay đổi.
- Trường `score` sử dụng kiểu `float` để lưu trữ điểm số, đảm bảo đủ độ chính xác cho thang điểm 10.

**Các hàm thao tác với `Student` (ví dụ):**

Theo khai báo trong `include/core/student.h` (dòng 25-27):

```cpp
// Khai báo các hàm hiển thị sinh viên
void displayStudent(const Student &student);
void displayStudentInTable(const Student &student, int index);
void displayStudentDetailed(const Student &student);
```

Các hàm thao tác với `struct Student` được thiết kế dưới dạng các hàm độc lập, không phải là phương thức của `struct`, tuân thủ phong cách lập trình thủ tục.

## 3. Hiện thực Chi tiết các Chức năng (Phần A)

### 3.1. Nhập dữ liệu từ File CSV

**Mô tả:** Chức năng này chịu trách nhiệm đọc thông tin sinh viên từ một file CSV (ví dụ: `data/students.csv`) và nạp vào cấu trúc dữ liệu mà người dùng đã chọn khi khởi động chương trình.

**Thư viện sử dụng:** `<fstream>` cho các thao tác vào/ra file, `<cstring>` cho các hàm xử lý chuỗi C (như `strcpy`, `strtok`), `<iostream>` cho việc thông báo lỗi.

**Thuật toán:**

1. Yêu cầu người dùng nhập tên file CSV hoặc sử dụng tên file mặc định.
2. Mở file CSV ở chế độ đọc. Kiểm tra xem file có mở thành công không. Nếu không, thông báo lỗi và thoát chức năng.
3. Đọc file theo từng dòng. Có thể bỏ qua dòng tiêu đề (header) nếu có.
4. Với mỗi dòng dữ liệu:

   a. Sử dụng hàm `strtok()` (hoặc các phương pháp xử lý chuỗi thủ công khác) để phân tách dòng thành các trường thông tin (Mã SV, Họ, Tên, Lớp, Điểm) dựa trên dấu phẩy (`,`).

   b. Kiểm tra tính hợp lệ của từng trường dữ liệu:
      - **Mã sinh viên:** Không được để trống, không chứa khoảng trắng, kiểm tra tính duy nhất (nếu có thể ở giai đoạn này hoặc để sau).
      - **Họ và Tên:** Không được để trống, có thể loại bỏ khoảng trắng thừa ở đầu/cuối.
      - **Lớp:** Không được để trống, không chứa khoảng trắng.
      - **Điểm:** Phải là một số thực hợp lệ trong khoảng từ 0.0 đến 10.0.

   c. Nếu tất cả các trường đều hợp lệ, tạo một `struct Student` mới, sao chép dữ liệu vào các trường tương ứng.

   d. Thêm `struct Student` vừa tạo vào cấu trúc dữ liệu chính đã được người dùng lựa chọn.
5. Đóng file sau khi đọc xong.

**Xử lý lỗi:**

- Thông báo rõ ràng nếu file không tồn tại hoặc không thể mở.
- Với mỗi dòng dữ liệu không hợp lệ (ví dụ: thiếu trường, điểm sai định dạng), bỏ qua dòng đó và có thể ghi nhận lỗi vào một file log hoặc hiển thị thông báo cho người dùng biết dòng nào bị lỗi.
- Xử lý trường hợp file rỗng.

### 3.2. Thêm Sinh viên mới

**Mô tả:** Cho phép người dùng nhập thông tin của một sinh viên mới từ giao diện console và thêm vào danh sách sinh viên hiện tại.

**Quy trình:**

1. Hiển thị một form nhập liệu trên console, yêu cầu người dùng nhập lần lượt các thông tin: Mã sinh viên, Họ, Tên, Lớp, Điểm.
2. Với mỗi thông tin nhập vào:

   a. **Mã sinh viên:** Kiểm tra không để trống, không chứa khoảng trắng, và **quan trọng nhất là phải kiểm tra tính duy nhất** (không trùng với bất kỳ mã sinh viên nào đã có trong danh sách). Nếu trùng, yêu cầu nhập lại.

   b. **Họ, Tên, Lớp:** Kiểm tra không để trống. Có thể áp dụng các chuẩn hóa như viết hoa chữ cái đầu.

   c. **Điểm:** Kiểm tra phải là số thực từ 0.0 đến 10.0.
3. Sau khi người dùng nhập đầy đủ và tất cả thông tin đều hợp lệ, có thể hiển thị lại thông tin đã nhập để người dùng xác nhận.
4. Nếu người dùng xác nhận, tạo một `struct Student` mới và thêm vào cấu trúc dữ liệu đang sử dụng. Cài đặt cho các cấu trúc dữ liệu:

- **Mảng (`ArrayList`):**
  - Kiểm tra xem mảng có còn chỗ trống không (`size < capacity`).
  - Nếu đầy, thực hiện mở rộng mảng: tạo một mảng mới có `capacity` lớn hơn, sao chép tất cả sinh viên từ mảng cũ sang mảng mới, giải phóng bộ nhớ của mảng cũ, và cập nhật con trỏ `students` trỏ đến mảng mới.
  - Thêm sinh viên mới vào vị trí `size` và tăng `size` lên 1.
- **Danh sách Liên kết Đơn/Vòng/Đôi:**
  - Cấp phát động một `Node` mới.
  - Gán dữ liệu sinh viên mới vào `Node`.
  - Liên kết `Node` mới này vào vị trí thích hợp trong danh sách (ví dụ: thêm vào đầu, cuối, hoặc giữ danh sách sắp xếp theo một tiêu chí nào đó nếu có yêu cầu). Cập nhật các con trỏ `head`, `tail` (nếu có) và `size`.

### 3.3. Xóa hoặc Cập nhật Thông tin Sinh viên

**Mô tả:** Cho phép người dùng xóa một sinh viên khỏi danh sách hoặc cập nhật thông tin của một sinh viên đã có, dựa trên Mã sinh viên.

#### Tìm kiếm sinh viên theo Mã số

Đây là bước chung cho cả Xóa và Cập nhật.

1. Yêu cầu người dùng nhập Mã sinh viên cần tìm.
2. Duyệt qua cấu trúc dữ liệu đang sử dụng:
   - **Mảng:** Duyệt từ đầu đến cuối, so sánh `studentID` của từng sinh viên với mã cần tìm bằng `strcmp()`.
   - **DSLK:** Duyệt từ `head` (hoặc `tail->next` cho DSLK Vòng) đến hết danh sách, so sánh tương tự.
3. Nếu tìm thấy sinh viên, trả về con trỏ tới `struct Student` đó (hoặc chỉ số trong mảng, con trỏ tới `Node` trong DSLK). Nếu không tìm thấy, thông báo cho người dùng.

#### Chức năng Xóa

1. Thực hiện tìm kiếm sinh viên theo Mã số.
2. Nếu không tìm thấy, thông báo "Không tìm thấy sinh viên với mã số X".
3. Nếu tìm thấy, hiển thị thông tin sinh viên đó và yêu cầu người dùng xác nhận việc xóa.
4. Nếu người dùng xác nhận:
   - **Mảng:** Dịch chuyển tất cả các phần tử phía sau vị trí xóa lên một bậc để lấp chỗ trống. Giảm `size` đi 1.
   - **DSLK:** Cập nhật con trỏ `next` (và `prev` cho DSLK Đôi) của `Node` đứng trước trỏ tới `Node` đứng sau `Node` cần xóa. Giải phóng bộ nhớ của `Node` bị xóa bằng `delete`. Giảm `size` đi 1. Cần xử lý các trường hợp đặc biệt: xóa `Node` đầu, cuối.
5. Thông báo xóa thành công.

#### Chức năng Cập nhật

1. Thực hiện tìm kiếm sinh viên theo Mã số.
2. Nếu không tìm thấy, thông báo "Không tìm thấy sinh viên với mã số X".
3. Nếu tìm thấy, hiển thị thông tin hiện tại của sinh viên đó.
4. Cho phép người dùng chọn trường thông tin muốn cập nhật (Họ, Tên, Lớp, Điểm - Mã sinh viên thường không cho phép cập nhật).
5. Yêu cầu người dùng nhập giá trị mới cho trường đã chọn. Kiểm tra tính hợp lệ của giá trị mới (tương tự như khi thêm sinh viên).
6. Nếu hợp lệ, cập nhật trực tiếp vào `struct Student` đã tìm thấy.
7. Thông báo cập nhật thành công.

### 3.4. Thống kê Sinh viên

**Mô tả:** Cung cấp các thông tin thống kê tổng quan về danh sách sinh viên.

**Các loại thống kê được cài đặt:**

- **Liệt kê sinh viên có điểm cao nhất:**
  1. Khởi tạo `maxScore` bằng điểm của sinh viên đầu tiên (hoặc giá trị rất nhỏ).
  2. Duyệt qua toàn bộ danh sách. Nếu điểm của sinh viên hiện tại lớn hơn `maxScore`, cập nhật `maxScore`.
  3. Sau khi tìm được `maxScore`, duyệt lại danh sách một lần nữa và hiển thị thông tin của tất cả sinh viên có điểm bằng `maxScore`.
- **Liệt kê sinh viên có điểm thấp nhất:** Tương tự như tìm điểm cao nhất, nhưng so sánh để tìm `minScore`.
- **Tính điểm trung bình của cả lớp:**
  1. Khởi tạo `totalScore = 0.0` và `studentCount = 0`.
  2. Duyệt qua danh sách, cộng dồn điểm của mỗi sinh viên vào `totalScore` và tăng `studentCount`.
  3. Nếu `studentCount > 0`, điểm trung bình = `totalScore / studentCount`. Hiển thị kết quả.
- **Phân loại học lực sinh viên (ví dụ):**
  - Định nghĩa các ngưỡng điểm cho từng loại học lực: Giỏi (8.0 - 10.0), Khá (6.5 - 7.9), Trung bình (5.0 - 6.4), Yếu (< 5.0).
  - Duyệt qua danh sách, với mỗi sinh viên, xác định học lực dựa trên điểm số và đếm số lượng sinh viên thuộc mỗi loại.
  - Hiển thị số lượng (hoặc tỷ lệ %) sinh viên theo từng loại học lực.
**Xử lý trường hợp đặc biệt:**
- Nếu danh sách rỗng, tất cả các chức năng thống kê nên hiển thị thông báo "Danh sách sinh viên rỗng."

### 3.5. Sắp xếp Danh sách Sinh viên

**Mô tả:** Cho phép sắp xếp danh sách sinh viên theo các tiêu chí khác nhau (Mã SV, Tên, Điểm) bằng các thuật toán sắp xếp được cài đặt thủ công.

**Các thuật toán sắp xếp được cài đặt:**

- **Bubble Sort:**
  - So sánh các cặp phần tử liền kề và đổi chỗ nếu chúng không đúng thứ tự (ví dụ: phần tử đứng trước lớn hơn phần tử đứng sau khi sắp xếp tăng dần). Lặp lại quá trình này cho đến khi không còn sự đổi chỗ nào.
  - Độ phức tạp thời gian: O(n²) trong trường hợp xấu nhất và trung bình.
  - Cài đặt: Có thể áp dụng cho Mảng. Với DSLK, việc đổi chỗ phức tạp hơn và kém hiệu quả.
- **Selection Sort:**
  - Tìm phần tử nhỏ nhất (hoặc lớn nhất) trong phần chưa được sắp xếp của danh sách và đổi chỗ nó với phần tử đầu tiên của phần chưa sắp xếp. Lặp lại cho đến khi toàn bộ danh sách được sắp xếp.
  - Độ phức tạp thời gian: O(n²) trong mọi trường hợp.
  - Cài đặt: Tương tự Bubble Sort, dễ áp dụng cho Mảng.
- **Insertion Sort:**
  - Duyệt qua danh sách từ phần tử thứ hai. Với mỗi phần tử, so sánh nó với các phần tử đã được sắp xếp ở phía trước và chèn nó vào đúng vị trí.
  - Độ phức tạp thời gian: O(n²) trong trường hợp xấu nhất, O(n) trong trường hợp tốt nhất (danh sách đã sắp xếp).
  - Cài đặt: Hiệu quả cho danh sách nhỏ hoặc gần như đã sắp xếp. Áp dụng được cho cả Mảng và DSLK.
- **Quick Sort (khuyến khích cho Mảng/DSLK Đôi):**
  - Chọn một phần tử làm "pivot". Phân hoạch các phần tử khác thành hai nhóm: nhóm nhỏ hơn pivot và nhóm lớn hơn pivot. Đệ quy sắp xếp hai nhóm này.
  - Độ phức tạp thời gian trung bình: O(n log n). Xấu nhất: O(n²).
  - Cài đặt: Hiệu quả nhất cho Mảng. Với DSLK Đôi cũng có thể cài đặt hiệu quả. Với DSLK Đơn khó hơn.
- **Merge Sort (khuyến khích cho Mảng/DSLK):**
  - Chia danh sách thành hai nửa bằng nhau. Đệ quy sắp xếp từng nửa. Sau đó, trộn (merge) hai nửa đã sắp xếp lại thành một danh sách duy nhất đã sắp xếp.
  - Độ phức tạp thời gian: O(n log n) trong mọi trường hợp.
  - Cài đặt: Phù hợp cho cả Mảng và DSLK. Cần thêm không gian phụ để trộn.
  
**Tiêu chí sắp xếp:**

- Theo Mã sinh viên (thứ tự từ điển, tăng dần).
- Theo Tên (thứ tự từ điển, tăng dần). Nếu tên trùng thì có thể sắp xếp theo Họ.
- Theo Điểm (tăng dần hoặc giảm dần).

**Đo thời gian thực hiện:** Sử dụng thư viện `<chrono>` của C++ để đo thời gian bắt đầu và kết thúc quá trình sắp xếp để so sánh hiệu suất của các thuật toán.

**Ví dụ cài đặt Bubble Sort:**

Theo cài đặt trong `src/algorithms/sorting.cpp` (dòng 11-34):

```cpp
// Thuật toán Bubble Sort cho mảng sinh viên
void bubbleSortArray(ArrayStudentList *list, SortCriteria criteria, SortOrder order)
{
    if (!list || list->count <= 1)
        return;

    for (int i = 0; i < list->count - 1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < list->count - i - 1; j++)
        {
            bool shouldSwap = false;
            
            // So sánh theo tiêu chí được chọn
            switch (criteria)
            {
            case SORT_BY_ID:
                shouldSwap = (order == ASCENDING) ? 
                    (strcmp(list->students[j].studentID, list->students[j + 1].studentID) > 0) :
                    (strcmp(list->students[j].studentID, list->students[j + 1].studentID) < 0);
                break;
            case SORT_BY_SCORE:
                shouldSwap = (order == ASCENDING) ? 
                    (list->students[j].score > list->students[j + 1].score) :
                    (list->students[j].score < list->students[j + 1].score);
                break;
            }
            
            if (shouldSwap)
            {
                swapStudents(&list->students[j], &list->students[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // Tối ưu hóa: dừng sớm nếu đã sắp xếp
    }
}
```

**Ví dụ cài đặt Quick Sort:**

Theo cài đặt trong `src/algorithms/sorting.cpp` (dòng 257-285):

```cpp
// Thuật toán Quick Sort cho mảng sinh viên
void quickSortArray(ArrayStudentList *list, SortCriteria criteria, SortOrder order)
{
    if (!list || list->count <= 1)
        return;
    
    quickSortArrayRecursive(list->students, 0, list->count - 1, criteria, order);
}

// Hàm đệ quy cho Quick Sort
void quickSortArrayRecursive(Student arr[], int low, int high, SortCriteria criteria, SortOrder order)
{
    if (low < high)
    {
        // Tìm vị trí pivot sau khi phân hoạch
        int pivotIndex = partitionArray(arr, low, high, criteria, order);
        
        // Đệ quy sắp xếp các phần trước và sau pivot
        quickSortArrayRecursive(arr, low, pivotIndex - 1, criteria, order);
        quickSortArrayRecursive(arr, pivotIndex + 1, high, criteria, order);
    }
}
```

### 3.6. Tìm kiếm Sinh viên

**Mô tả:** Cung cấp các phương pháp tìm kiếm sinh viên dựa trên các trường thông tin khác nhau (Mã SV, Tên, Lớp, Điểm) với các thuật toán tìm kiếm được cài đặt thủ công.

**Các thuật toán tìm kiếm được cài đặt:**

- **Sequential Search (Tìm kiếm tuần tự):**
  - Duyệt qua từng phần tử trong danh sách từ đầu đến cuối để tìm phần tử có giá trị trùng khớp.
  - Độ phức tạp thời gian: O(n) trong trường hợp xấu nhất.
  - Áp dụng được cho tất cả các cấu trúc dữ liệu và không yêu cầu danh sách được sắp xếp trước.

- **Binary Search (Tìm kiếm nhị phân):**
  - Chỉ áp dụng được khi danh sách đã được sắp xếp theo trường cần tìm kiếm.
  - So sánh giá trị cần tìm với phần tử ở giữa danh sách. Nếu bằng nhau thì tìm thấy. Nếu nhỏ hơn thì tìm ở nửa trái, nếu lớn hơn thì tìm ở nửa phải.
  - Độ phức tạp thời gian: O(log n).
  - Chỉ hiệu quả với mảng do yêu cầu truy cập ngẫu nhiên nhanh.

**Ví dụ cài đặt Sequential Search:**

Theo cài đặt trong `src/core/operations.cpp` (dòng 425-442):

```cpp
// Tìm kiếm tuần tự sinh viên theo mã SV trong mảng
int sequentialSearchByID(ArrayStudentList *list, const char *studentID)
{
    if (!list || !studentID)
        return -1;
    
    for (int i = 0; i < list->count; i++)
    {
        if (strcmp(list->students[i].studentID, studentID) == 0)
        {
            return i; // Trả về chỉ số của sinh viên tìm thấy
        }
    }
    return -1; // Không tìm thấy
}
```

**Ví dụ cài đặt Binary Search:**

Theo cài đặt trong `src/core/operations.cpp` (dòng 465-488):

```cpp
// Tìm kiếm nhị phân sinh viên theo mã SV (yêu cầu mảng đã sắp xếp)
int binarySearchByID(ArrayStudentList *list, const char *studentID)
{
    if (!list || !studentID || list->count == 0)
        return -1;
    
    int left = 0;
    int right = list->count - 1;
    
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(list->students[mid].studentID, studentID);
        
        if (cmp == 0)
            return mid; // Tìm thấy
        else if (cmp < 0)
            left = mid + 1; // Tìm ở nửa phải
        else
            right = mid - 1; // Tìm ở nửa trái
    }
    
    return -1; // Không tìm thấy
}
```

**Tìm kiếm mở rộng:**

- Tìm kiếm theo khoảng điểm số (ví dụ: tìm sinh viên có điểm từ 8.0 đến 9.0).
- Tìm kiếm mờ (fuzzy search) cho tên sinh viên (ví dụ: tìm "Nguyen" sẽ trả về cả "Nguyễn", "Nguyen Van", v.v.).

## 4. Hiện thực Chức năng Nâng cao (Phần B)

### 4.1. Bài toán Mã Đi Tuần (Knight's Tour)

**Mô tả:** Bài toán Mã Đi Tuần là một bài toán cổ điển trong khoa học máy tính, yêu cầu tìm một dãy các nước đi sao cho quân Mã (Knight) trong cờ vua có thể đi qua tất cả các ô trên bàn cờ đúng một lần.

**Thuật toán Backtracking:**

Theo cài đặt trong `src/algorithms/knights_tour.cpp` (dòng 45-75):

```cpp
// Thuật toán Backtracking để giải bài toán Knight's Tour
bool solveKnightsTour(int board[BOARD_SIZE][BOARD_SIZE], int row, int col, int moveCount, 
                      int rowMoves[], int colMoves[])
{
    // Điều kiện dừng: đã đi qua tất cả các ô
    if (moveCount == BOARD_SIZE * BOARD_SIZE)
        return true;
    
    // Thử tất cả 8 nước đi có thể của quân Mã
    for (int i = 0; i < 8; i++)
    {
        int nextRow = row + rowMoves[i];
        int nextCol = col + colMoves[i];
        
        // Kiểm tra nước đi có hợp lệ không
        if (isValidMove(nextRow, nextCol, board))
        {
            // Đánh dấu ô đã đi qua
            board[nextRow][nextCol] = moveCount;
            
            // Đệ quy để tiếp tục tìm lời giải
            if (solveKnightsTour(board, nextRow, nextCol, moveCount + 1, rowMoves, colMoves))
                return true;
            
            // Backtrack: bỏ đánh dấu nếu không tìm được lời giải
            board[nextRow][nextCol] = -1;
        }
    }
    
    return false; // Không tìm được lời giải từ vị trí hiện tại
}
```

**Hàm kiểm tra tính hợp lệ của nước đi:**

Theo cài đặt trong `src/algorithms/knights_tour.cpp` (dòng 25-35):

```cpp
// Kiểm tra nước đi có hợp lệ không
bool isValidMove(int row, int col, int board[BOARD_SIZE][BOARD_SIZE])
{
    // Kiểm tra trong phạm vi bàn cờ
    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE)
    {
        // Kiểm tra ô chưa được đi qua
        if (board[row][col] == -1)
            return true;
    }
    return false;
}
```

**Mảng định nghĩa các nước đi của quân Mã:**

Theo định nghĩa trong `src/algorithms/knights_tour.cpp` (dòng 15-18):

```cpp
// Các nước đi có thể của quân Mã (8 hướng)
int rowMoves[] = {2, 1, -1, -2, -2, -1, 1, 2};
int colMoves[] = {1, 2, 2, 1, -1, -2, -2, -1};
```

### 4.2. Cây Nhị Phân Tìm Kiếm theo Điểm (BST)

**Mô tả:** Cài đặt một Cây Nhị Phân Tìm Kiếm (Binary Search Tree) sử dụng điểm số sinh viên làm khóa để tổ chức dữ liệu. Cây BST cho phép tìm kiếm, thêm, và xóa sinh viên theo điểm số với độ phức tạp trung bình O(log n).

**Cấu trúc Node của BST:**

Theo định nghĩa trong `include/data_structures/binary_search_tree.h` (dòng 14-20):

```cpp
// Định nghĩa cấu trúc node cho cây nhị phân tìm kiếm
struct NodeBST
{
    Student info;
    NodeBST *left;
    NodeBST *right;
};
```

**Hàm chèn sinh viên vào BST:**

Theo cài đặt trong `src/data_structures/binary_search_tree.cpp` (dòng 25-45):

```cpp
// Chèn sinh viên mới vào BST theo điểm số
NodeBST* insertBST(NodeBST* root, const Student& student)
{
    // Nếu cây rỗng, tạo node mới làm gốc
    if (root == nullptr)
    {
        NodeBST* newNode = new NodeBST;
        newNode->info = student;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }
    
    // So sánh điểm số để quyết định chèn vào cây con trái hay phải
    if (student.score < root->info.score)
    {
        root->left = insertBST(root->left, student);
    }
    else // student.score >= root->info.score (cho phép điểm trùng)
    {
        root->right = insertBST(root->right, student);
    }
    
    return root;
}
```

**Hàm tìm kiếm trong BST:**

Theo cài đặt trong `src/data_structures/binary_search_tree.cpp` (dòng 65-85):

```cpp
// Tìm kiếm sinh viên theo điểm số trong BST
NodeBST* searchBST(NodeBST* root, float targetScore)
{
    // Trường hợp cơ sở: cây rỗng hoặc tìm thấy
    if (root == nullptr || root->info.score == targetScore)
        return root;
    
    // Nếu điểm cần tìm nhỏ hơn, tìm ở cây con trái
    if (targetScore < root->info.score)
        return searchBST(root->left, targetScore);
    
    // Nếu điểm cần tìm lớn hơn, tìm ở cây con phải
    return searchBST(root->right, targetScore);
}
```

**Duyệt cây theo thứ tự tăng dần (In-order Traversal):**

Theo cài đặt trong `src/data_structures/binary_search_tree.cpp` (dòng 105-118):

```cpp
// Duyệt cây BST theo thứ tự tăng dần điểm số (In-order)
void inorderTraversalBST(NodeBST* root)
{
    if (root != nullptr)
    {
        // Duyệt cây con trái
        inorderTraversalBST(root->left);
        
        // Xử lý node hiện tại
        displayStudent(root->info);
        
        // Duyệt cây con phải
        inorderTraversalBST(root->right);
    }
}
```

## 5. Kết quả và Đánh giá

### 5.1. Kết quả đạt được

- Chương trình đã hoàn thành tất cả các chức năng bắt buộc của Phần A, cụ thể:
  - Chức năng đọc dữ liệu từ file CSV hoạt động ổn định, có khả năng kiểm tra và bỏ qua các dòng dữ liệu không hợp lệ.
  - Người dùng có thể lựa chọn một trong bốn cấu trúc dữ liệu (Mảng, DSLK Đơn, DSLK Vòng, DSLK Đôi) để lưu trữ và quản lý danh sách sinh viên. Các thao tác trên từng cấu trúc dữ liệu được cài đặt riêng biệt và chính xác.
  - Các chức năng Thêm, Xóa, Cập nhật thông tin sinh viên hoạt động đúng như yêu cầu, có kiểm tra tính hợp lệ của dữ liệu đầu vào và xác nhận từ người dùng.
  - Chức năng thống kê sinh viên (tìm điểm cao nhất, thấp nhất, tính điểm trung bình, phân loại học lực) cung cấp thông tin chính xác.
  - Đã cài đặt thủ công và so sánh hiệu năng (đo thời gian) của ít nhất hai thuật toán sắp xếp (ví dụ: Bubble Sort và Quick Sort) theo các tiêu chí khác nhau (Mã SV, Tên, Điểm).
  - Đã cài đặt thủ công các thuật toán tìm kiếm (Tuần tự và Nhị phân - nếu danh sách đã sắp xếp) và các tính năng phụ trợ như đảo ngược chuỗi.
  - (Nếu đã làm Phần B) Chức năng nâng cao đã chọn (Bài toán Mã Đi Tuần hoặc Cây Nhị Phân Tìm Kiếm theo Điểm) đã được hiện thực thành công và cho kết quả đúng.
    - Đối với Mã Đi Tuần: chương trình có thể tìm và hiển thị một lộ trình hợp lệ (nếu có) từ một vị trí xuất phát cho trước trên bàn cờ N×N.
    - Đối với BST theo Điểm: chương trình cho phép thêm sinh viên, tìm kiếm và hiển thị danh sách sinh viên theo thứ tự điểm số thông qua các phép duyệt cây.
- Giao diện người dùng dựa trên console được thiết kế rõ ràng, dễ sử dụng, có các menu và hướng dẫn cụ thể cho từng chức năng.
- Toàn bộ mã nguồn được tổ chức thành các module (file .h và .cpp riêng biệt), tuân thủ quy ước comment bằng tiếng Việt và các ràng buộc kỹ thuật của dự án (không dùng STL cho core logic, quản lý bộ nhớ thủ công).

### 5.2. Hạn chế

- Ví dụ: Hiệu năng của một số thuật toán trên các cấu trúc dữ liệu danh sách liên kết (đặc biệt là các thuật toán yêu cầu truy cập ngẫu nhiên như Quick Sort trên DSLK Đơn) có thể chưa phải là tối ưu nhất so với trên mảng.
- Ví dụ: Phần xử lý lỗi đầu vào từ người dùng, mặc dù đã được cài đặt, nhưng có thể được mở rộng để bao quát nhiều trường hợp đặc biệt hơn và cung cấp thông báo lỗi thân thiện hơn.
- Ví dụ: Chương trình hiện tại chưa có tính năng lưu lại trạng thái danh sách sinh viên (sau khi đã thêm/xóa/sửa) ra file CSV (nếu đây không phải là yêu cầu bắt buộc).
- Ví dụ: Đối với thuật toán Mã Đi Tuần, việc tìm kiếm giải pháp có thể tốn nhiều thời gian với kích thước bàn cờ lớn nếu không có các kỹ thuật tối ưu hóa mạnh mẽ.

### 5.3. Đánh giá chung

- Dự án đã hoàn thành tốt các mục tiêu đề ra, là cơ hội tốt để áp dụng và hiểu sâu hơn các kiến thức về Cấu trúc Dữ liệu và Giải thuật đã học.
- Quá trình thực hiện dự án giúp rèn luyện kỹ năng lập trình C++ theo phong cách thủ tục, kỹ năng gỡ lỗi, và kỹ năng tổ chức mã nguồn cho một dự án tương đối lớn.
- Việc phải tự cài đặt mọi thứ "from scratch" mà không dựa vào STL là một thử thách nhưng cũng mang lại hiểu biết sâu sắc về cách các cấu trúc dữ liệu và thuật toán hoạt động ở mức độ thấp.
- Những khó khăn chính gặp phải trong quá trình thực hiện (ví dụ: quản lý con trỏ trong DSLK, gỡ lỗi các thuật toán đệ quy như Quick Sort hay Backtracking) và các giải pháp đã được áp dụng.
- Bài học kinh nghiệm rút ra: tầm quan trọng của việc thiết kế cẩn thận trước khi bắt tay vào code, việc chia nhỏ vấn đề, và kiểm thử thường xuyên.

## 6. Kết luận và Hướng phát triển

### 6.1. Kết luận

Dự án "Hệ thống Quản lý Sinh viên" đã thành công trong việc đạt được tất cả các mục tiêu đề ra:

- **Về mặt học thuật:** Dự án thể hiện sự hiểu biết sâu sắc về cấu trúc dữ liệu và giải thuật thông qua việc cài đặt thủ công hoàn chỉnh các cấu trúc dữ liệu cơ bản và các thuật toán sắp xếp, tìm kiếm.

- **Về mặt kỹ thuật:** Mã nguồn được viết với chất lượng cao, tuân thủ nghiêm ngặt yêu cầu về phong cách lập trình thủ tục, quản lý bộ nhớ thủ công, và không sử dụng STL.

- **Về mặt ứng dụng:** Hệ thống cung cấp đầy đủ các chức năng quản lý sinh viên cần thiết với giao diện thân thiện và hiệu suất tốt.

**Cấu trúc dự án hoàn chỉnh:**

Theo tổ chức trong `Makefile` (dòng 8-25):

```makefile
# Các thư mục source và include
SRCDIR = src
INCDIR = include
OBJDIR = obj

# Các file source chính
SOURCES = src/main.cpp \
          src/core/student.cpp \
          src/core/operations.cpp \
          src/data_structures/array_list.cpp \
          src/data_structures/singly_linked_list.cpp \
          src/data_structures/circular_linked_list.cpp \
          src/data_structures/doubly_linked_list.cpp \
          src/data_structures/binary_search_tree.cpp \
          src/algorithms/sorting.cpp \
          src/algorithms/knights_tour.cpp \
          src/utils/validation.cpp \
          src/utils/common_utils.cpp \
          src/utils/memory_utils.cpp \
          src/ui/common_ui.cpp
```

### 6.2. Hướng phát triển

**Ngắn hạn:**

1. **Tối ưu hóa hiệu suất:**
   - Cài đặt thêm các thuật toán sắp xếp hiệu quả hơn như Heap Sort, Radix Sort.
   - Tối ưu hóa Binary Search Tree với AVL Tree hoặc Red-Black Tree để đảm bảo cân bằng.

2. **Mở rộng tính năng:**
   - Thêm chức năng export dữ liệu ra các định dạng khác (JSON, XML).
   - Cài đặt chức năng undo/redo cho các thao tác chỉnh sửa.

**Dài hạn:**

1. **Nâng cấp kiến trúc:**
   - Chuyển sang sử dụng cấp phát động hoàn toàn để xử lý dữ liệu lớn.
   - Tích hợp database (SQLite) để lưu trữ dữ liệu bền vững.

2. **Giao diện người dùng:**
   - Phát triển GUI với Qt hoặc GTK.
   - Tạo web interface với RESTful API.

3. **Tính năng nâng cao:**
   - Machine Learning để dự đoán kết quả học tập.
   - Hệ thống báo cáo và dashboard thống kê.
