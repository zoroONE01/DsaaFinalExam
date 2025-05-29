#include "../../include/ui/ui_constants.h"

// Định nghĩa các mã ANSI escape cho màu sắc
const char *RESET = "\033[0m";
const char *RED = "\033[31m";
const char *GREEN = "\033[32m";
const char *YELLOW = "\033[33m";
const char *BLUE = "\033[34m";
const char *MAGENTA = "\033[35m";
const char *CYAN = "\033[36m";
const char *WHITE = "\033[37m";
const char *BOLD = "\033[1m";
const char *UNDERLINE = "\033[4m";

// Định nghĩa các màu cho các thành phần UI
const char *COLOR_RESET = "\033[0m";
const char *COLOR_HEADER = "\033[1;36m";  // Bold Cyan
const char *COLOR_ERROR = "\033[1;31m";   // Bold Red
const char *COLOR_SUCCESS = "\033[1;32m"; // Bold Green
const char *COLOR_INFO = "\033[1;34m";    // Bold Blue
const char *COLOR_WARNING = "\033[1;33m"; // Bold Yellow
