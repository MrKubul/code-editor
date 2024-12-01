#include "generator.h"
#include "../intermediate/ast_optimizer.h"
#include <cassert>
#include <variant>
#include <iostream>
#include <utility>

void Generator::generate_code(Program parsed_program)
{
    //it will be changed
    generate_instruction(Jump{0});

    for (auto const & procedure : parsed_program.procedure_list)
    {
        generate_procedure(procedure);
    }

    ctx.name = "main";

    for(auto const &decl : parsed_program.declaration_list.decls)
    {
        assign_declaration(decl);
    }

    //change to main function
    std::get<Jump>(code.at(0)).offset = code.size();

    for(auto const & cmd : parsed_program.commands_list.cmds)
    {
        generate_command(cmd);
    }

    generate_instruction(Halt{});
}

void Generator::generate_instruction(AsmInstruction instr)
{
    std::visit([&](auto &&arg) -> void { 
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<Read, T>) 
            {
                //std::cout<<std::get<Read>(instr).to_str()<<std::endl;
            }
            else if constexpr (std::is_same_v<Write, T>) 
            {
                //std::cout<<std::get<Write>(instr).to_str()<<std::endl;
            }
            else if constexpr (std::is_same_v<Add, T>) 
            {
                //std::cout<<std::get<Add>(instr).to_str()<<std::endl;
            }
            else if constexpr (std::is_same_v<Sub, T>) 
            {
                //std::cout<<std::get<Sub>(instr).to_str()<<std::endl;
            }
            else if constexpr (std::is_same_v<Get, T>) 
            {
                //std::cout<<std::get<Get>(instr).to_str()<<std::endl;
            }
            else if constexpr (std::is_same_v<Put, T>) 
            {
               // std::cout<<std::get<Put>(instr).to_str()<<std::endl;
            }
            else if constexpr (std::is_same_v<Rst, T>) 
            {
                //std::cout<<std::get<Rst>(instr).to_str()<<std::endl;
            }
            else if constexpr (std::is_same_v<Inc, T>) 
            {
                //std::cout<<std::get<Inc>(instr).to_str()<<std::endl;
            }
            else if constexpr (std::is_same_v<Dec, T>) 
            {
                //std::cout<<std::get<Dec>(instr).to_str()<<std::endl;
            }
            else if constexpr (std::is_same_v<Shl, T>) 
            {
               // std::cout<<std::get<Shl>(instr).to_str()<<std::endl;
            }
            else if constexpr (std::is_same_v<Shr, T>) 
            {
               // std::cout<<std::get<Shr>(instr).to_str()<<std::endl;
            }
            else if constexpr (std::is_same_v<Load, T>) 
            {
               // std::cout<<std::get<Load>(instr).to_str()<<std::endl;
            }
            else if constexpr (std::is_same_v<Store, T>) 
            {
               // std::cout<<std::get<Store>(instr).to_str()<<std::endl;
            }
            else if constexpr (std::is_same_v<Jump, T>) 
            {
               // std::cout<<std::get<Jump>(instr).to_str()<<std::endl;
            }
            else if constexpr (std::is_same_v<Jpos, T>) 
            {
               // std::cout<<std::get<Jpos>(instr).to_str()<<std::endl;
            }
            else if constexpr (std::is_same_v<Jzero, T>) 
            {
               // std::cout<<std::get<Jzero>(instr).to_str()<<std::endl;
            }
            else if constexpr (std::is_same_v<Strk, T>) 
            {
               // std::cout<<std::get<Strk>(instr).to_str()<<std::endl;
            }
            else if constexpr (std::is_same_v<Jumpr, T>) 
            {
               // std::cout<<std::get<Jumpr>(instr).to_str()<<std::endl;
            }
            else if constexpr (std::is_same_v<Halt, T>) 
            {
               // std::cout<<std::get<Halt>(instr).to_str()<<std::endl;
            }
            else 
            {
                //TODO is this needed
                assert(false);
            }
        }, instr);


    code.push_back(instr);
}

void Generator::set_register(Register reg, u64 value)
{
    //generating number with instructions
    //operation is O(log2(b)) where b is number of bits of value
    //based on ./notes/num/

    //ITS REVERSED, because of order of bits

    generate_instruction(Rst{reg});

    if(value == 0)
    {
        return;
    }

    generate_instruction(Inc{reg});

    std::vector<AsmInstruction> rev{};

    while(value != 1)
    {
        if(value % 2)
        {
            rev.insert(rev.begin(), Inc{reg});
            value -= 1;
        }
        else
        {
            rev.insert(rev.begin(), Shl{reg});
            value /= 2;
        }
    }

    //Reverse order of bits to process
    for(const AsmInstruction instr : rev)
    {
        generate_instruction(instr);
    }
}

