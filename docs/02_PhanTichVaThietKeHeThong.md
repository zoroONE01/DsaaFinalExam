# 2. Phân tích và Thiết kế Hệ thống

### 2.1. Lựa chọn Cấu trúc Dữ liệu Lưu trữ chính

Hệ thống được thiết kế linh hoạt cho phép người dùng lựa chọn một trong năm cấu trúc dữ liệu để lưu trữ danh sách sinh viên, mỗi cấu trúc được cài đặt thủ công:

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

Theo định nghĩa trong `include/data_structures/singly_linked_list.h` (dòng 14-17):

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

Theo định nghĩa trong `include/data_structures/circular_linked_list.h` (dòng 11), danh sách liên kết vòng tái sử dụng cấu trúc `NodeSLL`:

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

#### 2.1.5. Cây Tìm kiếm Nhị phân (Binary Search Tree)

**Mô tả:** Cây tìm kiếm nhị phân (BST) là một cấu trúc dữ liệu cây nhị phân trong đó mỗi `Node` có tối đa hai con: con trái và con phải. Đặc điểm quan trọng là giá trị của `Node` con trái luôn nhỏ hơn `Node` cha, và giá trị của `Node` con phải luôn lớn hơn `Node` cha.

**Cấu trúc `NodeBST`:**

Theo định nghĩa trong `include/data_structures/binary_search_tree.h` (dòng 16-22):

```cpp
// Định nghĩa cấu trúc node cho cây BST
struct NodeBST
{
    float key;                                // Điểm số làm khóa
    Student students[MAX_STUDENTS_PER_SCORE]; // Danh sách sinh viên có điểm số này
    int count;                                // Số lượng sinh viên trong node này
    NodeBST *left;                            // Con trỏ tới node con bên trái
    NodeBST *right;                           // Con trỏ tới node con bên phải
};
```

*Lưu ý: Trong thiết kế này, BST sử dụng điểm số (`score`) làm khóa để tổ chức cây. Mỗi `Node` có thể chứa nhiều sinh viên có cùng điểm số (tối đa `MAX_STUDENTS_PER_SCORE` = 10 sinh viên), điều này giúp xử lý trường hợp nhiều sinh viên có điểm giống nhau.*

**Ưu điểm:**

- Tìm kiếm, thêm, xóa có độ phức tạp trung bình O(log n) khi cây cân bằng.
- Duyệt cây theo thứ tự (in-order traversal) tự động cho kết quả đã được sắp xếp theo điểm số.
- Phù hợp cho các thao tác tìm kiếm theo khoảng điểm số (range search).
- Hỗ trợ nhiều sinh viên có cùng điểm số trong một `Node`, tiết kiệm bộ nhớ.

**Nhược điểm:**

- Trong trường hợp xấu nhất (cây không cân bằng), độ phức tạp có thể thoái hóa thành O(n).
- Cài đặt phức tạp hơn so với các cấu trúc dữ liệu tuyến tính.
- Cần bộ nhớ bổ sung cho việc lưu trữ con trỏ `left` và `right`.
- Giới hạn số lượng sinh viên cho mỗi điểm số (`MAX_STUDENTS_PER_SCORE` = 10).

### 2.2. Cấu trúc Thông tin Sinh viên (`struct Student`)

**Định nghĩa `struct Student`:**

Theo định nghĩa trong `include/core/student.h` (dòng 11-17):

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

Với các hằng số được định nghĩa trong `include/utils/constants.h` (dòng 8-11):

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
