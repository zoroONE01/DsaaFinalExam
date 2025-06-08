# Makefile cho Hệ thống Quản lý Sinh viên PTIT
CC = g++
CFLAGS = -Wall -g -Iinclude

# Thư mục
SRC_DIR = src
BUILD_DIR = build
TARGET = student_management

# Tự động tìm tất cả source files
SOURCES = $(shell find $(SRC_DIR) -name "*.cpp")
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Tạo thư mục build và các thư mục con cần thiết
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR) $(BUILD_DIR)/core $(BUILD_DIR)/data_structures $(BUILD_DIR)/algorithms $(BUILD_DIR)/ui $(BUILD_DIR)/utils

# Rule mặc định
all: $(TARGET)

# Rule để build chương trình
$(TARGET): $(BUILD_DIR) $(OBJECTS)
	@echo "===== Đang liên kết chương trình ====="
	$(CC) $(OBJECTS) -o $(TARGET)
	@echo "Biên dịch thành công!"

# Pattern rule để compile tất cả .cpp files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Đang biên dịch $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Dọn dẹp
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
	@echo "Đã dọn dẹp hoàn toàn."

# Build lại
rebuild: clean all

# Chạy chương trình
run: $(TARGET)
	@echo "===== CHẠY CHƯƠNG TRÌNH ====="
	./$(TARGET)

# Đảm bảo các rule này không bị nhầm với tên file
.PHONY: all clean rebuild run