void Generator::set_register(Register reg, std::shared_ptr<Value >value)
{
    //check what Value is??
    //VALUE = NUMBER OR ARR OR PID
    //if is identifier load it from memory and put it in register

    if(value->get_type() == NodeType::NUMBER)
    {
        //constant
        std::shared_ptr<Number> id = std::dynamic_pointer_cast<Number>(value);
        set_register(reg, id->token.numerical_value);
    }
    else if(value->get_type() == NodeType::PIDENTIFIER)
    {
        std::shared_ptr<Pidentifier> id = std::dynamic_pointer_cast<Pidentifier>(value);
        load_memory(id);
        generate_instruction(Put{reg});
    }
    else if(value->get_type() == NodeType::ARRAYIDENTIFIER)
    {
        std::shared_ptr<ArrayIdentifier> id = std::dynamic_pointer_cast<ArrayIdentifier>(value);
        load_memory(id);
        generate_instruction(Put{reg});
    }
}

//TODO ARE THOSE EVEN USED???
void Generator::set_accumulator(u64 value)
{
    set_register(Register::A, value);
}

void Generator::set_accumulator(std::shared_ptr<Value> value)
{
    set_register(Register::A, value);
}

MemoryAddress* Generator::get_var(std::string var_name)
{
    //check if ASMVariable exists in memory
    //nullptr as flag that it doesnt exists
    if(memory.contains({var_name, ctx})) { return &memory[{var_name, ctx}]; }
    return nullptr;
}

void Generator::set_address(u64 address)
{
    set_register(Register::G, address);
}

void Generator::set_address(std::shared_ptr<Value> identifier)
{
    //first check if we have pidentifier or array access
    if(identifier->get_type() == NodeType::PIDENTIFIER)
    {
        std::shared_ptr<Pidentifier> id = std::dynamic_pointer_cast<Pidentifier>(identifier);

        //check existance
        auto mem_info = get_var(*id->token.string_value);

        if(mem_info == nullptr) { //errors.push_back({"NO ASMVariable"}); 
        return; }

        if(mem_info->is_pointer) { set_address_from_ptr(identifier); return; }

        //waits in G to be load
        set_register(Register::G, mem_info->address);

    }
    else if (identifier->get_type() == NodeType::ARRAYIDENTIFIER)
    {
        std::shared_ptr<ArrayIdentifier> arr = std::dynamic_pointer_cast<ArrayIdentifier>(identifier);

        //check existance
        auto mem_info = get_var(*arr->token.string_value);

        if(mem_info == nullptr) { //errors.push_back({"NO ASMVariable"}); 
        return;  }

        if(mem_info->is_pointer) { set_address_from_ptr(identifier); return; }

        //handle both cases for ARR[NUM] or ARR[Pidentifier]
        if(std::holds_alternative<Number>(arr->index))
        {
            auto num = std::get<Number>(arr->index);
            long long int real_idx = num.token.numerical_value;

            //indexing starts at 0, IS IT REALLY OR real_idx >= mem_info->memory_cell_count, check it on example
            if(real_idx > mem_info->memory_cell_count) { errors.push_back(ASMError{"Out of bounds", real_idx, false}); 
            }
            set_register(Register::G, real_idx + mem_info->address);
        }
        else if(std::holds_alternative<Pidentifier>(arr->index)) 
        {
            // ARR[Pidentifier] case
            // we have to retrieve offset(index) from pidentifier

            auto idx_id = std::get<Pidentifier>(arr->index);

            generate_instruction(Put{Register::E}); //save current A

            auto mem_info_idx = get_var(*idx_id.token.string_value);

            if(mem_info_idx == nullptr) { errors.push_back(ASMError{"Bad index", idx_id.token.line_number, false}); 
            return; } //index doesnt exist :(
            
            set_register(Register::G, mem_info_idx->address);

            //dereference the ptr if it is a ptr
            if (mem_info_idx->is_pointer) 
            {
                generate_instruction(Load{Register::G});
                generate_instruction(Put{Register::G});
            }
            generate_instruction(Load{Register::G});

            set_register(Register::D, mem_info->address); //original address
            generate_instruction(Add{Register::D}); //real_idx + mem_info.address
            generate_instruction(Rst{Register::D}); 
            generate_instruction(Put{Register::G}); // real address to G

            //restore A register
            generate_instruction(Get{Register::E});
            generate_instruction(Rst{Register::E}); 
        }
    }
}

