#pragma once

#include "../code_parser/ast.h"
#include <unordered_map>

struct Error
{
    std::string message;
    uint64_t line;
    //erros end program 
    bool is_warning;
};

struct Var 
{
    const Token *token;

    bool used = false;
    bool initialized = false;
    bool is_pointer;
    bool is_array;
};

//TODO remove
struct ProcedureCheck
{
    const Procedure *procedure;
};

//TODO wrapp in struct
using variable_environment = std::unordered_map<std::string, Var>;

class AstOptimizer
{
    public:
    AstOptimizer() = default;

    bool check_correctness(Program parsed_program);
    void check_procedure_correctness(const Procedure &procedure);
    void check_arg_declarations_correctness(const ProcedureArgumentDeclarations &decls,  variable_environment &env);
    void check_declarations_correctness(const Declarations &decls,  variable_environment &env);
    void check_commands_correctness(const Commands &cmds,   variable_environment &env);
    
    void check_unused_variable(const variable_environment &var);
    void check_variable(Value *val, variable_environment &variables);
    void check_variable(const Token &token, variable_environment &variables);

    std::vector<Error> get_errors();
    Program optimize(Program parsed_program);
    void add_error(const std::string &message, unsigned line, bool is_warning);

    private:
    std::unordered_map<std::string, ProcedureCheck> procedures{};

    //Poprawki na produkcjiXDDD
    int loop_depth = 0;
    bool error_happened = false;
    //keeps tracks of currently seen errors
    std::vector<Error> errors;
};