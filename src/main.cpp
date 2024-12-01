#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <locale>

std::vector<std::string> textBuffer = {""};

static int cursorX = 0;
static int cursorY = 0;

static int rows = 0;
static int cols = 0;

static constexpr uint8_t KEY_TAB = 9;
static constexpr uint8_t TAB_SIZE = 4;

static constexpr uint8_t KEY_ESCAPE = 27;
static constexpr uint8_t KEY_DELETE = 127;
static constexpr uint8_t KEY_ENTER2 = 10;

std::string get_current_time() {
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
                            now.time_since_epoch()) % 1000;

    std::ostringstream oss;
    oss << std::put_time(std::localtime(&time_t_now), "%Y-%m-%d %H:%M:%S")
        << '.' << std::setfill('0') << std::setw(3) << milliseconds.count();
    return oss.str();
}

void log_message(const std::string& message) {
    std::ofstream log_file("log.txt", std::ios::app);
    if (log_file.is_open()) {
        log_file << "[" << get_current_time() << "] " << message << std::endl;
    }
}

// Function to update menu text dynamically
void updateMenuText(WINDOW* menuWin, const std::string& text) {
    werase(menuWin);               // Clear the menu window
    box(menuWin, 0, 0);            // Redraw the border
    mvwprintw(menuWin, 1, 2, "%s", text.c_str()); // Display the updated text
    wrefresh(menuWin);             // Refresh the window
}

// Function to capture user input inside the menu window
std::string getUserInput(std::string prompt) {
    std::string input;
    int ch;

         // Create the menu window at the bottom
    int menuHeight = 3;
    int menuWidth = COLS; // Full width of the terminal
    int menuStartY = LINES - menuHeight;
    int menuStartX = 0;

    WINDOW* menuWin = newwin(menuHeight, menuWidth, menuStartY, menuStartX);

    // Draw a border around the menu
    box(menuWin, 0, 0);

    // Add menu options
    mvwprintw(menuWin, 1, 2, "%s",prompt.c_str());

    // Refresh the menu window
    wrefresh(menuWin);

    while ((ch = wgetch(menuWin)) != '\n') { // Enter ends the input
        if (ch == KEY_DELETE) {
            // Handle backspace
            //
            if (!input.empty()) {
                input.pop_back();
                updateMenuText(menuWin, prompt + input + "_"); // Show the updated input
            }
        } else if (isprint(ch)) {
            // Add printable character to input
            input += ch;
            updateMenuText(menuWin, prompt + input + "_"); // Show the updated input
        }
    }
    delwin(menuWin);         // Delete the menu window
    return input;
}

void init_main_view()
{
    initscr();                
    raw();                   
    keypad(stdscr, TRUE);     
    noecho();  
}

void render_help_view() {
    //get new dimensions
    int rows, cols;
    getmaxyx(stdscr, rows, cols);  

    int win_height = rows / 2;
    int win_width = cols / 2;
    int start_y = (rows - win_height) / 2;
    int start_x = (cols - win_width) / 2;

    WINDOW *helpwin = newwin(win_height, win_width, start_y, start_x);
    box(helpwin, 0, 0);     

    // Display help content
    mvwprintw(helpwin, 1, 1, "Help Menu:");
    mvwprintw(helpwin, 2, 1, "JEBAC DZIEKANA CHUJA.");
    mvwprintw(helpwin, 2, 1, "Press Esc to go back.");
    mvwprintw(helpwin, 2, 1, "Press Esc to go back.");
    mvwprintw(helpwin, 2, 1, "Press Esc to go back.");
    mvwprintw(helpwin, 2, 1, "Press Esc to go back.");
    mvwprintw(helpwin, 2, 1, "Press Esc to go back.");

    wrefresh(helpwin);       // Refresh the help window

    int ch;
    while ((ch = getch()) != KEY_ESCAPE) {  // Wait for Esc key
        // Do nothing, just wait for Esc
    }

    delwin(helpwin);         // Delete the help window
}

