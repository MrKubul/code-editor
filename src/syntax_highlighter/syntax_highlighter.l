%{
#include <ncurses.h>
#include <string>

void print_token(const std::string &token, int color_pair);

%}

%option noyywrap

%%
"PROGRAM"|"PROCEDURE"|"IS"|"IN"|"END"|"ENDIF"|"ELSE"|"THEN"|"DO"|"ENDWHILE"|"REPEAT"|"UNTIL"|"WHILE"|"READ"|"WRITE" { 
    printf("KEYWORD: %s\n", yytext); 
    return KEYWORD; 
}

"="|"!="|">"|"<"|">="|"<="|"+"|"-"|"*"|"/"|"%"|":=" { 
    printf("OPERATOR: %s\n", yytext); 
    return OPERATOR; 
}

"(" | ")" | "[" | "]" | "," | ";" { 
    printf("SYMBOL: %s\n", yytext); 
    return SYMBOL; 
}

[a-zA-Z_][a-zA-Z0-9_]* {
    printf("IDENTIFIER: %s\n", yytext); 
    return IDENTIFIER; 
}

[0-9]+ {
    printf("NUMBER: %s\n", yytext); 
    return NUMBER; 
}

[ \t\n]+ {
    // Ignorowanie białych znaków
}

. {
    printf("UNKNOWN: %s\n", yytext); 
    return UNKNOWN; 
}
%%
