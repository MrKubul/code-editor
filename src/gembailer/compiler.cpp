#include <iostream>
#include <fstream>
#include <vector>
#include "intermediate/ast_optimizer.h"
#include "backend/generator.h"

extern std::shared_ptr<Program> parsed_program;
extern int yyparse();

extern FILE *yyin;

std::string err_to_str(Error err)
{
    if(!err.is_warning) return ("ERROR: " + err.message + " at line: " + std::to_string(err.line) + '\n');
    else return ("WARNING: " + err.message + " at line: " + std::to_string(err.line) + '\n');
}

int main(int argc, char **argv) {

    if (argc < 2) 
    {
        std::cerr << "[GEMBAILER] Usage: compiler <source> [destination]" << std::endl;
        return 1;
    }

    FILE *source = fopen(argv[1], "r");

    if (!source) 
    {
        std::cerr << "[GEMBAILER] Can't open " << argv[1] << std::endl;
        return 1;
    }

    std::ofstream output;
    output.open(argv[2] ? argv[2] : "a.out");

     yyin = source;

     yyparse();

     std::cerr << "Entry Parsing has ended\n";

     AstOptimizer optimizer;

     bool error_happened = optimizer.check_correctness(*parsed_program);

     if(error_happened)
     {
        auto errs = optimizer.get_errors();
        for(auto err: errs)
        {
            if(!err.is_warning) std::cout << err_to_str(err);
        }

        output.close();
        exit(-1);
     }
     else
     {
        std::cout << "No errors detected :)\n";
        
        auto errs = optimizer.get_errors();
        for(auto err: errs)
        {
            if(err.is_warning) std::cout << err_to_str(err);
        }
     }

#if 0
    Program optimized_program = optimizer->optimize(*parsed_program);
#endif

    Generator asm_generator;
    asm_generator.generate_code(*parsed_program);

    std::vector<std::string> result = asm_generator.get_final_code();
    auto errs = asm_generator.get_generator_errors();

    if(errs.size() != 0)
    {
        for(auto err : errs)
        {
            std::cout<<err.message<<"at line: "<<err.line<<std::endl;
        }
        exit(-1);
    }
    else
    {
        for(auto const& line: result)
        {
            output << line << '\n';
        }

        std::cout<<"Succesful compilation\n";
    }

    output.close();

    return 0;
}