//Used for procedure arguments passed by *
void Generator::set_address_from_ptr(std::shared_ptr<Value> pointer)
{
    //remember ptr can still be ptr to pidentifier orr array element
    if(pointer->get_type() == NodeType::PIDENTIFIER)
    {
        std::shared_ptr<Pidentifier> id = std::dynamic_pointer_cast<Pidentifier>(pointer);

        auto mem_info = get_var(*id->token.string_value);
        if (mem_info == nullptr) {//this->errors.push_back({"NO ASMVariable"}); 
        return;}

        //pointer dereference
        set_register(Register::G, mem_info->address);
        generate_instruction(Put{Register::B}); //place there A
        generate_instruction(Load{Register::G}); //laod what pointer points to
        generate_instruction(Put{Register::G});
        generate_instruction(Get{Register::B});
        generate_instruction(Rst{Register::B}); 


    }
    else if(pointer->get_type() == NodeType::ARRAYIDENTIFIER)
    {
        std::shared_ptr<ArrayIdentifier> arr = std::dynamic_pointer_cast<ArrayIdentifier>(pointer);

        auto mem_info = get_var(*arr->token.string_value);
        if (mem_info == nullptr) {//errors.push_back({"NO ASMVariable"}); 
        return;}

        set_register(Register::G, mem_info->address);
        generate_instruction(Put{Register::B}); //place there A
        generate_instruction(Load{Register::G}); //laod what pointer points to

        //handle both cases for ARR[NUM] or ARR[Pidentifier]
        if(std::holds_alternative<Number>(arr->index))
        {
            auto num = std::get<Number>(arr->index);
            long long int real_idx = num.token.numerical_value;

            set_register(Register::D, real_idx);
            generate_instruction(Add{Register::D});
            //add index
        }
        else if(std::holds_alternative<Pidentifier>(arr->index))
        {
            auto idx_id = std::get<Pidentifier>(arr->index);

            auto mem_info_idx = get_var(*idx_id.token.string_value);

            if(mem_info == nullptr) { //errors.push_back({"NO ASMVariable"}); 
            return; } //index doesnt exist :(

            generate_instruction(Put{Register::H});
            set_register(Register::F, mem_info_idx->address);

            //dereference the pointer *
            if (mem_info_idx->is_pointer) 
            {
                generate_instruction(Load{Register::F});
                generate_instruction(Put{Register::F});
            }

            generate_instruction(Load{Register::F});
            generate_instruction(Add{Register::H});
            generate_instruction(Rst{Register::H});
        }

        generate_instruction(Put{Register::G}); //put answear to G
        generate_instruction(Get{Register::B}); //retrieve A
        generate_instruction(Rst{Register::B}); //free B register
    }
}

void Generator::set_memory(u64 address)
{
    set_address(address);

    generate_instruction(Store{Register::G});
}

void Generator::set_memory(std::shared_ptr<Value> identifier)
{
    set_address(identifier);

    generate_instruction(Store{Register::G});
}

void Generator::load_memory(u64 address)
{
    set_address(address);

    generate_instruction(Load{Register::G});
}

void Generator::load_memory(std::shared_ptr<Value> identifier)
{
    set_address(identifier);

    generate_instruction(Load{Register::G});
}

void Generator::assign_declaration(std::shared_ptr<Declaration> dec)
{
    if(dec->get_type() == NodeType::PIDENTIFIERDECLARATION)
    {
        std::shared_ptr<PidentifierDeclaration> pd = std::dynamic_pointer_cast<PidentifierDeclaration>(dec);

        memory[{*pd->name.token.string_value, ctx}] = MemoryAddress{mem_ptr, 1};

        mem_ptr += 1;
    }
    else if (dec->get_type() == NodeType::ARRAYDECLARATION)
    {
        std::shared_ptr<ArrayDeclaration> pd = std::dynamic_pointer_cast<ArrayDeclaration>(dec);

        memory[{*pd->name.token.string_value, ctx}] = MemoryAddress{.address=mem_ptr, .memory_cell_count=static_cast<u64>(pd->size)};

        mem_ptr += pd->size;
    }
}

//utility to set variant of jumps
void Generator::set_jump(AsmInstruction &instr, u64 line)
{
    //check varaint
    if(std::holds_alternative<Jump>(instr))
    {
        std::get<Jump>(instr).offset = line;
    }
    else if(std::holds_alternative<Jzero>(instr))
    {
        std::get<Jzero>(instr).offset = line;
    }
    else if(std::holds_alternative<Jpos>(instr))
    {
        std::get<Jpos>(instr).offset = line;
    }
    //TODO add jumpr?
}

void Generator::generate_procedure(Procedure p)
{
    ctx.name = *p.procedure_head.name.token.string_value;

    //at the beggining of the procedure in memory is return address
    auto return_addr = mem_ptr;
    procedures.push_back({code.size(), mem_ptr ,p});
    mem_ptr++;

    for(const auto & argument: p.procedure_head.decls.args)
    {
        memory[{*argument.name.token.string_value, ctx}] = {mem_ptr, 1, true};
        mem_ptr++;
    }

    if(p.declarations.has_value())
    {
        auto arr = p.declarations.value();
        for(const auto & decl: arr.decls)
        {
            assign_declaration(decl);
        }
    }

    //H holds return address when proc is called
    set_accumulator(2);
    generate_instruction(Add{Register::H});
    generate_instruction(Put{Register::H});
    //H+=2

    generate_instruction(Get{Register::H});
    generate_instruction(Rst{Register::H});

    //H is saved as return addr
    set_memory(return_addr);

    for(const auto & cmd: p.commands.cmds)
    {
        generate_command(cmd);
    }
    
    //return addres should be stored in H register
    load_memory(return_addr);
    //now return addres is in A we jump to it
    generate_instruction(Jumpr{Register::A});
}

