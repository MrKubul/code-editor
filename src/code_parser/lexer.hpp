#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include "ast.h"
#include "parser.tab.hpp"

FILE *yyin;

int yylex();
void yyset_in(FILE *in);
extern int yylineno;

#endif // LEXER_HPP