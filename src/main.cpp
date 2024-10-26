#include <ncurses.h>
#include <iostream>

int main() {
    initscr();           
    cbreak();           
    noecho();            

    printw("Hello, Ncurses in C++23!\n");
    printw("Press any key to exit...");

    refresh();    
    getch();           

    endwin();     

    return 0;
}