void Generator::generate_write(WriteStatement wr)
{
    if (wr.value->get_type() == NodeType::NUMBER)
    {
        std::shared_ptr<Number> id = std::dynamic_pointer_cast<Number>(wr.value);
        set_accumulator(id->token.numerical_value);
    } 
    else if(wr.value->get_type() == NodeType::PIDENTIFIER)
    {
        ///Tutaj musi byc dynamic pointer cast jednak
        std::shared_ptr<Pidentifier> id = std::dynamic_pointer_cast<Pidentifier>(wr.value);
        load_memory(id);
    }
    else if(wr.value->get_type() == NodeType::ARRAYIDENTIFIER)
    {
        std::shared_ptr<ArrayIdentifier> id = std::dynamic_pointer_cast<ArrayIdentifier>(wr.value);
        load_memory(id);
    }

    generate_instruction(Write{});
    generate_instruction(Rst{Register::A});

}

void Generator::generate_read(ReadStatement r)
{
    generate_instruction(Read{});

    if(std::holds_alternative<Pidentifier>(r.identifier))
    {
        std::shared_ptr<Pidentifier> v(std::make_shared<Pidentifier>(std::get<Pidentifier>(r.identifier)));
        set_memory(v);
    }
    else if(std::holds_alternative<ArrayIdentifier>(r.identifier))
    {
        std::shared_ptr<ArrayIdentifier> v(std::make_shared<ArrayIdentifier>(std::get<ArrayIdentifier>(r.identifier)));
        set_memory(v);
    }
}

void Generator::generate_procedure_call(ProcedureCall p_c)
{
    //ERROR CHECKING CAN BE DELETED ITS DONE AT ASTOPTIMIZER NOW

    int found_idx = -1;
    for(auto const & p: procedures)
    {
        found_idx++;
        if(*p.procedure.procedure_head.name.token.string_value == *p_c.name.token.string_value) {
            break;
        }
    }

    auto proc_to_call = (procedures[found_idx]);

    //change ctx to proc
    auto outer_ctx = ctx;
    //we go into that proc ctx
    ctx.name = *p_c.name.token.string_value;

    //get mem address of start
    u64 mem_ptr = proc_to_call.mem_ptr;

    //we will be storing args there
    set_register(Register::F, mem_ptr + 1);

    //process_args
    size_t args_count = p_c.args.args.size();
    for(auto idx = 0; idx < args_count; idx++)
    {
        //exist check
        if(!memory.contains({*p_c.args.args[idx].token.string_value, outer_ctx}))
        {
            errors.push_back({"Arg doesnt exist", p_c.args.args[idx].token.line_number, false});
            //assert(false);
        }

        auto mem_info = memory[{*p_c.args.args[idx].token.string_value, outer_ctx}];

        //IT SHOULD BE COVERED at checker

        // //array isnt array
        // if (!mem_info.is_pointer && mem_info.memory_cell_count == 1 && proc_to_call.procedure.procedure_head.decls.args[idx].is_array) {
        //     assert(false);
        //     //errors.push_back("wanted array got identifier");
        // }
        // //identifier isnt identifier
        // if (mem_info.memory_cell_count > 1 && !proc_to_call.procedure.procedure_head.decls.args[idx].is_array) {
        //     assert(false);
        //     //errors.push_back("Wanted identifier got array");
        // }

        if (memory[{*p_c.args.args[idx].token.string_value, outer_ctx}].is_pointer) 
        {
            //dereference ptr
            set_register(Register::G, mem_info.address);
            generate_instruction(Load{Register::G});
        } 
        else 
        {
            set_accumulator(mem_info.address);
        }

        //store in address held in G
        generate_instruction(Store{Register::F});
        //go to next
        generate_instruction(Inc{Register::F});
    }

    generate_instruction(Rst{Register::F});
    //save return point in H
    generate_instruction(Strk{Register::H});
    //jump to procedure
    generate_instruction(Jump{proc_to_call.start_line});

    //We have to jump back to H + 2

    ctx = outer_ctx;
}

