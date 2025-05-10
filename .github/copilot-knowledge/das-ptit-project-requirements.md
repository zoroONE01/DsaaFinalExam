# Yêu cầu Đồ án Môn học Cấu trúc Dữ liệu và Giải thuật

## Thông tin Chung

* **Thời gian thực hiện:** 4 tuần
* **Hình thức:** Làm theo nhóm (4-5 sinh viên/nhóm)
* **Điểm:** Điểm đồ án là điểm chung cho cả nhóm

## I. Xây dựng Chương trình

### A. Phần Bắt buộc: Bài 1 (7 điểm)

Xây dựng chương trình bằng C++ với các chức năng sau. *Lưu ý: có kiểm tra lỗi nếu người dùng nhập sai khi thực hiện các chức năng.*

1. **(1 điểm)** Nhập danh sách sinh viên từ file Excel (DSSV.xlsx) hoặc CSV (DSSV.csv) với các thông tin:
    * Mã sinh viên (số + chữ)
    * Họ
    * Tên sinh viên
    * Lớp
    * Điểm
    * *Yêu cầu:* Báo lỗi nếu nhập trùng mã sinh viên. Kiểm tra khoảng trắng đầu cuối. Mã sinh viên và lớp không chứa khoảng trắng.
    * *Ví dụ thông tin sinh viên:*
        * Mã sinh viên: N20DCPT110
        * Họ: Nguyễn Ngọc
        * Tên sinh viên: Mai
        * Lớp: D23CQPT01
        * Điểm: 7.5

2. **(1 điểm)** Cho người dùng chọn cách thức lưu trữ danh sách sinh viên:
    * Mảng
    * Danh sách liên kết đơn
    * Danh sách liên kết vòng
    * Danh sách liên kết kép

3. **(1 điểm)** Xây dựng chức năng thêm mới sinh viên, cho phép nhập các thông tin: Mã sinh viên, Họ, Tên, Lớp, Điểm.

4. **(1 điểm)** Xây dựng chức năng cho phép xóa hoặc cập nhật thông tin sinh viên dựa theo Mã sinh viên nhập vào.

5. **(1 điểm)** Xây dựng chức năng cho người dùng chọn:
    * Liệt kê các sinh viên có điểm thấp nhất.
    * Liệt kê các sinh viên có điểm cao nhất.
    * Tính điểm trung bình của lớp.

6. **(1 điểm)** Xây dựng chức năng sắp xếp danh sách tăng dần:
    * **Chọn thuật toán sắp xếp:** Bubble Sort, Insertion Sort, Quick Sort, Selection Sort, Heap Sort, Merge Sort.
        * *Lưu ý:* Heap Sort và Quick Sort chỉ áp dụng khi kiểu lưu trữ là mảng hoặc danh sách liên kết kép.
    * **Chọn tiêu chí sắp xếp:** Mã SV, Tên, Điểm.
    * **Hiển thị:** Kết quả danh sách sau khi sắp xếp và thời gian thực hiện (giây/mili giây).

7. **(1 điểm)** Xây dựng chức năng tìm kiếm sinh viên:
    * **Nhập điều kiện tìm kiếm:** Dựa theo một trong các tiêu chí (Mã sinh viên, Họ, Tên, Lớp, Điểm), không phân biệt chữ hoa/thường.
    * **Phương pháp tìm kiếm:**
        * Tìm kiếm nhị phân nếu danh sách đã có thứ tự (mảng, danh sách liên kết kép).
        * Tìm kiếm tuần tự (vét cạn) nếu danh sách chưa có thứ tự.
    * **Tùy chọn:** Xuất đảo ngược thông tin họ và tên các sinh viên được tìm thấy. Nếu có, hiển thị thêm chuỗi này trong kết quả.
        * *Ví dụ:* Chuỗi đảo ngược họ và tên của "Nguyen Ngoc Mai" là "iaM cogN neyugN".
    * **Hiển thị kết quả:** In đậm/tô đỏ thông tin sinh viên tương ứng tiêu chí đang tìm kiếm. Hiển thị thời gian tìm kiếm (giây/mili giây).

### B. Phần Tự chọn (Chọn 1 trong 2 bài - 2 điểm)

#### **Bài 2.1: Mã đi tuần (2 điểm)**

Xây dựng chức năng bằng C++ cho phép người dùng nhập:

* Kích thước bàn cờ `n x n` (2 <= n <= 200).
* Vị trí xuất phát của con mã là ô (u,v) với u, v <= n-1.

Yêu cầu:

* Dùng mảng 2 chiều `n x n` để lưu trữ bàn cờ.
* Viết chương trình liệt kê các nước đi của con mã để nó đi qua tất cả các ô của bàn cờ, mỗi ô đúng 1 lần.
* Hiển thị kết quả các nước đi theo định dạng: `k : (u,v)` (con mã đi nước thứ k ở ô (u,v)).

#### **Bài 2.2: Cây nhị phân tìm kiếm (2 điểm)**

Xây dựng chức năng bằng C++ cho phép người dùng tạo cây nhị phân tìm kiếm từ danh sách sinh viên của Bài 1. Mỗi node trong cây gồm:

* `key`: điểm
* `Info`: danh sách các sinh viên cùng điểm.

Các chức năng:

1. Thêm 1 node mới.
2. Xóa 1 node bằng cách nhập giá trị `key` của node cần xóa.
3. Duyệt cây theo: PreOrder, InOrder, PostOrder (bằng đệ quy hoặc không đệ quy).
    * Hiển thị kết quả sau khi duyệt và thời gian thực hiện (giây/mili giây).

## II. Viết File Báo cáo (1 điểm)

1. Nội dung file báo cáo:
    * Tên các thành viên trong nhóm.
    * Trình bày tổng quan các nội dung đã làm được và chưa làm được.
    * Đối với các phần đã làm được: mô tả ngắn gọn các giải thuật/thuật toán áp dụng, có ảnh minh họa kết quả demo.
2. **Nộp báo cáo:** In dạng 2 mặt, nộp cho GVHD chậm nhất 1 tuần sau ngày báo cáo.
