#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include "ast.h"
#include "parser.tab.hpp"

int yylex();
void yyset_in(FILE *in);
extern int yylineno;

#endif // LEXER_HPP