auto Generator::generate_condition(Condition cond)
{
    //empty jumps that have to be filled
    std::vector<u64> missing_false_jumps = {};
    std::vector<u64> missing_true_jumps = {};

    //E is reserved for substraction
    //check which register is empty
    auto minus_op = [&](Condition condition, Register lhs, Register rhs) 
    {   
        //swap to always have accumulator read and
        if (lhs == Register::A) 
        {
            set_register(rhs, condition.rhs);

            set_register(lhs, condition.lhs);
        } 
        else 
        {
            set_register(lhs, condition.lhs);

            set_register(rhs, condition.rhs);
        }

        generate_instruction(Sub{Register::E});
    };

    //-1 addressing is to previously genereated jump
    const size_t debug_address = 2345678;
    switch(cond.operand)
    {
        case ConditionType::EQUAL:
        {
            //x >= y
            //if(x-y)>0
            minus_op(cond, Register::A, Register::E);
            generate_instruction(Jpos{debug_address});
            missing_false_jumps.push_back(code.size()-1);
            //if(y-x)>0
            minus_op(cond, Register::E, Register::A);
            generate_instruction(Jpos{debug_address});

            missing_false_jumps.push_back(code.size()-1);

        } break;

        case ConditionType::NOT_EQUAL:
        {
        
            //x <= y
            minus_op(cond, Register::E, Register::A);
            generate_instruction(Jpos{debug_address});
            missing_true_jumps.push_back(code.size()-1);

            //rev
            minus_op(cond, Register::A, Register::E);
            generate_instruction(Jpos{debug_address});
            missing_true_jumps.push_back(code.size()-1);

            generate_instruction(Jump{debug_address});
            missing_false_jumps.push_back(code.size()-1);

        } break;

        case ConditionType::BIGGER:
        {
            //x <= y
            minus_op(cond, Register::A, Register::E);

            generate_instruction(Jpos{debug_address});
            missing_true_jumps.push_back(code.size()-1);

            minus_op(cond, Register::E, Register::A);
            generate_instruction(Jpos{debug_address});
            missing_false_jumps.push_back(code.size()-1);

            generate_instruction(Jump{debug_address});
            missing_false_jumps.push_back(code.size()-1);
        } break;

        case ConditionType::SMALLER:
        {
            //x <= y

            minus_op(cond, Register::E, Register::A);
            generate_instruction(Jpos{debug_address});
            missing_true_jumps.push_back(code.size()-1);

            minus_op(cond, Register::A, Register::E);
            generate_instruction(Jpos{debug_address});
            missing_false_jumps.push_back(code.size()-1);

            generate_instruction(Jump{debug_address});
            missing_false_jumps.push_back(code.size()-1);
        } break;

        case ConditionType::BIGGER_EQUAL:
        {
            //>=
            minus_op(cond, Register::E, Register::A);
            generate_instruction(Jpos{debug_address});
            missing_false_jumps.push_back(code.size()-1);
        } break;

        case ConditionType::SMALLER_EQUAL:
        {
            //<=
            minus_op(cond, Register::A, Register::E);
            generate_instruction(Jpos{debug_address});
            missing_false_jumps.push_back(code.size()-1);
        } break;
    }

    generate_instruction(Rst{Register::E});

    std::pair<std::vector<uint64_t>, std::vector<uint64_t>> res; 
    res.first = missing_false_jumps;
    res.second = missing_true_jumps;
    return res;
}

