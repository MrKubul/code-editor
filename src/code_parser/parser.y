%{
    #include <iostream>
    #include <vector>
    #include <memory>

    #include "ast.h"

    extern int yylex();
    extern int yyset_in(FILE* in);
    extern FILE *yyin;
    extern int yylineno;
    extern char* yytext;

    int yyerror(std::string);

    //AST OF PRORGAM HANDLE
    std::shared_ptr<Program> parsed_program = std::make_shared<Program>();

    //BISON
%}

%union {
    Value *value;
    Condition *condition;
    Expression *expression;
    Command* cmd;
    ProcedureHead *head;

    CallArguments *call_args;
    ProcedureArgumentDeclarations *proc_args;

    Declarations *decls;
    Commands *cmds;

    long long num;
    std::string* id;
}

%start program_all

%token PROGRAM
%token END
%token PROCEDURE
%token IS
%token IN

%token IF
%token THEN
%token ELSE
%token ENDIF

%token WHILE
%token DO
%token ENDWHILE

%token REPEAT
%token UNTIL

%token READ
%token WRITE

%token ASSIGNMENT
%token T

%token <num> NUMBER
%token <id> PIDENTIFIER

%left '+' '-' '*' '/' '%'

%token ERROR

%type<value> value
%type<value> identifier
%type<condition> condition;
%type<expression> expression;
%type<call_args> args;
%type<proc_args> args_decl;
%type<decls> declarations;
%type<cmds> commands;
%type<cmd> command;
%type<cmd> proc_call;
%type<head> proc_head;

%%

program_all:     procedures main                                                            { 
                                                                                                ;
                                                                                            }

procedures:      procedures PROCEDURE proc_head IS declarations IN commands END         { 
                                                                                            std::optional<Declarations> d(*$5);
                                                                                            Procedure p(*$3, d, *$7);
                                                                                            parsed_program->procedure_list.push_back(p);
                                                                                        }

                | procedures PROCEDURE proc_head IS IN commands END                     { 
                                                                                            std::optional<Declarations> d = std::nullopt;
                                                                                            Procedure p(*$3, d, *$6);
                                                                                            parsed_program->procedure_list.push_back(p);   
                                                                                        }
                
                |                                                                       {   
                                                                                            ;   
                                                                                        } 

main:           PROGRAM IS declarations IN commands END                                 { 
                                                                                            parsed_program->declaration_list = *$3; parsed_program->commands_list = *$5;   
                                                                                        }

                | PROGRAM IS IN commands END                                            { 
                                                                                            parsed_program->commands_list = *$4; 
                                                                                        }

 proc_head:      PIDENTIFIER '(' args_decl ')'                                           {   
                                                                                            Token token_id({ .line_number = yylineno, .string_value = $1}); 
                                                                                            Pidentifier p(token_id);

                                                                                            $$ = new ProcedureHead(p, *$3);   
                                                                                         }

commands:       commands command                                                        {   
                                                                                            std::shared_ptr<Command> ptr($2);
                                                                                            ($1)->cmds.push_back(ptr);     
                                                                                         }

                | command                                                               { 
                                                                                            $$ = new Commands(); 
                                                                                            std::shared_ptr<Command> ptr($1);
                                                                                            $$->cmds.push_back(ptr);  
                                                                                         }

