#include "syntax_highlighter/syntax_highlighter.hpp"
#include "pattern_finder/pattern_finder.h"
#include "code_parser/lexer.hpp"
//#include "code_parser/cfg_builder.h"
//#include "static_analyzer/static_analyzer.hpp"
//#include "auto_complete/trie.hpp"
#include "../cmake/parser.tab.hpp"

#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <locale>
#include <cstdlib> 
#include <cstdio> 

std::vector<std::string> keywords = {
    "PROGRAM", "PROCEDURE", "IS", "IN", "IF", "END", "ENDIF", "ELSE", "THEN", "DO", "ENDWHILE", "REPEAT", "UNTIL", "WHILE", "READ", "WRITE"
};

std::vector<std::string> textBuffer = {""};
std::vector<std::pair<int , int>> highlighted_characters;
//std::vector<Error> analyzer_errors;
//std::vector<Error> compiler errors;


//static Trie autocomplete_trie;

extern int yyparse();
extern std::shared_ptr<Program> parsed_program;

//extern FILE *SA_yyin;
extern FILE *yyin;

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

bool saveToFile(const std::string& fileName) {
    if (fileName.substr(fileName.find_last_of(".") + 1) != "geb") {
        log_message("Error: File extension must be .geb\n");
        return false;
    }

    std::ofstream outFile(fileName);
    if (!outFile) {
        log_message("Error: Could not open file for writing: " + fileName + "\n");
        return false;
    }

    for (const auto& line : textBuffer) {
        outFile << line << '\n';
    }

    outFile.close();
    if (!outFile) {
        log_message("Error: Could not write to file: " + fileName + "\n");
        return false;
    }

    return true;
}

bool openFromFile(const std::string& fileName) {
    if (fileName.substr(fileName.find_last_of(".") + 1) != "geb") {
        log_message("Error: File extension must be .geb\n");
        return false;
    }

    std::ifstream inFile(fileName);
    if (!inFile) {
        log_message("Error: Could not open file for reading: " + fileName + "\n");
        return false;
    }

    textBuffer.clear(); // Clear existing content before loading new content
    std::string line;
    while (std::getline(inFile, line)) {
        textBuffer.push_back(line);
    }

    inFile.close();
    if (!inFile.eof() && inFile.fail()) {
        log_message("Error: Could not read file completely: " + fileName + "\n");
        return false;
    }

    return true;
}

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

void static_analysis()
{
    saveToFile("code.geb");
    FILE *source = fopen("code.geb", "r");
    //SA_yyin = source;
    yyin = source;

    auto x = yyparse();
    
    //AstOptimizer static_analyzer;

}

void autocomplete(std::string prefix)
{
    // const int LevenshteinDepth = 2;
    // const std::vector<std::string> suggestions = autocomplete_trie.searchWithLevenshteinDistance(prefix, LevenshteinDepth)

    // std::vector<std::string> results;

    //parse_code();
    //construct triee
    //analiza zywotnosci zmiennych i kontekstu
    //display sugesstions
}

std::string executeCommand(const std::string& command) {
    std::string result;
    char buffer[128];
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    try {
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

void compile_code(const std::string& inputFile, const std::string& outputFile)
{
    // saveToFile("a.geb");
    //  // Compile the input file using the compiler
    // std::string compileCommand = "./compiler/kompilator " + inputFile + " " + outputFile;
    // int compileStatus = system(compileCommand.c_str());

    // if (compileStatus != 0) {
    //     throw std::runtime_error("Compilation failed.");
    // }

    // // Execute the compiled output file using the virtual machine
    // std::string executeCommandStr = "./maszyna_wirtualna/maszyna-wirtualna " + outputFile;
    // return executeCommand(executeCommandStr);
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
            auto response = saveToFile(result);
        }
            break;

        case KEY_F(3):
        {
            std::string result = getUserInput("Enter filename to open: ");
            auto response = openFromFile(result);
        }
            break;

        case KEY_F(4):
        {
            std::string result = getUserInput("Enter phrase to find: ");
            if(result == "editor_reset")
            {
                highlighted_characters.clear();
            }
            else
            {
                find_pattern(result);
            }
        }
            break;
        case KEY_F(5):
            //static_analysis();
            break;
        case KEY_F(6):
            //autocomplete();
            break;
        case KEY_F(7):
            //compile_code();
            break;
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

// void print_error_on_line(unsigned line, unsigned offset)
// {
//     for(auto err : analyzer_errors)
//     {
//         if(err.line == line)
//         {
//             mvprintw(line, offset, "%s", err.message.c_str());
//         }
//     }
// }

void render() {
    clear();

    const int lineNumberWidth = 5; // Stała szerokość kolumny na numery linii
    
    for (size_t i = 0; i < textBuffer.size(); ++i) 
    {
        mvprintw(i, 0, "%*lu ", lineNumberWidth - 1, i + 1); 

        print_colored_line(i, lineNumberWidth, textBuffer[i]);
        //mvprintw(i, lineNumberWidth, "%s", textBuffer[i].c_str());

        //print_error_on_line(i, textBuffer[i].length() + 5 + 1);
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
    mvwprintw(menuWin, 1, 2, "Gebalang EDITOR | F1:Help | F2:Save | F3:Open | F4:Find | F5:Analyze | F6:Autocomplete | F7:Compile | ESC:Exit");

    wrefresh(menuWin);

    delwin(menuWin);        
}


int main() {

    // for(const auto& keyword : keywords) {
    // autocomplete_trie.insert(keyword);
    // }

    
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