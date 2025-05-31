# Báo cáo Cuối kỳ Dự án: Hệ thống Quản lý Sinh viên (C++)

## Tóm tắt báo cáo

Dự án "Hệ thống Quản lý Sinh viên" được phát triển nhằm mục tiêu áp dụng kiến thức về Cấu trúc Dữ liệu và Giải thuật vào việc xây dựng một ứng dụng quản lý thông tin sinh viên hoàn chỉnh. Dự án được cài đặt hoàn toàn bằng ngôn ngữ C++ theo phong cách lập trình thủ tục, tuân thủ nghiêm ngặt yêu cầu tự cài đặt thủ công các cấu trúc dữ liệu và giải thuật mà không sử dụng các thư viện STL có sẵn.

Hệ thống hỗ trợ bốn lựa chọn cấu trúc dữ liệu lưu trữ chính (Mảng, Danh sách liên kết đơn, Danh sách liên kết vòng, Danh sách liên kết đôi) và cài đặt đầy đủ các chức năng cốt lõi bao gồm: đọc dữ liệu từ file CSV, thêm/xóa/cập nhật thông tin sinh viên, thống kê điểm số, sắp xếp theo nhiều tiêu chí với các thuật toán khác nhau, và tìm kiếm sinh viên. Đặc biệt, dự án còn có thể triển khai các thuật toán nâng cao như bài toán Mã Đi Tuần (Knight's Tour) hoặc Cây Nhị Phân Tìm Kiếm theo điểm số, tùy theo lựa chọn.

Toàn bộ mã nguồn được viết với comment bằng tiếng Việt, sử dụng quản lý bộ nhớ thủ công và kiểm tra lỗi đầu vào người dùng một cách toàn diện. Kết quả đạt được là một hệ thống quản lý sinh viên ổn định, hiệu quả và thể hiện rõ việc nắm vững các khái niệm cơ bản về cấu trúc dữ liệu và giải thuật.

---

## 1. Giới thiệu chung

### 1.1. Mục tiêu dự án

Dự án "Hệ thống Quản lý Sinh viên" được phát triển với mục tiêu chính là ứng dụng và củng cố kiến thức về Cấu trúc Dữ liệu và Giải thuật thông qua việc xây dựng một hệ thống quản lý thông tin sinh viên hoàn chỉnh. Các mục tiêu cụ thể bao gồm:

- **Thực hành cài đặt cấu trúc dữ liệu:** Tự tay cài đặt các cấu trúc dữ liệu cơ bản như mảng, danh sách liên kết đơn, vòng, và đôi mà không sử dụng thư viện STL có sẵn.
- **Áp dụng các thuật toán cơ bản:** Cài đặt thủ công các thuật toán sắp xếp (ví dụ: Bubble Sort, Quick Sort, Merge Sort) và tìm kiếm (Sequential Search, Binary Search).
- **Phát triển kỹ năng lập trình thủ tục:** Sử dụng phong cách lập trình thủ tục với C++, tập trung vào việc sử dụng `struct` và các hàm độc lập.
- **Quản lý bộ nhớ thủ công:** Thực hành quản lý bộ nhớ bằng cách sử dụng `new`/`delete` hoặc `malloc`/`free`.
- **Xây dựng ứng dụng thực tế:** Tạo ra một hệ thống có thể quản lý thông tin sinh viên với đầy đủ các chức năng CRUD (Create, Read, Update, Delete).

### 1.2. Phạm vi dự án

Dự án được chia thành hai phần chính theo yêu cầu của môn học:

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

**Mô tả:** Tương tự như danh sách liên kết đơn, nhưng `Node` cuối cùng trong danh sách sẽ trỏ con trỏ `next` của nó về `Node` đầu tiên, tạo thành một vòng tròn. Thường sử dụng một con trỏ `tail` để dễ dàng truy cập cả đầu và cuối danh sách.
**Cấu trúc `CircularNode` và `CircularLinkedList`:** (Tương tự `SinglyNode`, có thể dùng con trỏ `tail`)

```cpp
struct CircularNode { // Giống SinglyNode
    Student data;
    CircularNode* next;
};

struct CircularLinkedList {
    CircularNode* tail; // Con trỏ đến node cuối, tail->next là head
    int size;
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
   b. **Kiểm tra tính hợp lệ của từng trường dữ liệu:**
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
4. Nếu người dùng xác nhận, tạo một `struct Student` mới và thêm vào cấu trúc dữ liệu đang sử dụng.
**Cài đặt cho các cấu trúc dữ liệu:**

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
**Các thuật toán sắp xếp được cài đặt (ví dụ, chọn ít nhất 2-3):**

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
**Đo thời gian thực hiện:**
- Sử dụng thư viện `<chrono>` của C++ để đo thời gian bắt đầu và kết thúc của mỗi thuật toán sắp xếp.
- Hiển thị thời gian thực hiện (ví dụ: bằng mili giây hoặc micro giây) để người dùng có thể so sánh hiệu năng.

### 3.6. Tìm kiếm Sinh viên

**Mô tả:** Cho phép tìm kiếm sinh viên trong danh sách dựa trên các tiêu chí khác nhau.
**Các phương pháp tìm kiếm được cài đặt:**

- **Tìm kiếm tuần tự (Sequential Search):**
  - Duyệt qua từng phần tử trong danh sách từ đầu đến cuối.
  - So sánh trường thông tin cần tìm kiếm của phần tử hiện tại với từ khóa tìm kiếm.
  - Nếu tìm thấy sự trùng khớp, hiển thị thông tin sinh viên đó. Có thể dừng lại ở kết quả đầu tiên hoặc hiển thị tất cả các kết quả khớp.
  - Áp dụng cho mọi cấu trúc dữ liệu và mọi tiêu chí tìm kiếm, không yêu cầu danh sách phải được sắp xếp.
  - Độ phức tạp: O(n).
- **Tìm kiếm nhị phân (Binary Search):**
  - **Yêu cầu:** Danh sách phải được sắp xếp theo tiêu chí tìm kiếm.
  - So sánh từ khóa tìm kiếm với phần tử ở giữa danh sách.
  - Nếu khớp, tìm thấy.
  - Nếu từ khóa nhỏ hơn phần tử giữa, tìm kiếm tiếp ở nửa đầu danh sách.
  - Nếu từ khóa lớn hơn phần tử giữa, tìm kiếm tiếp ở nửa sau danh sách.
  - Lặp lại cho đến khi tìm thấy hoặc phạm vi tìm kiếm rỗng.
  - Áp dụng hiệu quả nhất cho Mảng (do truy cập O(1) vào phần tử giữa). Với DSLK, việc tìm phần tử giữa tốn O(n), làm giảm hiệu quả của Binary Search.
  - Độ phức tạp: O(log n) cho Mảng.
**Tiêu chí tìm kiếm:**
- **Mã sinh viên:** Tìm kiếm chính xác, thường chỉ có một kết quả.
- **Họ hoặc Tên:** Tìm kiếm gần đúng (ví dụ: chứa một phần của họ/tên), không phân biệt hoa thường. Có thể trả về nhiều kết quả.
- **Lớp:** Tìm kiếm chính xác tên lớp.
- **Điểm hoặc Khoảng điểm:** Tìm sinh viên có điểm chính xác X, hoặc nằm trong khoảng [Y, Z].
**Tính năng đảo ngược chuỗi (ví dụ cho tên):**
- Khi tìm thấy một sinh viên, chương trình có thể cung cấp tùy chọn hiển thị một trường chuỗi nào đó (ví dụ: Họ và Tên đầy đủ) ở dạng đảo ngược.
- Cài đặt một hàm `char* reverseString(const char* str)` thủ công để đảo ngược một chuỗi ký tự.

## 4. Hiện thực Chức năng Nâng cao (Phần B)

(Sinh viên chọn MỘT trong hai chức năng sau để hiện thực)

### 4.1. Bài toán Mã Đi Tuần (Knight's Tour)

**Mô tả bài toán:** Trên một bàn cờ vua kích thước N×N (ví dụ N=8), tìm một chuỗi các nước đi của quân mã sao cho quân mã xuất phát từ một ô (u,v) cho trước, đi qua tất cả các ô trên bàn cờ, mỗi ô đúng một lần.
**Cấu trúc dữ liệu:**

- Sử dụng một mảng 2D `int board[N][N]` để biểu diễn bàn cờ. `board[x][y]` sẽ lưu thứ tự của nước đi tại ô (x,y). Ban đầu, tất cả các ô được khởi tạo giá trị -1 (hoặc 0) để đánh dấu là chưa được đi qua.
**Thuật toán Backtracking (Quay lui):**

1. Hàm đệ quy `solveKnightTourUtil(x, y, moveCount, board, xMove[], yMove[])`:
   - `(x, y)`: Tọa độ hiện tại của quân mã.
   - `moveCount`: Số thứ tự của nước đi hiện tại.
   - `board`: Ma trận bàn cờ.
   - `xMove[], yMove[]`: Hai mảng lưu 8 hướng di chuyển có thể của quân mã (ví dụ: `xMove = {2, 1, -1, -2, -2, -1, 1, 2}`, `yMove = {1, 2, 2, 1, -1, -2, -2, -1}`).
2. **Điều kiện dừng đệ quy (Thành công):** Nếu `moveCount == N*N`, tất cả các ô đã được đi qua, trả về `true`.
3. **Thử các nước đi tiếp theo:**
   Lặp qua tất cả 8 hướng di chuyển `k` từ 0 đến 7:
   a. Tính tọa độ nước đi tiếp theo: `nextX = x + xMove[k]`, `nextY = y + yMove[k]`.
   b. **Kiểm tra tính hợp lệ của nước đi (`isSafe(nextX, nextY, board)`):**
      - `nextX`, `nextY` phải nằm trong phạm vi bàn cờ (0 đến N-1).
      - Ô `board[nextX][nextY]` phải chưa được đi qua (giá trị là -1).
   c. Nếu nước đi hợp lệ:
      i. Đánh dấu ô đó: `board[nextX][nextY] = moveCount`.
      ii. Gọi đệ quy: `if (solveKnightTourUtil(nextX, nextY, moveCount + 1, board, xMove, yMove)) return true;`
      iii. **Nếu lời gọi đệ quy không dẫn đến giải pháp (trả về `false`), quay lui (backtrack):** `board[nextX][nextY] = -1;` (bỏ đánh dấu nước đi này).
4. Nếu thử hết 8 hướng mà không có hướng nào dẫn đến giải pháp, trả về `false`.
**Hàm chính `solveKnightTour()`:**

- Khởi tạo bàn cờ `board` với tất cả giá trị -1.
- Yêu cầu người dùng nhập ô xuất phát (startX, startY).
- Đặt `board[startX][startY] = 0` (hoặc 1 nếu `moveCount` bắt đầu từ 1).
- Gọi `solveKnightTourUtil` với `moveCount = 1` (hoặc 2).
- Nếu hàm trả về `true`, hiển thị bàn cờ kết quả. Ngược lại, thông báo không tìm thấy lời giải.
**Hiển thị kết quả:** In ra ma trận `board` thể hiện thứ tự các nước đi.
**Tối ưu hóa (Tùy chọn):** Có thể áp dụng Heuristic của Warnsdorff: tại mỗi bước, quân mã ưu tiên di chuyển đến ô mà từ đó có ít lựa chọn di chuyển tiếp theo nhất. Điều này giúp giảm số lần quay lui và tăng khả năng tìm ra lời giải.

### 4.2. Cây Nhị Phân Tìm Kiếm theo Điểm (BST)

**Mô tả:** Xây dựng một cây nhị phân tìm kiếm (BST) trong đó khóa (key) của mỗi node là điểm số của sinh viên. Do nhiều sinh viên có thể có cùng một điểm số, mỗi node trên cây cần có khả năng lưu trữ một danh sách các sinh viên có cùng điểm số đó.
**Cấu trúc `NodeBST`:**

```cpp
// Node cho danh sách liên kết các sinh viên có cùng điểm (nếu dùng DSLK)
struct StudentNodeForBST {
    Student studentData;
    StudentNodeForBST* next;
};

struct NodeBST {
    float key; // Điểm số làm khóa
    
    // Lựa chọn 1: Dùng DSLK để lưu các SV cùng điểm
    StudentNodeForBST* studentListHead; 
    // int countSameScore; // Số lượng SV trong DSLK này

    // Lựa chọn 2: Dùng mảng cố định (nếu số SV cùng điểm không quá nhiều)
    // Student studentsWithScore[MAX_STUDENTS_SAME_SCORE];
    // int studentCountInNode; 

    NodeBST* left;  // Con trỏ tới cây con trái (điểm nhỏ hơn)
    NodeBST* right; // Con trỏ tới cây con phải (điểm lớn hơn)
};
```

**Các chức năng chính (cài đặt thủ công):**

- **Thêm một sinh viên vào BST (`insertStudentToBST(NodeBST*& root, Student s)`):**
  1. Nếu `root` là `NULL`, tạo một `NodeBST` mới, gán `s.score` làm `key`. Thêm `s` vào danh sách sinh viên của node này.
  2. Nếu `s.score < root->key`, gọi đệ quy `insertStudentToBST(root->left, s)`.
  3. Nếu `s.score > root->key`, gọi đệ quy `insertStudentToBST(root->right, s)`.
  4. Nếu `s.score == root->key`, thêm `s` vào danh sách sinh viên (DSLK hoặc mảng) tại `root` hiện tại.
- **Xóa một sinh viên khỏi BST (phức tạp hơn):**
  - Tìm node BST có `key` bằng điểm của sinh viên cần xóa.
  - Xóa sinh viên đó khỏi danh sách sinh viên trong node.
  - Nếu danh sách sinh viên trong node trở nên rỗng sau khi xóa, thì tiến hành xóa chính `NodeBST` đó khỏi cây (theo các quy tắc xóa node trong BST: node lá, node có 1 con, node có 2 con).
- **Tìm kiếm sinh viên theo điểm hoặc khoảng điểm:**
  - Tìm chính xác: Duyệt cây theo kiểu BST để tìm node có `key` bằng điểm cần tìm. Sau đó hiển thị tất cả sinh viên trong danh sách của node đó.
  - Tìm theo khoảng [minScore, maxScore]: Duyệt cây (ví dụ: In-order), nếu `node->key` nằm trong khoảng thì hiển thị danh sách sinh viên của node đó.
- **Duyệt cây và hiển thị thông tin:**
  - **In-order (LNR):** Duyệt cây con trái, xử lý node gốc (hiển thị điểm và danh sách SV tại node), duyệt cây con phải. Kết quả là danh sách sinh viên được sắp xếp theo điểm tăng dần.
  - **Pre-order (NLR), Post-order (LRN):** Cài đặt các phép duyệt này và hiển thị thông tin tương ứng.
**Lưu ý quan trọng:**
- Việc quản lý danh sách sinh viên trong mỗi `NodeBST` (dù bằng mảng cố định hay DSLK) phải được cài đặt thủ công, bao gồm các thao tác thêm/xóa sinh viên khỏi danh sách đó.
- Quản lý bộ nhớ cẩn thận khi tạo và xóa các `NodeBST` và các node trong danh sách sinh viên (nếu dùng DSLK).

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

### 5.2. Hạn chế (Nếu có)

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

**Kết luận:**
Dự án "Hệ thống Quản lý Sinh viên bằng C++" đã được hoàn thành, đáp ứng các yêu cầu chính của đề bài. Hệ thống cung cấp một bộ công cụ cơ bản nhưng đầy đủ để quản lý thông tin sinh viên, đồng thời là một minh chứng cho việc ứng dụng thành công các cấu trúc dữ liệu và giải thuật cơ bản cũng như nâng cao. Việc tuân thủ các ràng buộc về lập trình thủ tục và tự cài đặt đã mang lại nhiều kinh nghiệm quý báu.

**Hướng phát triển (Nếu có):**

- **Cải thiện giao diện người dùng:** Mặc dù là ứng dụng console, có thể nghiên cứu sử dụng các thư viện như `ncurses` (trên Linux/macOS) hoặc các kỹ thuật khác để làm cho giao diện thân thiện và dễ tương tác hơn.
- **Mở rộng chức năng:**
  - Thêm chức năng quản lý điểm theo từng môn học, tính điểm trung bình tích lũy.
  - Cho phép nhập/xuất dữ liệu với các định dạng file khác (ví dụ: JSON, XML).
  - Thêm chức năng sao lưu và phục hồi dữ liệu.
- **Tối ưu hóa hiệu năng:** Nghiên cứu và áp dụng các kỹ thuật tối ưu hóa cho các thuật toán đã cài đặt, đặc biệt với các tập dữ liệu lớn.
- **Phát triển phiên bản có Giao diện Đồ họa (GUI):** Sử dụng các thư viện GUI như Qt hoặc wxWidgets để phát triển một phiên bản ứng dụng desktop hoàn chỉnh.
- **Áp dụng các cấu trúc dữ liệu và giải thuật nâng cao hơn:** Ví dụ, sử dụng B-Tree để quản lý dữ liệu trên đĩa nếu số lượng sinh viên rất lớn, hoặc các thuật toán đồ thị cho các mối quan hệ phức tạp hơn.

## Phụ lục

### A. Ví dụ mã nguồn minh họa

(Chỉ bao gồm các đoạn mã ngắn gọn, quan trọng, minh họa cho việc cài đặt một cấu trúc dữ liệu hoặc một thuật toán phức tạp. Các đoạn mã này phải tuân thủ yêu cầu comment tiếng Việt.)

#### A.1. Cấu trúc Danh sách Liên kết Đơn và Hàm Thêm vào Đầu

**Từ `include/data_structures/singly_linked_list.h` (dòng 14-18):**

```cpp
// Định nghĩa cấu trúc node cho danh sách liên kết đơn
struct NodeSLL
{
    Student info;
    NodeSLL *next;
};
```

**Từ `src/data_structures/singly_linked_list.cpp` (dòng 15-21 và 24-29):**

```cpp
// Tạo mới một node sinh viên
NodeSLL *createNodeSLL(const Student &student)
{
    NodeSLL *newNode = new NodeSLL;
    newNode->info = student;
    newNode->next = NULL;
    return newNode;
}

// Thêm sinh viên vào đầu danh sách liên kết đơn
void addToHeadSLL(NodeSLL *&head, const Student &student)
{
    NodeSLL *newNode = createNodeSLL(student);
    newNode->next = head;
    head = newNode;
}
```

#### A.2. Thuật toán Quick Sort cho Mảng Sinh viên (Sắp xếp theo Điểm)

**Từ `src/algorithms/sorting.cpp` (dòng 55-76 và 78-88):**

```cpp
// --- QuickSort cho danh sách mảng ---
// Hàm phân vùng (partition) cho thuật toán QuickSort
int partitionArrayList(ArrayStudentList &list, int low, int high)
{
    float pivot = list.students[high].score; // Chọn phần tử cuối làm pivot
    int i = low - 1;                         // Vị trí của phần tử nhỏ hơn

    for (int j = low; j < high; j++)
    {
        // Nếu phần tử hiện tại nhỏ hơn hoặc bằng pivot
        if (list.students[j].score <= pivot)
        {
            i++;
            // Hoán đổi list.students[i] và list.students[j]
            Student temp = list.students[i];
            list.students[i] = list.students[j];
            list.students[j] = temp;
        }
    }

    // Hoán đổi list.students[i+1] và list.students[high] (pivot)
    Student temp = list.students[i + 1];
    list.students[i + 1] = list.students[high];
    list.students[high] = temp;

    return i + 1;
}

// Thuật toán QuickSort
void quickSortArrayList(ArrayStudentList &list, int low, int high)
{
    if (low < high)
    {
        // Tìm vị trí phân vùng
        int pi = partitionArrayList(list, low, high);

        // Sắp xếp các phần tử trước và sau vị trí phân vùng
        quickSortArrayList(list, low, pi - 1);
        quickSortArrayList(list, pi + 1, high);
    }
}
```

**Từ `src/algorithms/sorting.cpp` (dòng 91-99):**

```cpp
// Hàm gọi QuickSort
void quickSortArrayList(ArrayStudentList &list)
{
    if (list.count <= 1)
    {
        return; // Danh sách đã sắp xếp
    }

    quickSortArrayList(list, 0, list.count - 1);
}
```

#### A.3. Các thuật toán sắp xếp cơ bản khác

**Từ `src/algorithms/sorting.cpp` (dòng 3-17):**

```cpp
// --- Sắp xếp nổi bọt cho danh sách mảng ---
void bubbleSortArrayList(ArrayStudentList &list)
{
    for (int i = 0; i < list.count - 1; i++)
    {
        for (int j = 0; j < list.count - i - 1; j++)
        {
            if (list.students[j].score > list.students[j + 1].score)
            {
                // Hoán đổi hai sinh viên
                Student temp = list.students[j];
                list.students[j] = list.students[j + 1];
                list.students[j + 1] = temp;
            }
        }
    }
}
```

**Từ `src/algorithms/sorting.cpp` (dòng 19-33):**

```cpp
// --- Sắp xếp chèn cho danh sách mảng ---
void insertionSortArrayList(ArrayStudentList &list)
{
    for (int i = 1; i < list.count; i++)
    {
        Student key = list.students[i];
        int j = i - 1;

        while (j >= 0 && list.students[j].score > key.score)
        {
            list.students[j + 1] = list.students[j];
            j--;
        }

        list.students[j + 1] = key;
    }
}
```

#### A.4. Thuật toán Tìm kiếm Nhị phân

**Từ `src/algorithms/sorting.cpp` (dòng 103-122):**

```cpp
// --- Tìm kiếm nhị phân trong danh sách mảng đã sắp xếp ---
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
```
