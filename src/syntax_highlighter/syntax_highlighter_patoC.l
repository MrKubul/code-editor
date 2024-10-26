%{
#include <ncurses.h> // do obsługi ncurses
#include <string>

void print_token(const std::string &token, int color_pair);

%}

// Definicja kolorów
%option noyywrap

%%

// Definicja tokenów
"if"|"else"|"while"     { print_token(yytext, 1); } // Słowa kluczowe
[0-9]+                  { print_token(yytext, 2); } // Liczby
[a-zA-Z_][a-zA-Z0-9_]*  { print_token(yytext, 3); } // Identyfikatory
.|\n                    { print_token(yytext, 4); } // Inne symbole

%%

// Funkcja do drukowania tokenów w kolorach
void print_token(const std::string &token, int color_pair) {
    attron(COLOR_PAIR(color_pair));
    printw("%s", token.c_str());
    attroff(COLOR_PAIR(color_pair));
}