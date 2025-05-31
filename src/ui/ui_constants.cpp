#include "../../include/ui/ui_constants.h"

// Định nghĩa các mã ANSI escape cho màu sắc cơ bản
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
const char *DIM = "\033[2m";
const char *REVERSE = "\033[7m";

// Màu nền
const char *BG_BLACK = "\033[40m";
const char *BG_RED = "\033[41m";
const char *BG_GREEN = "\033[42m";
const char *BG_YELLOW = "\033[43m";
const char *BG_BLUE = "\033[44m";
const char *BG_MAGENTA = "\033[45m";
const char *BG_CYAN = "\033[46m";
const char *BG_WHITE = "\033[47m";

// Màu sắc nâng cao (bright colors)
const char *BRIGHT_RED = "\033[91m";
const char *BRIGHT_GREEN = "\033[92m";
const char *BRIGHT_YELLOW = "\033[93m";
const char *BRIGHT_BLUE = "\033[94m";
const char *BRIGHT_MAGENTA = "\033[95m";
const char *BRIGHT_CYAN = "\033[96m";
const char *BRIGHT_WHITE = "\033[97m";

// Định nghĩa các màu cho các thành phần UI
const char *COLOR_RESET = "\033[0m";
const char *COLOR_HEADER = "\033[1;96m";        // Bold Bright Cyan
const char *COLOR_ERROR = "\033[1;91m";         // Bold Bright Red
const char *COLOR_SUCCESS = "\033[1;92m";       // Bold Bright Green
const char *COLOR_INFO = "\033[1;94m";          // Bold Bright Blue
const char *COLOR_WARNING = "\033[1;93m";       // Bold Bright Yellow
const char *COLOR_MENU_ITEM = "\033[37m";       // White
const char *COLOR_MENU_SELECTED = "\033[1;47;30m"; // Bold White background, black text
const char *COLOR_TABLE_HEADER = "\033[1;46;30m";  // Bold Cyan background, black text
const char *COLOR_TABLE_ROW_EVEN = "\033[48;5;235;37m";    // Dark gray background, white text
const char *COLOR_TABLE_ROW_ODD = "\033[48;5;237;37m";     // Lighter gray background, white text
const char *COLOR_INPUT_PROMPT = "\033[1;95m";     // Bold Bright Magenta
const char *COLOR_STATUS = "\033[2;36m";           // Dim Cyan
const char *COLOR_LOADING = "\033[1;33m";          // Bold Yellow

// Màu sắc mở rộng cho UI cải tiến
const char *COLOR_STATS = "\033[1;35m";            // Bold Magenta for stats
const char *COLOR_HIGHLIGHT = "\033[1;93;48;5;236m"; // Yellow on dark gray
const char *COLOR_SECONDARY = "\033[38;5;245m";    // Gray for secondary text
const char *COLOR_ACCENT = "\033[1;92m";           // Bright green accent
const char *COLOR_BORDER = "\033[38;5;240m";       // Gray border
const char *COLOR_BACKGROUND = "\033[48;5;234m";   // Dark background
const char *COLOR_MUTED = "\033[38;5;248m";        // Muted text

// Ký tự đặc biệt cho icons
const char *ICON_SUCCESS = "✓";
const char *ICON_ERROR = "✗";
const char *ICON_WARNING = "⚠";
const char *ICON_INFO = "ℹ";
const char *ICON_MENU = "☰";
const char *ICON_ARROW_RIGHT = "▶";
const char *ICON_ARROW_LEFT = "◀";
const char *ICON_BULLET = "•";
const char *ICON_LOADING = "⟳";
const char *ICON_STUDENT = "👤";
const char *ICON_SEARCH = "🔍";
const char *ICON_STATS = "📊";
const char *ICON_SORT = "⇅";
const char *ICON_EXIT = "🚪";

// Icons mở rộng
const char *ICON_HOME = "🏠";
const char *ICON_ADD = "➕";
const char *ICON_DELETE = "🗑️";
const char *ICON_EDIT = "✏️";
const char *ICON_FILE = "📄";
const char *ICON_FOLDER = "📁";
const char *ICON_SETTINGS = "⚙️";
const char *ICON_HELP = "❓";
const char *ICON_BOOK = "📚";
const char *ICON_STAR = "⭐";
const char *ICON_CHECK = "✅";
const char *ICON_CROSS = "❌";
const char *ICON_CLOCK = "🕐";
const char *ICON_SAVE = "💾";
const char *ICON_PRINT = "🖨️";
const char *ICON_GRAPH = "📈";
const char *ICON_TROPHY = "🏆";
const char *ICON_TARGET = "🎯";
const char *ICON_LIGHTBULB = "💡";
const char *ICON_GEAR = "⚙️";

// Box drawing characters
const char *BOX_HORIZONTAL = "─";
const char *BOX_VERTICAL = "│";
const char *BOX_TOP_LEFT = "┌";
const char *BOX_TOP_RIGHT = "┐";
const char *BOX_BOTTOM_LEFT = "└";
const char *BOX_BOTTOM_RIGHT = "┘";
const char *BOX_CROSS = "┼";
const char *BOX_T_DOWN = "┬";
const char *BOX_T_UP = "┴";
const char *BOX_T_LEFT = "┤";
const char *BOX_T_RIGHT = "├";
