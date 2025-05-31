# Makefile cho Hệ thống Quản lý Sinh viên PTIT
# Biến compiler và flags
CC = g++
CFLAGS = -Wall -g -Iinclude

# Thư mục
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Tên chương trình
TARGET = student_management

# Tạo thư mục build nếu chưa có
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rule mặc định
all: $(BUILD_DIR) $(TARGET)

# Rule để build chương trình
$(TARGET): $(SRC_DIR)/main.cpp
	@echo "===== HỆ THỐNG QUẢN LÝ SINH VIÊN ====="
	@echo "Đang biên dịch chương trình..."
	$(CC) $(CFLAGS) $(SRC_DIR)/main.cpp -o $(TARGET)
	@echo "Biên dịch thành công!"

# Rule để dọn dẹp các file object và executable
clean:
	rm -f $(TARGET) *.o

# Rule để build lại hoàn toàn
rebuild: clean all

# Rule để chạy chương trình
run: $(TARGET)
	@echo "Đang chạy chương trình..."
	@echo "------------------------------"
	./$(TARGET)

# Rule tổng hợp (giống run_student_management.sh)
console: $(TARGET) run

# Rule để rebuild và chạy chương trình
rerun: rebuild run

# Đảm bảo các rule này không bị nhầm với tên file
.PHONY: all clean rebuild run console rerun