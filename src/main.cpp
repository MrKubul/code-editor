#include "syntax_highlighter/syntax_highlighter.hpp"
#include "pattern_finder/pattern_finder.h"

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
std::vector<std::pair<int , int>> highlighted_characters;

static int cursorX = 0;
static int cursorY = 0;

static int rows = 0;
static int cols = 0;

static constexpr uint8_t KEY_TAB = 9;
static constexpr uint8_t TAB_SIZE = 4;

static constexpr uint8_t KEY_ESCAPE = 27;
static constexpr uint8_t KEY_DELETE = 127;
static constexpr uint8_t KEY_ENTER2 = 10;

// void save_file(result);
// void open_file(result);
void find_pattern(std::string pattern)
{
    highlighted_characters.clear();
    int line_counter = 0;

    for(const auto &line : textBuffer)
    {
        std::vector<int> occurences = search(line, pattern);
        if(!occurences.empty())
        {
            for(int occurence : occurences)
            {
                for (int i = 0; i <= pattern.length(); ++i) {
                    highlighted_characters.emplace_back(occurence + i, line_counter); 
                }
            }
        }
        line_counter++;
    }
}

void highlight_patterns()
{
    for(auto character : highlighted_characters)
    {
        attron(COLOR_PAIR(COLOR_HIGHLIGHT));
        mvprintw(character.second, 5 + character.first, "%c", textBuffer[character.second][character.first]);
        attroff(COLOR_PAIR(COLOR_HIGHLIGHT));
    }
}

void init_colors() {
    start_color(); 

    init_pair(COLOR_KEYWORD, COLOR_BLUE, COLOR_BLACK);       // Keywords in blue
    init_pair(COLOR_IDENTIFIER, COLOR_GREEN, COLOR_BLACK);   // Identifiers in green
    init_pair(COLOR_NUMBER, COLOR_CYAN, COLOR_BLACK);        // Numbers in cyan
    init_pair(COLOR_OPERATOR, COLOR_MAGENTA, COLOR_BLACK);   // Operators in magenta
    init_pair(COLOR_SYMBOL, COLOR_YELLOW, COLOR_BLACK);      // Symbols in yellow
    init_pair(COLOR_COMMENT, COLOR_WHITE, COLOR_BLACK);      // Comments in white
    init_pair(COLOR_HIGHLIGHT, COLOR_WHITE, COLOR_YELLOW);
    init_pair(COLOR_WHITESPACE, COLOR_BLACK, COLOR_BLACK);   // Whitespace in black (invisible)
}

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

void updateMenuText(WINDOW* menuWin, const std::string& text) {
    werase(menuWin);              
    box(menuWin, 0, 0);           
    mvwprintw(menuWin, 1, 2, "%s", text.c_str()); 
    wrefresh(menuWin);             
}

std::string getUserInput(std::string prompt) {
    std::string input;
    int ch;

    int menuHeight = 3;
    int menuWidth = COLS; 
    int menuStartY = LINES - menuHeight;
    int menuStartX = 0;

    WINDOW* menuWin = newwin(menuHeight, menuWidth, menuStartY, menuStartX);

    box(menuWin, 0, 0);
    mvwprintw(menuWin, 1, 2, "%s",prompt.c_str());
    wrefresh(menuWin);

    while ((ch = wgetch(menuWin)) != '\n') 
    { 
        if (ch == KEY_DELETE) {
            if (!input.empty()) {
                input.pop_back();
                updateMenuText(menuWin, prompt + input + "_"); 
            }
        } else if (isprint(ch)) {
            input += ch;
            updateMenuText(menuWin, prompt + input + "_"); 
        }
    }
    delwin(menuWin);         
    return input;
}

void init_main_view()
{
    initscr();
    init_colors();                
    raw();                   
    keypad(stdscr, TRUE);     
    noecho();  
}

void render_help_view() {
    int rows, cols;
    getmaxyx(stdscr, rows, cols);  

    int win_height = rows / 2;
    int win_width = cols / 2;
    int start_y = (rows - win_height) / 2;
    int start_x = (cols - win_width) / 2;

    WINDOW *helpwin = newwin(win_height, win_width, start_y, start_x);
    box(helpwin, 0, 0);     

    mvwprintw(helpwin, 1, 1, "Zapelnic:");
    mvwprintw(helpwin, 2, 1, "JEBAC DZIEKANA CHUJA.");
    mvwprintw(helpwin, 3, 1, "T og owno.");
    mvwprintw(helpwin, 4, 1, "AAA.");
    mvwprintw(helpwin, 5, 1, "AAAAA.");
    mvwprintw(helpwin, 6, 1, "AAAAA.");

    wrefresh(helpwin);    

    int ch;
    while ((ch = getch()) != KEY_ESCAPE) {  
    }

    delwin(helpwin);         
}

void print_colored_line(int y, int x, std::string line)
{
    process_line(line);

    for (size_t i = 0; i < colored_line.size(); ++i)
    {
        switch(colored_line[i].second)
        {
            case COLOR_KEYWORD:
             attron(COLOR_PAIR(COLOR_KEYWORD));
             mvprintw(y, x+i, "%c", colored_line[i].first);
             attroff(COLOR_PAIR(COLOR_KEYWORD));
            break;
            case COLOR_IDENTIFIER:
             attron(COLOR_PAIR(COLOR_IDENTIFIER));
             mvprintw(y, x+i, "%c", colored_line[i].first);
             attroff(COLOR_PAIR(COLOR_IDENTIFIER));
            break;
            case COLOR_NUMBER:
             attron(COLOR_PAIR(COLOR_NUMBER));
             mvprintw(y, x+i, "%c", colored_line[i].first);
             attroff(COLOR_PAIR(COLOR_NUMBER));
            break;
            case COLOR_SYMBOL:
             attron(COLOR_PAIR(COLOR_SYMBOL));
             mvprintw(y, x+i, "%c", colored_line[i].first);
             attroff(COLOR_PAIR(COLOR_SYMBOL));
            break;
            case COLOR_OPERATOR:
             attron(COLOR_PAIR(COLOR_OPERATOR));
             mvprintw(y, x+i, "%c", colored_line[i].first);
             attroff(COLOR_PAIR(COLOR_OPERATOR));
            break;
            case COLOR_COMMENT:
             attron(COLOR_PAIR(COLOR_COMMENT));
             mvprintw(y, x+i, "%c", colored_line[i].first);
             attroff(COLOR_PAIR(COLOR_COMMENT));
            break;
            case COLOR_WHITESPACE:
             attron(COLOR_PAIR(COLOR_WHITESPACE));
             mvprintw(y, x+i, "%c", colored_line[i].first);
             attroff(COLOR_PAIR(COLOR_WHITESPACE));;
            break;
        }
    }
    colored_line.clear();
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
            //save_file(result);
        }
            break;

        case KEY_F(3):
        {
            std::string result = getUserInput("Enter filename to open: ");
            //open_file(result;)
        }
            break;

        case KEY_F(4):
        {
            std::string result = getUserInput("Enter phrase to find: ");
            find_pattern(result);
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

    const int lineNumberWidth = 5; // Stała szerokość kolumny na numery linii
    
    for (size_t i = 0; i < textBuffer.size(); ++i) 
    {
        mvprintw(i, 0, "%*lu ", lineNumberWidth - 1, i + 1); 

        print_colored_line(i, lineNumberWidth, textBuffer[i]);
        //mvprintw(i, lineNumberWidth, "%s", textBuffer[i].c_str());
    }

    highlight_patterns();

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