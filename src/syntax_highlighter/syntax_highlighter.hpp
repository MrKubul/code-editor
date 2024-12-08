#ifndef SYNTAX_HIGHLIGHTER_HPP
#define SYNTAX_HIGHLIGHTER_HPP

#include <string>
#include <vector>

#define COLOR_KEYWORD 1
#define COLOR_IDENTIFIER 2
#define COLOR_NUMBER 3
#define COLOR_OPERATOR 4
#define COLOR_SYMBOL 5
#define COLOR_COMMENT 6
#define COLOR_WHITESPACE 7
#define COLOR_HIGHLIGHT 8


extern std::vector<std::pair<char, int>> colored_line;

void process_line(const std::string& line);

// Forward declaration of Flex functions
int SH_yylex();
void SH_yyset_in(FILE *in);


#endif // SYNTAX_HIGHLIGHTER_HPP