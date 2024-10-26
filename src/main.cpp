#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> textBuffer = {""};
int cursorX = 0, cursorY = 0;

//zamienic to na define z ncurses
static constexpr uint8_t ENTER_CODE = 10;
static constexpr uint8_t TAB_CODE = 9;
static constexpr uint8_t BACKSPACE_CODE = 127;
static constexpr uint8_t ESCAPE_CODE = 127;

static constexpr uint8_t TAB_SIZE = 4;

void handleInput(int character) 
{
    switch (character) 
    {
        case ENTER_CODE:  
            textBuffer.insert(textBuffer.begin() + cursorY + 1, textBuffer[cursorY].substr(cursorX));
            textBuffer[cursorY] = textBuffer[cursorY].substr(0, cursorX);
            cursorY++;
            cursorX = 0;
            break;
        case TAB_CODE: 
            textBuffer[cursorY].insert(cursorX, "    ");
            cursorX += TAB_SIZE;
            break;
        case BACKSPACE_CODE: 
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
        default:
            textBuffer[cursorY].insert(cursorX, 1, character);
            cursorX++;
            break;
    }
}

void render() {
    clear();
    for (size_t i = 0; i < textBuffer.size(); ++i) 
    {
        mvprintw(i, 0, "%s", textBuffer[i].c_str());
    }
    move(cursorY, cursorX);
    refresh();
}

int main() {
    initscr();                
    raw();                   
    keypad(stdscr, TRUE);     
    noecho();               

    int character;
    while ((character = getch()) != ESCAPE_CODE) 
    { 
        if (character == KEY_LEFT) 
        {
            if (cursorX > 0) cursorX--;
        } 
        else if (character == KEY_RIGHT) 
        {
            if (cursorX < textBuffer[cursorY].length()) cursorX++;
        }
        else if (character == KEY_UP) 
        {
            if (cursorY > 0) 
            {
                cursorY--;
                cursorX = std::min(cursorX, (int)textBuffer[cursorY].length());
            }
        } 
        else if (character == KEY_DOWN) 
        {
            if (cursorY < textBuffer.size() - 1) 
            {
                cursorY++;
                cursorX = std::min(cursorX, (int)textBuffer[cursorY].length());
            }
        } else {
            handleInput(character);
        }
        render();
    }

    endwin(); 
    return 0;
}