void handleInput(int character) 
{
    switch (character) 
    {
        case KEY_ENTER2:  
            textBuffer.insert(textBuffer.begin() + cursorY + 1, textBuffer[cursorY].substr(cursorX));
            textBuffer[cursorY] = textBuffer[cursorY].substr(0, cursorX);
            cursorY++;
            cursorX = 0;
            break;
        case KEY_TAB: 
            textBuffer[cursorY].insert(cursorX, "    ");
            cursorX += TAB_SIZE;
            break;
        case KEY_BACKSPACE:
        case KEY_DELETE:
            if (cursorX > 0) 
            {
                textBuffer[cursorY].erase(cursorX - 1, 1);
                cursorX--;
            } 
            else if (cursorY > 0) 
            {
                cursorX = textBuffer[cursorY - 1].length();
                textBuffer[cursorY - 1] += textBuffer[cursorY];
                textBuffer.erase(textBuffer.begin() + cursorY);
                cursorY--;
            }
            break;
        case KEY_LEFT: 
            if (cursorX > 0) cursorX--;
            break;
        case KEY_RIGHT:
            if (cursorX < textBuffer[cursorY].length()) cursorX++;
            break;
        case KEY_UP: 
            if (cursorY > 0) 
            {
                cursorY--;
                cursorX = std::min(cursorX, static_cast<int>(textBuffer[cursorY].length()));
            }
            break; 
        case KEY_DOWN: 
            if (cursorY < textBuffer.size() - 1) 
            {
                cursorY++;
                cursorX = std::min(cursorX, static_cast<int>(textBuffer[cursorY].length()));
            }
            break;
        case KEY_F(1):
            render_help_view();
            break;
        case KEY_F(2):
        {
            std::string result = getUserInput("Enter filename where to save: ");
            //save(result);
        }
            break;

        case KEY_F(3):
        {
            std::string result = getUserInput("Enter filename to open: ");
            //open(result;)
        }
            break;

        case KEY_F(4):
        {
            std::string result = getUserInput("Enter phrase to find: ");
            //find(result);
        }
            break;
        case KEY_F(5):
        case KEY_F(6):
        case KEY_F(7):
        case KEY_F(8):
        case KEY_F(9):
        case KEY_F(10):
        case KEY_F(11):
        case KEY_F(12):
            break;
        default:
            textBuffer[cursorY].insert(cursorX, 1, character);
            cursorX++;
            break;
    }
}

void render() {
    clear();

    // // Concatenate code lines into a single string
    // std::string code_content;
    // for (const auto &line : code) {
    //     code_content += line + "\n";
    // }

    // // Pass the string to the lexer
    // yy_scan_string(code_content.c_str());
    // while (yylex()) {
    //     // Tokens are automatically added to the `tokens` vector
    // }

    const int lineNumberWidth = 5; // Stała szerokość kolumny na numery linii

    
    for (size_t i = 0; i < textBuffer.size(); ++i) 
    {
        mvprintw(i, 0, "%*lu ", lineNumberWidth - 1, i + 1); // i + 1, ponieważ numeracja zaczyna się od 1
        mvprintw(i, lineNumberWidth, "%s", textBuffer[i].c_str());
    }

    move(cursorY, cursorX + lineNumberWidth);
    refresh();

     // Create the menu window at the bottom
    int menuHeight = 3;
    int menuWidth = COLS; // Full width of the terminal
    int menuStartY = LINES - menuHeight;
    int menuStartX = 0;

    WINDOW* menuWin = newwin(menuHeight, menuWidth, menuStartY, menuStartX);

    // Draw a border around the menu
    box(menuWin, 0, 0);

    // Add menu options
    mvwprintw(menuWin, 1, 2, "GEBALANG CODE EDITOR | F1: Help  |  F2: Save  |  F3: Open  | F2: Find  | ESC: Exit");

    // Refresh the menu window
    wrefresh(menuWin);

    delwin(menuWin);         // Delete the menu window
}


int main() {
    setlocale(LC_ALL, "");
    init_main_view();  

    int character;
    while ((character = getch()) != KEY_ESCAPE)
    { 
        handleInput(character);
        render();
        refresh();
    }


    endwin(); 
    return 0;
}