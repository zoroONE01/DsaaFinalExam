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

# Source files
SOURCES = $(SRC_DIR)/main.cpp \
          $(SRC_DIR)/core/operations.cpp \
          $(SRC_DIR)/core/student.cpp \
          $(SRC_DIR)/data_structures/array_list.cpp \
          $(SRC_DIR)/data_structures/singly_linked_list.cpp \
          $(SRC_DIR)/data_structures/circular_linked_list.cpp \
          $(SRC_DIR)/data_structures/doubly_linked_list.cpp \
          $(SRC_DIR)/data_structures/binary_search_tree.cpp \
          $(SRC_DIR)/algorithms/sorting.cpp \
          $(SRC_DIR)/ui/common_ui.cpp \
          $(SRC_DIR)/utils/common_utils.cpp \
          $(SRC_DIR)/utils/validation.cpp \
          $(SRC_DIR)/utils/error_handling.cpp

# Object files
OBJECTS = $(BUILD_DIR)/main.o \
          $(BUILD_DIR)/operations.o \
          $(BUILD_DIR)/student.o \
          $(BUILD_DIR)/array_list.o \
          $(BUILD_DIR)/singly_linked_list.o \
          $(BUILD_DIR)/circular_linked_list.o \
          $(BUILD_DIR)/doubly_linked_list.o \
          $(BUILD_DIR)/binary_search_tree.o \
          $(BUILD_DIR)/sorting.o \
          $(BUILD_DIR)/common_ui.o \
          $(BUILD_DIR)/common_utils.o \
          $(BUILD_DIR)/validation.o \
          $(BUILD_DIR)/error_handling.o

# Tạo thư mục build nếu chưa có
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rule mặc định
all: $(BUILD_DIR) $(TARGET)

# Rule để build chương trình
$(TARGET): $(OBJECTS)
	@echo "===== HỆ THỐNG QUẢN LÝ SINH VIÊN ====="
	@echo "Đang liên kết chương trình..."
	$(CC) $(OBJECTS) -o $(TARGET)
	@echo "Biên dịch thành công!"

# Rule để compile main.cpp
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	@echo "Đang biên dịch main.cpp..."
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

# Rule để compile operations.cpp
$(BUILD_DIR)/operations.o: $(SRC_DIR)/core/operations.cpp
	@echo "Đang biên dịch operations.cpp..."
	$(CC) $(CFLAGS) -c $(SRC_DIR)/core/operations.cpp -o $(BUILD_DIR)/operations.o

# Rule để compile array_list.cpp
$(BUILD_DIR)/array_list.o: $(SRC_DIR)/data_structures/array_list.cpp
	@echo "Đang biên dịch array_list.cpp..."
	$(CC) $(CFLAGS) -c $(SRC_DIR)/data_structures/array_list.cpp -o $(BUILD_DIR)/array_list.o

# Rule để compile singly_linked_list.cpp
$(BUILD_DIR)/singly_linked_list.o: $(SRC_DIR)/data_structures/singly_linked_list.cpp
	@echo "Đang biên dịch singly_linked_list.cpp..."
	$(CC) $(CFLAGS) -c $(SRC_DIR)/data_structures/singly_linked_list.cpp -o $(BUILD_DIR)/singly_linked_list.o

# Rule để compile circular_linked_list.cpp
$(BUILD_DIR)/circular_linked_list.o: $(SRC_DIR)/data_structures/circular_linked_list.cpp
	@echo "Đang biên dịch circular_linked_list.cpp..."
	$(CC) $(CFLAGS) -c $(SRC_DIR)/data_structures/circular_linked_list.cpp -o $(BUILD_DIR)/circular_linked_list.o

# Rule để compile doubly_linked_list.cpp
$(BUILD_DIR)/doubly_linked_list.o: $(SRC_DIR)/data_structures/doubly_linked_list.cpp
	@echo "Đang biên dịch doubly_linked_list.cpp..."
	$(CC) $(CFLAGS) -c $(SRC_DIR)/data_structures/doubly_linked_list.cpp -o $(BUILD_DIR)/doubly_linked_list.o

# Rule để compile binary_search_tree.cpp
$(BUILD_DIR)/binary_search_tree.o: $(SRC_DIR)/data_structures/binary_search_tree.cpp
	@echo "Đang biên dịch binary_search_tree.cpp..."
	$(CC) $(CFLAGS) -c $(SRC_DIR)/data_structures/binary_search_tree.cpp -o $(BUILD_DIR)/binary_search_tree.o

# Rule để compile student.cpp
$(BUILD_DIR)/student.o: $(SRC_DIR)/core/student.cpp
	@echo "Đang biên dịch student.cpp..."
	$(CC) $(CFLAGS) -c $(SRC_DIR)/core/student.cpp -o $(BUILD_DIR)/student.o

# Rule để compile sorting.cpp
$(BUILD_DIR)/sorting.o: $(SRC_DIR)/algorithms/sorting.cpp
	@echo "Đang biên dịch sorting.cpp..."
	$(CC) $(CFLAGS) -c $(SRC_DIR)/algorithms/sorting.cpp -o $(BUILD_DIR)/sorting.o

# Rule để compile common_ui.cpp
$(BUILD_DIR)/common_ui.o: $(SRC_DIR)/ui/common_ui.cpp
	@echo "Đang biên dịch common_ui.cpp..."
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ui/common_ui.cpp -o $(BUILD_DIR)/common_ui.o

# Rule để compile common_utils.cpp
$(BUILD_DIR)/common_utils.o: $(SRC_DIR)/utils/common_utils.cpp
	@echo "Đang biên dịch common_utils.cpp..."
	$(CC) $(CFLAGS) -c $(SRC_DIR)/utils/common_utils.cpp -o $(BUILD_DIR)/common_utils.o

# Rule để compile validation.cpp
$(BUILD_DIR)/validation.o: $(SRC_DIR)/utils/validation.cpp
	@echo "Đang biên dịch validation.cpp..."
	$(CC) $(CFLAGS) -c $(SRC_DIR)/utils/validation.cpp -o $(BUILD_DIR)/validation.o

# Rule để compile error_handling.cpp
$(BUILD_DIR)/error_handling.o: $(SRC_DIR)/utils/error_handling.cpp
	@echo "Đang biên dịch error_handling.cpp..."
	$(CC) $(CFLAGS) -c $(SRC_DIR)/utils/error_handling.cpp -o $(BUILD_DIR)/error_handling.o

# Rule để dọn dẹp các file object và executable
clean:
	rm -f $(TARGET) $(BUILD_DIR)/*.o
	@echo "Đã dọn dẹp các file tạm thời."

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