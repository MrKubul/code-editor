%option noyywrap
%option yylineno
%option nounput

%{
  #include <iostream>
  #include <string>
  #include "ast.h"
  #include "compiler.tab.hpp"

  //LEXER
%}

%x COMMENT

%%

[[:blank:]]+    ;

[_a-z]+     { yylval.id = new std::string(yytext); return PIDENTIFIER; } 
[0-9]+      { yylval.num = stoll(std::string(yytext)); return NUMBER; } 

"PROGRAM"       { return PROGRAM; }
"END"           { return END; }
"PROCEDURE"     { return PROCEDURE; }
"IS"            { return IS; }
"IN"            { return IN; }

"IF"            { return IF; }
"THEN"          { return THEN; }
"ELSE"          { return ELSE; }
"ENDIF"         { return ENDIF; }

"WHILE"         { return WHILE; }
"DO"            { return DO; }
"ENDWHILE"      { return ENDWHILE; }

"REPEAT"        { return REPEAT; }
"UNTIL"         { return UNTIL; }

"READ"          { return READ; }
"WRITE"         { return WRITE; }

":="            { return ASSIGNMENT; }
"T"             { return T; }

"+"             { return '+'; }
"-"             { return '-'; }
"*"             { return '*'; }
"/"             { return '/'; }
"%"             { return '%'; }

"="             { return '='; } 
"!="            { return '!'; }
"<"             { return '<'; } 
">"             { return '>'; } 
"<="            { return '{'; } //hack for passing it like char 
">="            { return '}'; } //hack for passing it like char 

"["             { return '['; }
"]"             { return ']'; }

[\;\(\)\:\,]    {return yytext[0]; } 

"#"             BEGIN(COMMENT);
<COMMENT>\n     { 
                  BEGIN(INITIAL);
                }
<COMMENT>.      ;

[ \t\n\r]+      ;
.               { return ERROR; }

%%