void Generator::generate_assignment(AssignmentStatement ass)
{
    // std::variant<Pidentifier, ArrayIdentifier> identifier;
    // std::shared_ptr<Expression> expression;
    // expression can be unary or binary

    //first make identifier shared ptr to PId or arr
    //expression can be ptr to unary or binary expression
    //every value in that can be num/pidentifier/arrayidentifier

    if (ass.expression->get_type() == NodeType::UNARYEXPRESSION)
    {
        std::shared_ptr<UnaryExpression> u = std::dynamic_pointer_cast<UnaryExpression>(ass.expression);
        set_accumulator(u->value);

        if (std::holds_alternative<Pidentifier>(ass.identifier))
        {
            Pidentifier p = std::get<Pidentifier>(ass.identifier);
            std::shared_ptr<Value> v(std::make_shared<Pidentifier>(p));
            set_memory(v);
        }
        else if (std::holds_alternative<ArrayIdentifier>(ass.identifier))
        {
            ArrayIdentifier ar = std::get<ArrayIdentifier>(ass.identifier);
            std::shared_ptr<Value> v(std::make_shared<ArrayIdentifier>(ar));
            set_memory(v);
        }
    }
    else //binary expr
    {
        std::shared_ptr<BinaryExpression> bin_exp = std::dynamic_pointer_cast<BinaryExpression>(ass.expression);

        switch(bin_exp->operand)
        {
            //All these operations are based on /notes/ implementations

            case ExpressionType::ADD:
            {
                set_register(Register::C, bin_exp->rhs);
                set_accumulator(bin_exp->lhs);
                generate_instruction(Add{Register::C});
                generate_instruction(Rst{Register::C});

            }
            break;

            case ExpressionType::SUB:
            {
                set_register(Register::E, bin_exp->rhs);
                set_accumulator(bin_exp->lhs);
                generate_instruction(Sub{Register::E});
                generate_instruction(Rst{Register::E});

            }
            break;

            case ExpressionType::MULT:
            {
                //based on notes/mult
                //Rejestry: 
                // A - używane do obliczeń na bieżąco, nie moge tu nic trzymać
                // B - p
                // C - a
                // D - b

                generate_instruction(Rst{Register::C});
                generate_instruction(Rst{Register::D});

                set_register(Register::C, bin_exp->lhs);
                set_register(Register::D, bin_exp->rhs);

                generate_instruction(Rst{Register::B});
                size_t cd = code.size();

                generate_instruction(Get{Register::D});
                generate_instruction(Jzero{code.size() + 12});
                
                //sprawdzam parzystosc na ostatnim bicie
                //>>
                //<<
                //++
                generate_instruction(Shr{Register::A});
                generate_instruction(Shl{Register::A});
                generate_instruction(Inc{Register::A});
                generate_instruction(Sub{Register::D});

                //w zaleznosci od parzystosci skacze
                generate_instruction(Jpos{code.size() + 4});

                //p+=A
                generate_instruction(Get{Register::B});
                generate_instruction(Add{Register::C});
                generate_instruction(Put{Register::B});

                //here comes jump of parity
                //shift both
                generate_instruction(Shl{Register::C});
                generate_instruction(Shr{Register::D});

                //
                generate_instruction(Jump{cd});
                generate_instruction(Get{Register::B});
                generate_instruction(Rst{Register::B});

                
            break;
            }

            case ExpressionType::DIV:
            {
                //based on notes/div
                // REJESTRY: wykorzstane ażę 5

                //TODO ZLE ROZPISANE, byla podmiana B

                // A | zajety na dzialania
                // B | p
                // C | a
                // D | b
                // E | tmp

                set_register(Register::C, bin_exp->lhs);
                set_register(Register::D, bin_exp->rhs);

                generate_instruction(Rst{Register::B});
                generate_instruction(Rst{Register::E});

                //if y == 0 jump end
                generate_instruction(Get{Register::D});
                generate_instruction(Jzero{code.size() + 21});

                //tmp=1
                generate_instruction(Inc{Register::E});

                //y <= x cond
                generate_instruction(Get{Register::D});
                generate_instruction(Sub{Register::C});
                generate_instruction(Jpos{code.size() + 4});

                //shifting
                generate_instruction(Shl{Register::E});
                generate_instruction(Shl{Register::D});
                generate_instruction(Jump{code.size() - 5});

                //if y <= x
                size_t repeat_begin = code.size();
                generate_instruction(Get{Register::D});
                generate_instruction(Sub{Register::C});
                generate_instruction(Jpos{code.size() + 7});
                // p += tmp
                generate_instruction(Get{Register::B});
                generate_instruction(Add{Register::E});
                generate_instruction(Put{Register::B});
                // x -= y
                generate_instruction(Get{Register::C});
                generate_instruction(Sub{Register::D});
                generate_instruction(Put{Register::C});

                // shifting B and tmp
                generate_instruction(Shr{Register::D});
                generate_instruction(Shr{Register::E});

                generate_instruction(Get{Register::E});
                generate_instruction(Jpos{repeat_begin});

                generate_instruction(Get{Register::B});
                generate_instruction(Rst{Register::B});

                generate_instruction(Rst{Register::C});
                generate_instruction(Rst{Register::D});

            }
            break;

            case ExpressionType::MOD:
            {
                 //based on notes/mod
                // REJESTRY: wykorzstane ażę 5

                //TODO ZLE ROZPISANE

                // A | zajety na dzialania
                // B | tmp
                // C | a
                // D | b
                // E | p

                // if b >= a return a
                set_register(Register::C, bin_exp->lhs);
                set_register(Register::D, bin_exp->rhs);

                generate_instruction(Get{Register::D});
                generate_instruction(Sub{Register::C});

                generate_instruction(Jpos{code.size() + 21});

                generate_instruction(Rst{Register::F});

                // if y = 0
                generate_instruction(Get{Register::D});
                generate_instruction(Jzero{code.size() + 21});

                // tmp= y
                generate_instruction(Get{Register::D});
                generate_instruction(Put{Register::E});

                // while y <= x
                generate_instruction(Get{Register::D});
                generate_instruction(Sub{Register::C});
                generate_instruction(Jpos{code.size() + 3});
                // y <<= 1
                generate_instruction(Shl{Register::D});
                generate_instruction(Jump{code.size() - 4});

                const auto repeat_begin = code.size();
                // y>>= 1
                generate_instruction(Shr{Register::D});

                // if y <= x
                generate_instruction(Get{Register::D});
                generate_instruction(Sub{Register::C});
                generate_instruction(Jpos{code.size() + 4});

                // x -= b
                generate_instruction(Get{Register::C});
                generate_instruction(Sub{Register::D});
                generate_instruction(Put{Register::C});

                // while tmp <= a
                generate_instruction(Get{Register::E});
                generate_instruction(Sub{Register::C});
                generate_instruction(Jzero{repeat_begin});

                generate_instruction(Get{Register::C});
                generate_instruction(Rst{Register::C});
                generate_instruction(Rst{Register::D});
            }
            break;
        }

        //we have a result in accumulator now
        if (std::holds_alternative<Pidentifier>(ass.identifier))
        {
            Pidentifier p = std::get<Pidentifier>(ass.identifier);
            std::shared_ptr<Value> v(std::make_shared<Pidentifier>(p));
            set_memory(v);
        }
        else if (std::holds_alternative<ArrayIdentifier>(ass.identifier))
        {
            ArrayIdentifier ar = std::get<ArrayIdentifier>(ass.identifier);
            std::shared_ptr<Value> v(std::make_shared<ArrayIdentifier>(ar));
            set_memory(v);
        }
    }
}