command:         identifier ASSIGNMENT expression ';'                                    { 
                                                                                             $$ = new AssignmentStatement($1, $3);   
                                                                                         }

                 | IF condition THEN commands ELSE commands ENDIF                        { 
                                                                                             $$ = new IfElseStatement(*$2, *$4, *$6);   
                                                                                         }

                 | IF condition THEN commands ENDIF                                      { 
                                                                                             $$ = new IfStatement(*$2, *$4);   
                                                                                         }

                 | WHILE condition DO commands ENDWHILE                                  { 
                                                                                             $$ = new WhileStatement(*$2, *$4);   
                                                                                         }

                 | REPEAT commands UNTIL condition ';'                                 { 
                                                                                             $$ = new RepeatStatement(*$4, *$2);   
                                                                                         }

                 | proc_call ';'                                                        { 
                                                                                             $$ = $1;   
                                                                                         }

                 | READ identifier ';'                                                   { 
                                                                                             $$ = new ReadStatement($2);   
                                                                                        }

                 | WRITE value ';'                                                       { 
                                                                                             $$ = new WriteStatement($2);   
                                                                                         }

 proc_call:      PIDENTIFIER '(' args ')'                                                { 
                                                                                            Token token_id({ .line_number = yylineno, .string_value = $1}); 
                                                                                            Pidentifier p(token_id);

                                                                                            $$ = new ProcedureCall(p, *$3);
                                                                                         }

 declarations:   declarations ',' PIDENTIFIER                                            { 
                                                                                            Token token_id({ .line_number = yylineno, .string_value = $3}); 
                                                                                            Pidentifier p(token_id);
                                                                                            PidentifierDeclaration pd(p);

                                                                                            ($1)->decls.push_back(std::make_shared<PidentifierDeclaration>(pd));
                                                                                         }

                 | declarations ',' PIDENTIFIER '[' NUMBER ']'                           { 
                                                                                            Token token_id({ .line_number = yylineno, .string_value = $3}); 
                                                                                            Pidentifier p(token_id);
                                                                                            ArrayDeclaration ad(p, $5);

                                                                                            ($1)->decls.push_back(std::make_shared<ArrayDeclaration>(ad));
                                                                                         }

                 | PIDENTIFIER                                                           { 
                                                                                            Token token_id({ .line_number = yylineno, .string_value = $1}); 
                                                                                            Pidentifier p(token_id);
                                                                                            PidentifierDeclaration pd(p);

                                                                                            $$ = new Declarations();
                                                                                            $$->decls.push_back(std::make_shared<PidentifierDeclaration>(pd));   
                                                                                         }

                 | PIDENTIFIER '[' NUMBER ']'                                            { 

                                                                                            Token token_id({ .line_number = yylineno, .string_value = $1}); 
                                                                                            Pidentifier p(token_id);
                                                                                            ArrayDeclaration ad(p, $3);

                                                                                            $$ = new Declarations();
                                                                                            $$->decls.push_back(std::make_shared<ArrayDeclaration>(ad));  
                                                                                         }

 args_decl:      args_decl ',' PIDENTIFIER                                               { 
                                                                                            Token token_id({ .line_number = yylineno, .string_value = $3}); 
                                                                                            Pidentifier p(token_id);
                                                                                            ArgDeclaration arg_dec(p, false);

                                                                                            ($1)->args.push_back(arg_dec); 
                                                                                         }

                 | args_decl ',' T PIDENTIFIER                                           {   
                                                                                            Token token_id({ .line_number = yylineno, .string_value = $4}); 
                                                                                            Pidentifier p(token_id);
                                                                                            ArgDeclaration arg_dec(p, true);  

                                                                                            ($1)->args.push_back(arg_dec);   
                                                                                         }

                 | PIDENTIFIER                                                               
                                                                                         { 
                                                                                            Token token_id({ .line_number = yylineno, .string_value = $1}); 
                                                                                            Pidentifier p(token_id);
                                                                                            ArgDeclaration arg_dec(p, false);

                                                                                             $$ = new ProcedureArgumentDeclarations(); 
                                                                                             $$->args.push_back(arg_dec);   
                                                                                         }

                 | T PIDENTIFIER                                                             
                                                                                         { 
                                                                                            Token token_id({ .line_number = yylineno, .string_value = $2}); 
                                                                                            Pidentifier p(token_id);
                                                                                            ArgDeclaration arg_dec(p, true);
                                                                                             
                                                                                            $$ = new ProcedureArgumentDeclarations();
                                                                                            $$->args.push_back(arg_dec);
                                                                                         }

 args:           args ',' PIDENTIFIER                                                    {
                                                                                            Token token_id({ .line_number = yylineno, .string_value = $3}); 
                                                                                            Pidentifier p(token_id); 
                                                                                             
                                                                                            ($1)->args.push_back(p); 
                                                                                         }

                 | PIDENTIFIER                                                           { 
                                                                                            Token token_id({ .line_number = yylineno, .string_value = $1}); 
                                                                                            Pidentifier p(token_id); 

                                                                                            $$ = new CallArguments(); 
                                                                                            $$->args.push_back(p);   
                                                                                         }

 expression:     value                                                                   {  
                                                                                             $$ = new UnaryExpression($1);   
                                                                                         }

                 | value '+' value                                                       { 
                                                                                             $$ = new BinaryExpression($1, $3, ExpressionType::ADD);   
                                                                                         }

                 | value '-' value                                                       { 
                                                                                             $$ = new BinaryExpression($1, $3, ExpressionType::SUB);   
                                                                                         }

                 | value '*' value                                                       { 
                                                                                             $$ = new BinaryExpression($1, $3, ExpressionType::MULT);   
                                                                                         }

                 | value '/' value                                                       { 
                                                                                             $$ = new BinaryExpression($1, $3, ExpressionType::DIV);   
                                                                                         }

                 | value '%' value                                                       { 
                                                                                             $$ = new BinaryExpression($1, $3, ExpressionType::MOD);   
                                                                                         }

 condition:      value '=' value                                                         { 
                                                                                             $$ = new Condition($1, $3, ConditionType::EQUAL);   
                                                                                         }

                 | value '!' value                                                      { 
                                                                                             $$ = new Condition($1, $3, ConditionType::NOT_EQUAL);   
                                                                                         }

                 | value '>' value                                                       { 
                                                                                             $$ = new Condition($1, $3, ConditionType::BIGGER);                                                                                            }

                 | value '<' value                                                       { 
                                                                                             $$ = new Condition($1, $3, ConditionType::SMALLER);   
                                                                                         }

                | value '}' value                                                      { 
                                                                                             $$ = new Condition($1, $3, ConditionType::BIGGER_EQUAL);   
                                                                                         }

                 | value '{' value                                                      { 
                                                                                            $$ = new Condition($1, $3, ConditionType::SMALLER_EQUAL);   
                                                                                        }

