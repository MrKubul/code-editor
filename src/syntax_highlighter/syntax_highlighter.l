%{
#include "syntax_highlighter.hpp"

#include <ncurses.h>
#include <string>
#include <vector>
#include <utility>

std::vector<std::pair<char, int>> colored_line; 

%}

%option noyywrap

%%

#.* { 
    for (char c : std::string(yytext)) {
        colored_line.emplace_back(c, COLOR_COMMENT); 
    } 
} 

"PROGRAM"|"PROCEDURE"|"IS"|"IN"|"IF"|"END"|"ENDIF"|"ELSE"|"THEN"|"DO"|"ENDWHILE"|"REPEAT"|"UNTIL"|"WHILE"|"READ"|"WRITE" { 
    for (char c : std::string(yytext)) {
        colored_line.emplace_back(c, COLOR_KEYWORD); 
    } 
}

"="|"!="|">"|"<"|">="|"<="|"+"|"-"|"*"|"/"|"%"|":=" { 
    for (char c : std::string(yytext)) {
        colored_line.emplace_back(c, COLOR_OPERATOR); 
    } 
}

"("|")"|"["|"]"|","|";" { 
    for (char c : std::string(yytext)) {
        colored_line.emplace_back(c, COLOR_SYMBOL); 
    }  
}

[_a-zA-Z]+ {
    for (char c : std::string(yytext)) {
        colored_line.emplace_back(c, COLOR_IDENTIFIER); 
    }   
}

[0-9]+ {
    for (char c : std::string(yytext)) {
        colored_line.emplace_back(c, COLOR_NUMBER); 
    } 
}

[ \t\n]+ {
    for (char c : std::string(yytext)) {
        colored_line.emplace_back(c, COLOR_WHITESPACE); 
    } 
}

. {
    printf("UNKNOWN: %s\n", yytext); 
}

%%

void process_line(const std::string& line) {
    YY_BUFFER_STATE buffer = yy_scan_string(line.c_str());
    yylex();
    yy_delete_buffer(buffer);
}