# Makefile cho Hệ Thống Quản Lý Sinh Viên
# Được tạo cho môn học Cấu Trúc Dữ Liệu và Giải Thuật

# Tên chương trình
TARGET = student_management

# Trình biên dịch
CC = g++

# Các thư mục
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj

# Cờ biên dịch
CFLAGS = -Wall -std=c++11 -I$(INCLUDE_DIR)

# Tìm tất cả các tệp nguồn .cpp
SRC_FILES = $(wildcard $(SRC_DIR)/*/*.cpp)
# Thêm tệp main.cpp
SRC_FILES += main.cpp
# Tạo danh sách các tệp đối tượng .o
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(filter-out main.cpp,$(SRC_FILES)))
OBJ_FILES += $(OBJ_DIR)/main.o

# Đích mặc định
all: directories $(TARGET)

# Tạo các thư mục cần thiết
directories:
	@mkdir -p $(OBJ_DIR)/algorithms
	@mkdir -p $(OBJ_DIR)/data_structures
	@mkdir -p $(OBJ_DIR)/ui
	@mkdir -p $(OBJ_DIR)/utils

# Quy tắc liên kết
$(TARGET): $(OBJ_FILES)
	$(CC) -o $@ $^

# Biên dịch main.cpp
$(OBJ_DIR)/main.o: main.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Quy tắc biên dịch các tệp nguồn trong thư mục con
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Dọn dẹp
clean:
	rm -rf $(OBJ_DIR)/* $(TARGET)

# Đảm bảo không có lỗi nếu tệp tin trùng tên với các đích
.PHONY: all clean directories