value:          NUMBER                                                                  { 
                                                                                            Token token_num({ .line_number = yylineno, .numerical_value = $1});
                                                                                            $$ = new Number(token_num);
                                                                                        }

                | identifier                                                            { 
                                                                                            //pass Value* further up
                                                                                            $$ = $1;
                                                                                        }                                 

identifier:     PIDENTIFIER                                                             {
                                                                                            Token token_id({ .line_number = yylineno, .string_value = $1}); 
                                                                                            $$ = new Pidentifier(token_id); 
                                                                                        }

                | PIDENTIFIER '[' NUMBER ']'                                            { 
                                                                                            Token token_id({ .line_number = yylineno, .string_value = $1});
                                                                                            Token token_num({ .line_number = yylineno, .numerical_value = $3});
                                                                                            Number n(token_num);

                                                                                            $$ = new ArrayIdentifier(token_id, n);
                                                                                        }

                | PIDENTIFIER '[' PIDENTIFIER ']'                                       { 
                                                                                            Token token_id({ .line_number = yylineno, .string_value = $1});
                                                                                            Token token_idx({ .line_number = yylineno, .string_value = $3});
                                                                                            Pidentifier p(token_idx);

                                                                                            $$ = new ArrayIdentifier(token_id, p);
                                                                                        }

%%

int yyerror(std::string error_msg) 
{
    std::cout << "[GEBALANG ERROR]: Line " << yylineno << "\n";
    std::cout << "[GEBALANG MESSAGE]: " << error_msg << "\n";
    exit(1);
}