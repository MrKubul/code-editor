#include "static_analyzer.hpp"

extern int yyerror(std::string);

//find errors based on AST
bool AstOptimizer::check_correctness(Program parsed_program)
{
    for (const auto &procedure : parsed_program.procedure_list) 
    {
        check_procedure_correctness(procedure);

        procedures[*(procedure.procedure_head.name.token.string_value)] = ProcedureCheck{&procedure};
    }

    //MAIN function checking
    auto env = variable_environment{};
    check_declarations_correctness(parsed_program.declaration_list, env);
    check_commands_correctness(parsed_program.commands_list, env);

    return error_happened;
}

void AstOptimizer::check_procedure_correctness(const Procedure &procedure) 
{
    auto variable_declarations = variable_environment{};
    //args
    check_arg_declarations_correctness(procedure.procedure_head.decls, variable_declarations);
    //decls if they are
    if(procedure.declarations.has_value())
    {
        check_declarations_correctness(procedure.declarations.value(), variable_declarations);
    } 

    //commands
    check_commands_correctness(procedure.commands, variable_declarations);
}

 void AstOptimizer::check_arg_declarations_correctness(const ProcedureArgumentDeclarations &decls, variable_environment &env)
 {
     for (const auto &dec : decls.args) {

        if (env.contains(*dec.name.token.string_value)) 
        {
            add_error(("duplicate variable-declaration of" + *dec.name.token.string_value), dec.name.token.line_number, false );
        }

        env[*dec.name.token.string_value] = Var{.token = &dec.name.token, .is_pointer = true, .is_array = dec.is_array};
        env[*dec.name.token.string_value].initialized = true;
    }
 }

 void AstOptimizer::check_declarations_correctness(const Declarations &decls, variable_environment &env)
 {
     for (const auto &dec : decls.decls) {

        //DEBUG var
        auto a = dec->get_type();

        if(dec->get_type() == NodeType::PIDENTIFIERDECLARATION)
        {
            std::shared_ptr<PidentifierDeclaration> pd = std::dynamic_pointer_cast<PidentifierDeclaration>(dec);

            if (env.contains(*(pd->name.token.string_value))) 
            {
                add_error(("duplicate variable-declaration of:" + *pd->name.token.string_value), pd->name.token.line_number, false );
            }

            env[*(pd->name.token.string_value)] = Var{.token = &pd->name.token, .is_pointer = false, .is_array = false};
            env[*(pd->name.token.string_value)].initialized = false;

        }
        else if (dec->get_type() == NodeType::ARRAYDECLARATION)
        {
            std::shared_ptr<ArrayDeclaration> pd = std::dynamic_pointer_cast<ArrayDeclaration>(dec);

            if (env.contains(*(pd->name.token.string_value))) 
            {
                add_error(("Duplicate variable declaration" + *pd->name.token.string_value), pd->name.token.line_number, false );
            }

            env[*(pd->name.token.string_value)] = Var{.token = &pd->name.token, .is_pointer = false, .is_array = true};
            env[*(pd->name.token.string_value)].initialized = false;
        }
    }
 }

 void AstOptimizer::check_commands_correctness(const Commands &cmds, variable_environment &env)
 {
    for (const auto &command : cmds.cmds) 
    {
         if(command->get_type() == NodeType::ASSIGNMENTSTATEMENT)
         {  
            //received types
            //std::variant<Pidentifier, ArrayIdentifier> identifier;
            //std::shared_ptr<Expression> expression; -> Unary lub binary
            
            std::shared_ptr<AssignmentStatement> pd = std::dynamic_pointer_cast<AssignmentStatement>(command);

            if (std::holds_alternative<Pidentifier>(pd->identifier)) {
                Pidentifier p = std::get<Pidentifier>(pd->identifier);

                if (env.contains(*p.token.string_value)) 
                {
                    env[*p.token.string_value].initialized = true;
                }

                check_variable(&p, env);

            }
            else if (std::holds_alternative<ArrayIdentifier>(pd->identifier)) {
                ArrayIdentifier ar = std::get<ArrayIdentifier>(pd->identifier);

                if (env.contains(*ar.token.string_value)) 
                {
                    env[*ar.token.string_value].initialized = true;
                }

                check_variable(&ar, env);

            }

            if((pd->expression)->get_type() == NodeType::UNARYEXPRESSION)
            {
                std::shared_ptr<UnaryExpression> u = std::dynamic_pointer_cast<UnaryExpression>(pd->expression);

                //iF Value* points to some identifier
                check_variable((u->value).get(), env);
            }
            else if((pd->expression)->get_type() == NodeType::BINARYEXPRESSION)
            {
                std::shared_ptr<BinaryExpression> b = std::dynamic_pointer_cast<BinaryExpression>(pd->expression);

                check_variable((b->lhs).get(), env);
                check_variable((b->rhs).get(), env);
            }

         }
         else if(command->get_type() == NodeType::PROCEDURE_CALL)
         {
            std::shared_ptr<ProcedureCall> pc = std::dynamic_pointer_cast<ProcedureCall>(command);

            if (!procedures.contains(*pc->name.token.string_value)) 
            {
                add_error(("Calling not known procedure: " + *pc->name.token.string_value), pc->name.token.line_number, false);
                return;
            }

            unsigned arg_idx = 0;
            //check all passed args
            for (Pidentifier &p : pc->args.args) 
            {
                if(env.contains(*p.token.string_value)) env[*p.token.string_value].initialized = true;
                
                check_variable(p.token, env);

                if(env.contains(*p.token.string_value))
                {
                    if (env[*p.token.string_value].is_array != procedures[*pc->name.token.string_value].procedure->procedure_head.decls.args[arg_idx].is_array) 
                    {
                        add_error(("Procedure argument type doesnt match (array/not array) " + *p.token.string_value), p.token.line_number, false);
                    }
                }
                arg_idx++;
            }

            //check if arguments count macthes, thats not neceessary
            if (pc->args.args.size() != procedures[*pc->name.token.string_value].procedure->procedure_head.decls.args.size()) 
            {
                add_error(("Not enough args passed to proc " + *pc->name.token.string_value), pc->name.token.line_number, false);
            }
         }
         else if(command->get_type() == NodeType::WHILESTATEMENT)
         {
            std::shared_ptr<WhileStatement> pd = std::dynamic_pointer_cast<WhileStatement>(command);
            loop_depth++;
            check_commands_correctness(pd->commands, env);
            loop_depth--;
         }
         else if(command->get_type() == NodeType::REPEATSTATEMENT)
         {
            std::shared_ptr<RepeatStatement> pd = std::dynamic_pointer_cast<RepeatStatement>(command);
            loop_depth++;
            check_commands_correctness(pd->commands, env);
            loop_depth--;
         }
         else if(command->get_type() == NodeType::READ_STATEMENT)
         {
            std::shared_ptr<ReadStatement> read = std::dynamic_pointer_cast<ReadStatement>(command);

            //read->identifier is std::variant<Pidentifier, ArrayIdentifier> !

            if (std::holds_alternative<Pidentifier>(read->identifier))
            {
                Pidentifier p = std::get<Pidentifier>(read->identifier);

                if (!env.contains(*p.token.string_value)) 
                {
                    add_error(("Reading undeclared var: " + *p.token.string_value), p.token.line_number, false);
                    return;
                }

                    //Var will be initialized by the user
                env[*p.token.string_value].initialized = true;

                //we want to pass it as Value*, we can because both derive from Value!
                check_variable(&p, env);
            }
            else if(std::holds_alternative<ArrayIdentifier>(read->identifier))
            {
                ArrayIdentifier ar = std::get<ArrayIdentifier>(read->identifier);

                if (!env.contains(*ar.token.string_value)) 
                {
                    add_error(("Reading undeclared var(arr): " + *ar.token.string_value), ar.token.line_number, false);
                    return;
                }

                    //Var will be initialized by the user
                env[*ar.token.string_value].initialized = true;

                //we want to pass it as Value*, we can because both derive from Value!
                check_variable(&ar, env);
            }
         }
         else if(command->get_type() == NodeType::WRITE_STATEMENT)
         {
            std::shared_ptr<WriteStatement> pd = std::dynamic_pointer_cast<WriteStatement>(command);

            //iF Value* points to some identifier
            check_variable((pd->value).get(), env);
         }
         else if(command->get_type() == NodeType::IFSTATEMENT)
         {
            std::shared_ptr<IfStatement> pd = std::dynamic_pointer_cast<IfStatement>(command);

            check_commands_correctness(pd->commands, env);
         }
         else if(command->get_type() == NodeType::IFELSESTATEMENT)
         {
            std::shared_ptr<IfElseStatement> pd = std::dynamic_pointer_cast<IfElseStatement>(command);

            check_commands_correctness(pd->commands_true, env);
            check_commands_correctness(pd->commands_false, env);
         }

    }
 }

 void AstOptimizer::check_unused_variable(const variable_environment &var)
 {
    for (const auto &[name, variable] : var) 
    {
        if (!variable.used) 
        {

            add_error(("unused variable of name: " + name), variable.token->line_number, true);
        }
    }
 }

  void AstOptimizer::check_variable(Value *val, variable_environment &env)
 {
    if(val->get_type() == NodeType::PIDENTIFIER)
    {
        Pidentifier p = *(dynamic_cast<Pidentifier*>(val));
        check_variable(p.token, env);

        if(env.contains(*p.token.string_value))
        {
            if (env[*p.token.string_value].is_array) 
            {
                add_error(("It should be array, but its used as var!!: " + *p.token.string_value), p.token.line_number, false);
            }
        }
    }
    else if(val->get_type() == NodeType::ARRAYIDENTIFIER)
    {
        ArrayIdentifier arr = *(dynamic_cast<ArrayIdentifier*>(val));
        check_variable(arr.token, env);

        if(env.contains(*arr.token.string_value))
        {
            if (!env[*arr.token.string_value].is_array) 
            {
                add_error(("It should be var, but its used as array!!: " + *arr.token.string_value), arr.token.line_number, false);
            }
        }

        //Debug var
        auto aaa = *arr.token.string_value;

        //if Index is Pidentifier, check its token!!!
        if (std::holds_alternative<Pidentifier>(arr.index))
        {
            Pidentifier p = std::get<Pidentifier>(arr.index);

            //Debug VAR
            auto aaa = *p.token.string_value;

            check_variable(p.token, env);
        }
    }
 }

 void AstOptimizer::check_variable(const Token &token, variable_environment &env)
 {
    if (!env.contains(*token.string_value)) 
    {
        std::string message = ("undeclared var " +  (*token.string_value));
        add_error(message, token.line_number, false);

        //Debug Vars
        auto x = error_happened;
        auto xd =  errors.size();
    }

    env[*token.string_value].used = true;

    if (!env[*token.string_value].initialized && loop_depth==0) 
    {
        std::string message = ("var used before set " +  (*token.string_value));
        add_error(message, token.line_number, false);
    }
    else if (!env[*token.string_value].initialized) 
    {
        std::string message = ("un-initialzied variable " +  (*token.string_value));
        add_error(message, token.line_number, true);
    }
 }

bool AstOptimizer::check_correctness(std::vector<BasicBlock> control_flow_graph)
{
    reurn true;
}


 std::vector<Error> AstOptimizer::get_errors()
 {
    //return 
    return errors;
 }

void AstOptimizer::add_error(const std::string &m, unsigned l, bool is_w)
{
    if (is_w == false) error_happened = true;
    Error error({.message = m, .line = l, .is_warning = is_w});
    errors.push_back(error);
}