void Generator::generate_if(IfStatement if_s)
{
    auto js = generate_condition(if_s.condition);
    auto js_missing_false = js.first;
    auto js_missing_true = js.second;

    auto stmnt_begin = code.size();
    for (const auto &command : if_s.commands.cmds) {generate_command(command);}
    auto stmnt_end = code.size();

    for (auto j : js_missing_true) { set_jump(code[j], stmnt_begin);}
    for (auto j : js_missing_false) { set_jump(code[j], stmnt_end); }
}

void Generator::generate_ifelse(IfElseStatement ifelse)
{
    auto js_exit_stmnt = std::vector<uint64_t>{};
    auto js = generate_condition(ifelse.condition);
    auto js_missing_false = js.first;
    auto js_missing_true = js.second;

    auto stmnt_begin = code.size();
    for (const auto &command : ifelse.commands_true.cmds) { generate_command(command); }

    if(ifelse.commands_false.cmds.size() > 0) 
    {
        generate_instruction(Jump{0});
        js_exit_stmnt.push_back(code.size()-1);
    }
    auto stmnt_end = code.size();
    for (auto j : js_missing_true) {  set_jump(code[j], stmnt_begin);}
    for (auto j : js_missing_false) {   set_jump(code[j], stmnt_end); }

    if(ifelse.commands_false.cmds.size() > 0)
    {
        for (const auto &command : ifelse.commands_false.cmds) {  generate_command(command); }
        const auto else_end = code.size();
        for (auto j : js_exit_stmnt) {  set_jump(code[j], else_end); }
    }

}

void Generator::generate_while(WhileStatement w)
{
    const auto cond_begin = code.size();

    auto js = generate_condition(w.condition);
    auto js_missing_false = js.first;
    auto js_missing_true = js.second;
    const auto stmnt_begin = code.size();

    for (const auto &command : w.commands.cmds) {  generate_command(command);}
    generate_instruction(Jump{cond_begin});
    const auto stmnt_end = code.size();

    for (auto j : js_missing_true) {  set_jump(code[j], stmnt_begin);}
    for (auto j : js_missing_false) {  set_jump(code[j], stmnt_end);}
}

void Generator::generate_repeat(RepeatStatement r)
{
    const auto stmnt_begin = code.size();
    for (const auto &command : r.commands.cmds) {  generate_command(command); }
    auto js = generate_condition(r.condition);
    auto js_missing_false = js.first;
    auto js_missing_true = js.second;
    const auto stmnt_end = code.size();

    //i think it should be the other way
    for (auto j : js_missing_false) {  set_jump(code[j], stmnt_begin); }
    for (auto j : js_missing_true) {  set_jump(code[j], stmnt_end); }
}

void Generator::generate_command(std::shared_ptr<Command> cmd)
{
    //Debug Var
    auto xx = cmd->get_type();

    if (cmd->get_type() == NodeType::WRITE_STATEMENT)
    {
        std::shared_ptr<WriteStatement> id = std::dynamic_pointer_cast<WriteStatement>(cmd);
        generate_write(*id); 
    }
    else if (cmd->get_type() == NodeType::READ_STATEMENT)
    {
        std::shared_ptr<ReadStatement> id = std::dynamic_pointer_cast<ReadStatement>(cmd);
        generate_read(*id); 
    }
    else if (cmd->get_type() == NodeType::ASSIGNMENTSTATEMENT)
    {
        std::shared_ptr<AssignmentStatement> id = std::dynamic_pointer_cast<AssignmentStatement>(cmd);
        generate_assignment(*id); 
    }
    else if (cmd->get_type() == NodeType::IFELSESTATEMENT)
    {
        std::shared_ptr<IfElseStatement> id = std::dynamic_pointer_cast<IfElseStatement>(cmd);
        generate_ifelse(*id); 
    }
    else if (cmd->get_type() == NodeType::IFSTATEMENT)
    {
        std::shared_ptr<IfStatement> id = std::dynamic_pointer_cast<IfStatement>(cmd);
        generate_if(*id);
    }
    else if (cmd->get_type() == NodeType::WHILESTATEMENT)
    {
        std::shared_ptr<WhileStatement> id = std::dynamic_pointer_cast<WhileStatement>(cmd);
        generate_while(*id); 
    }
    else if (cmd->get_type() == NodeType::REPEATSTATEMENT)
    {
        std::shared_ptr<RepeatStatement> id = std::dynamic_pointer_cast<RepeatStatement>(cmd);
        generate_repeat(*id); 
    }
    else if (cmd->get_type() == NodeType::PROCEDURE_CALL)
    {
        std::shared_ptr<ProcedureCall> id = std::dynamic_pointer_cast<ProcedureCall>(cmd);
        generate_procedure_call(*id); 
    }
}

