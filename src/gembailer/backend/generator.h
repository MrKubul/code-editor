#include "../frontend/ast.h"
#include "asm.h"

#include <unordered_map>
#include <vector>

//GEBALANG code generator for VM

using u64 = uint64_t;

struct Context
{
    //where the line of code belongs 
    //Procedure name or "main" for main function
    //No Procedure can have name "main", thats err
    std::string name{};
};

//TODO change
struct ASMVariable
{
    std::string id;
    Context local_ctx;

    //to hide unordered map comparison operator
    bool operator==(const ASMVariable &rhs) const 
    {
        return id == rhs.id && local_ctx.name == rhs.local_ctx.name;
    }
};

template<>
struct std::hash<ASMVariable>
{
    std::size_t operator()(const ASMVariable& var) const
    {
        //concatenate and calculate hash, workaround for struct hash from stackoverflow
        return std::hash<std::string>()(var.id + var.local_ctx.name);
    }
};

struct ASMProcedure
{
    //no. of line in final code where procedure code starts
    u64 start_line;
    //ptr to memory
    u64 mem_ptr;
    //procedure struct from bison
    Procedure procedure;

    //overloaded for vector usage and map usage
    bool operator==(const ASMProcedure &rhs) const 
    {
        return (start_line == rhs.start_line && mem_ptr == rhs.mem_ptr);
    }
};

struct MemoryAddress
{
    //p[address]
    u64 address;

    //arrays can be bigger than one, keep their size
    u64 memory_cell_count = 1; 
    //args are passed as pointer
    bool is_pointer = false;
};

//generator error, different than Error
//TODO ujednolicic bo to to samo
struct ASMError
{
    std::string message;

    long long line;
    bool is_warning;
};

class Generator
{
      public: 
        void generate_code(Program parsed_program);
        void generate_instruction(AsmInstruction instr);

        void set_register(Register reg, u64 value);
        void set_register(Register reg, std::shared_ptr<Value> value);

        void set_accumulator(u64 value);
        void set_accumulator(std::shared_ptr<Value> value);

        MemoryAddress* get_var(std::string var_name);

        void set_address(u64 address);
        void set_address(std::shared_ptr<Value> identifier);
        void set_address_from_ptr(std::shared_ptr<Value> pointer);

        void set_memory(u64 address);
        void set_memory(std::shared_ptr<Value> identifier);

        void load_memory(u64 address);
        void load_memory(std::shared_ptr<Value> identifier);

        void assign_declaration(std::shared_ptr<Declaration> dec);

        void set_jump(AsmInstruction &instr, u64 loc);

        void generate_procedure(Procedure p);
        void generate_command(std::shared_ptr<Command> cmd);
        auto generate_condition(Condition cond);
        void generate_read(ReadStatement r);
        void generate_write(WriteStatement wr);
        void generate_assignment(AssignmentStatement ass);
        void generate_if(IfStatement if_s);
        void generate_ifelse(IfElseStatement ifelse);
        void generate_while(WhileStatement w);
        void generate_repeat(RepeatStatement r);
        void generate_procedure_call(ProcedureCall p_c);

        std::vector<std::string> get_final_code();
        std::vector<ASMError> get_generator_errors();


        private:
            std::vector<AsmInstruction> code;
            //create struct Error and keep there also line of error
            std::vector<ASMError> errors;

            u64 mem_ptr = 0;
            Context ctx{};

            //keep track of registers occupancy
            //std::array<Register, 8> registers;
            std::unordered_map<ASMVariable, MemoryAddress> memory;
            std::vector<ASMProcedure> procedures;
};