std::vector<std::string> Generator::get_final_code()
{
    std::vector<std::string> result_source_code;

    //DEBUG PRINTING
    for(auto & instr : code)
    {
        std::visit([&](auto &&arg) -> void { 
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<Read, T>) 
            {
                //std::cout<<std::get<Read>(instr).to_str()<<std::endl;
                result_source_code.push_back((std::get<Read>(instr).to_str())); 
            }
            else if constexpr (std::is_same_v<Write, T>) 
            {
                //std::cout<<std::get<Write>(instr).to_str()<<std::endl;
                result_source_code.push_back((std::get<Write>(instr).to_str())); 
            }
            else if constexpr (std::is_same_v<Add, T>) 
            {
                //std::cout<<std::get<Add>(instr).to_str()<<std::endl;
                result_source_code.push_back((std::get<Add>(instr).to_str())); 
            }
            else if constexpr (std::is_same_v<Sub, T>) 
            {
               // std::cout<<std::get<Sub>(instr).to_str()<<std::endl;
                result_source_code.push_back((std::get<Sub>(instr).to_str())); 
            }
            else if constexpr (std::is_same_v<Get, T>) 
            {
               // std::cout<<std::get<Get>(instr).to_str()<<std::endl;
                result_source_code.push_back((std::get<Get>(instr).to_str())); 
            }
            else if constexpr (std::is_same_v<Put, T>) 
            {
               // std::cout<<std::get<Put>(instr).to_str()<<std::endl;
                result_source_code.push_back((std::get<Put>(instr).to_str())); 
            }
            else if constexpr (std::is_same_v<Rst, T>) 
            {
               // std::cout<<std::get<Rst>(instr).to_str()<<std::endl;
                result_source_code.push_back((std::get<Rst>(instr).to_str())); 
            }
            else if constexpr (std::is_same_v<Inc, T>) 
            {
               // std::cout<<std::get<Inc>(instr).to_str()<<std::endl;
                result_source_code.push_back((std::get<Inc>(instr).to_str())); 
            }
            else if constexpr (std::is_same_v<Dec, T>) 
            {
               // std::cout<<std::get<Dec>(instr).to_str()<<std::endl;
                result_source_code.push_back((std::get<Dec>(instr).to_str())); 
            }
            else if constexpr (std::is_same_v<Shl, T>) 
            {
               // std::cout<<std::get<Shl>(instr).to_str()<<std::endl;
                result_source_code.push_back((std::get<Shl>(instr).to_str())); 
            }
            else if constexpr (std::is_same_v<Shr, T>) 
            {
               // std::cout<<std::get<Shr>(instr).to_str()<<std::endl;
                result_source_code.push_back((std::get<Shr>(instr).to_str())); 
            }
            else if constexpr (std::is_same_v<Load, T>) 
            {
               // std::cout<<std::get<Load>(instr).to_str()<<std::endl;
                result_source_code.push_back((std::get<Load>(instr).to_str())); 
            }
            else if constexpr (std::is_same_v<Store, T>) 
            {
               // std::cout<<std::get<Store>(instr).to_str()<<std::endl;
                result_source_code.push_back((std::get<Store>(instr).to_str())); 
            }
            else if constexpr (std::is_same_v<Jump, T>) 
            {
               // std::cout<<std::get<Jump>(instr).to_str()<<std::endl;
                result_source_code.push_back((std::get<Jump>(instr).to_str())); 
            }
            else if constexpr (std::is_same_v<Jpos, T>) 
            {
               // std::cout<<std::get<Jpos>(instr).to_str()<<std::endl;
                result_source_code.push_back((std::get<Jpos>(instr).to_str())); 
            }
            else if constexpr (std::is_same_v<Jzero, T>) 
            {
               // std::cout<<std::get<Jzero>(instr).to_str()<<std::endl;
                result_source_code.push_back((std::get<Jzero>(instr).to_str())); 
            }
            else if constexpr (std::is_same_v<Strk, T>) 
            {
               // std::cout<<std::get<Strk>(instr).to_str()<<std::endl;
                result_source_code.push_back((std::get<Strk>(instr).to_str())); 
            }
            else if constexpr (std::is_same_v<Jumpr, T>) 
            {
              //  std::cout<<std::get<Jumpr>(instr).to_str()<<std::endl;
                result_source_code.push_back((std::get<Jumpr>(instr).to_str())); 
            }
            else if constexpr (std::is_same_v<Halt, T>) 
            {
               // std::cout<<std::get<Halt>(instr).to_str()<<std::endl;
                result_source_code.push_back((std::get<Halt>(instr).to_str())); 
            }
            else 
            {
                assert(false);
            }
        }, instr);
    }

    return result_source_code;
}

std::vector<ASMError> Generator::get_generator_errors()
{
    return errors;
}
