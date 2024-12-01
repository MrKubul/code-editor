#pragma once

#include <vector>
#include <string>
#include <variant>
#include <optional>
#include <memory>

//MY AST CODE
//It matches bison grammar

struct Token
{
    int line_number;
    long long numerical_value;
    std::string* string_value;
};

//TYPE OF NODE
enum class NodeType
{
    NUMBER,
    PIDENTIFIER,
    ARRAYIDENTIFIER,
    VALUE,
    CONDITION,
    EXPRESSION,
    UNARYEXPRESSION,
    BINARYEXPRESSION,
    CALLARGUMENTS,
    PROCEDUREARGUMENTDECLARATIONS,
    ARGUMENTDECLARATION,
    DECLARATION,
    PIDENTIFIERDECLARATION,
    ARRAYDECLARATION,
    DECLARATIONS,
    COMMAND,
    COMMANDS,
    ASSIGNMENTSTATEMENT,
    IFELSESTATEMENT,
    IFSTATEMENT,
    WHILESTATEMENT,
    REPEATSTATEMENT,
    PROCEDURE_CALL,
    READ_STATEMENT,
    WRITE_STATEMENT,
    PROCEDURE_HEAD,
    PROCEDURE,
    PROGRAM
};

struct AstNode
{
    AstNode() = default;
    ~AstNode() = default;
    AstNode(const AstNode &node) = default;
    AstNode& operator=(const AstNode &node) = default;
    AstNode(AstNode&&) = default;
    AstNode& operator=(AstNode&&) = default;

    virtual NodeType get_type() const = 0;
};

struct Value : AstNode
{
    Value()
    {

    }

    virtual NodeType get_type() const
    {
        return NodeType::VALUE;
    }
};

struct Number : Value
{
    Token token;

    Number()
    {

    }

    Number(Token t)
    {
        token = t;
    }

    NodeType get_type() const
    {
        return NodeType::NUMBER;
    }
};

struct Pidentifier : Value
{
    Token token;

    Pidentifier()
    {

    }

    Pidentifier(Token t)
    {
        token = t;
    }

    NodeType get_type() const
    {
        return NodeType::PIDENTIFIER;
    }
};

//wariacik
using ArrayAccess = std::variant<Number, Pidentifier>;

struct ArrayIdentifier : Value
{
    Token token;
    ArrayAccess index;

    ArrayIdentifier(Token t, ArrayAccess i)
    {
        token = t;
        index = i;
    }

    NodeType get_type() const
    {
        return NodeType::ARRAYIDENTIFIER;
    }
};

enum class ConditionType
{
    SMALLER,
    BIGGER,
    EQUAL,
    NOT_EQUAL,
    BIGGER_EQUAL,
    SMALLER_EQUAL
};

struct Condition : AstNode
{
    std::shared_ptr<Value> lhs;
    std::shared_ptr<Value> rhs;
    ConditionType operand;

    Condition()
    {

    }

    Condition(Value* l, Value *r, ConditionType op)
    : lhs(l)
    ,rhs(r)
    {
        operand = op;
    }

    NodeType get_type() const
    {
        return NodeType::CONDITION;
    }
};

struct Expression : AstNode
{
    Expression()
    {

    }

    NodeType get_type() const
    {
        return NodeType::EXPRESSION;
    }
};

struct UnaryExpression : Expression
{
    std::shared_ptr<Value> value;

    UnaryExpression(Value *v)
    : value(v)
    {
    }

    NodeType get_type() const
    {
        return NodeType::UNARYEXPRESSION;
    }
};

enum class ExpressionType
{
    ADD,
    SUB,
    MULT,
    DIV,
    MOD
};

struct BinaryExpression : Expression
{
    std::shared_ptr<Value> lhs;
    std::shared_ptr<Value> rhs;
    ExpressionType operand;

    BinaryExpression(Value *l, Value *r, ExpressionType op)
    :lhs(l)
    ,rhs(r)
    {
        operand = op;
    }

    NodeType get_type() const
    {
        return NodeType::BINARYEXPRESSION;
    }
};

struct CallArguments : AstNode
{
    std::vector<Pidentifier> args{};

    CallArguments()
    {

    }

    NodeType get_type() const
    {
        return NodeType::CALLARGUMENTS;
    }
};

struct ArgDeclaration : AstNode
{
    Pidentifier name;
    bool is_array;

    ArgDeclaration(Pidentifier &p, bool a)
    {
        name = p;
        is_array = a;
    }

    NodeType get_type() const
    {
        return NodeType::ARGUMENTDECLARATION;
    }
};

struct ProcedureArgumentDeclarations : AstNode
{
    std::vector<ArgDeclaration> args{};

    ProcedureArgumentDeclarations()
    {

    }

    NodeType get_type() const
    {
        return NodeType::PROCEDUREARGUMENTDECLARATIONS;
    }
};

struct Declaration : AstNode
{

    Declaration()
    {

    }

    virtual NodeType get_type() const
    {
        return NodeType::DECLARATION;
    }
};

struct PidentifierDeclaration : Declaration
{
    Pidentifier name;

    PidentifierDeclaration(Pidentifier &p)
    {
        name = p;
    }

    NodeType get_type() const
    {
        return NodeType::PIDENTIFIERDECLARATION;
    }
};


struct ArrayDeclaration : Declaration
{
    Pidentifier name;
    long long size;

    ArrayDeclaration(Pidentifier &p, long long s)
    {
        name = p;
        size = s;
    }

    NodeType get_type() const
    {
        return NodeType::ARRAYDECLARATION;
    }
};

struct Declarations : AstNode
{
    std::vector<std::shared_ptr<Declaration>> decls{};

    Declarations()
    {

    }

    NodeType get_type() const
    {
        return NodeType::DECLARATIONS;
    }
};

struct Command : AstNode
{
    Command()
    {

    }

    virtual NodeType get_type() const
    {
        return NodeType::COMMAND;
    }
};

struct Commands : AstNode
{
    std::vector<std::shared_ptr<Command>> cmds{};

    Commands()
    {

    }

    NodeType get_type() const
    {
        return NodeType::COMMANDS;
    }
};

struct AssignmentStatement : Command
{
    //wariacik
    std::variant<Pidentifier, ArrayIdentifier> identifier;
    std::shared_ptr<Expression> expression;

    AssignmentStatement(Value *p, Expression *expr)
    :expression(expr)
    {
        if(p->get_type() == NodeType::PIDENTIFIER)
        {
            identifier = *(dynamic_cast<Pidentifier*>(p));
        }
        else if(p->get_type() == NodeType::ARRAYIDENTIFIER)
        {
            identifier = *(dynamic_cast<ArrayIdentifier*>(p));
        }
    }

    NodeType get_type() const
    {
        return NodeType::ASSIGNMENTSTATEMENT;
    }
};

struct IfElseStatement : Command
{
    Condition condition;
    Commands commands_true;
    Commands commands_false;

    IfElseStatement(Condition &cond, Commands &cmds_true, Commands &cmds_false)
    {
        condition = cond;
        commands_true = cmds_true;
        commands_false = cmds_false;
    }

    NodeType get_type() const
    {
        return NodeType::IFELSESTATEMENT;
    }
};

struct IfStatement : Command
{
    Condition condition;
    Commands commands;

    IfStatement(Condition &cond, Commands &cmds)
    {
        condition = cond;
        commands = cmds;
    }

    NodeType get_type() const
    {
        return NodeType::IFSTATEMENT;
    }
};

struct WhileStatement : Command
{
    Condition condition;
    Commands commands;

    WhileStatement(Condition &cond, Commands &cmds)
    {
        condition = cond;
        commands = cmds;
    }

    NodeType get_type() const
    {
        return NodeType::WHILESTATEMENT;
    }
};

struct RepeatStatement : Command
{
    Condition condition;
    Commands commands;

    RepeatStatement(Condition &cond, Commands &cmds)
    {
        condition = cond;
        commands = cmds;
    }

    NodeType get_type() const
    {
        return NodeType::REPEATSTATEMENT;
    }
};

struct ProcedureCall : Command
{
    Pidentifier name;
    CallArguments args;

    ProcedureCall(Pidentifier &p, CallArguments &a)
    {
        name = p;
        args = a;
    }

    NodeType get_type() const
    {
        return NodeType::PROCEDURE_CALL;
    }
};

struct ReadStatement : Command
{
    std::variant<Pidentifier, ArrayIdentifier> identifier;

    ReadStatement(Value *p)
    {
        if(p->get_type() == NodeType::PIDENTIFIER)
        {
            identifier = *(dynamic_cast<Pidentifier*>(p));
        }
        else if(p->get_type() == NodeType::ARRAYIDENTIFIER)
        {
            identifier = *(dynamic_cast<ArrayIdentifier*>(p));
        }
    }

    NodeType get_type() const
    {
        return NodeType::READ_STATEMENT;
    }
};

struct WriteStatement : Command
{
    std::shared_ptr<Value> value;

    WriteStatement(Value *v)
    : value(v)
    {

    }

    NodeType get_type() const
    {
        return NodeType::WRITE_STATEMENT;
    }
};

struct ProcedureHead : AstNode
{
    Pidentifier name;
    ProcedureArgumentDeclarations decls;

    ProcedureHead(Pidentifier &p, ProcedureArgumentDeclarations &d)
    : name(p)
    , decls(d)
    {

    }

    NodeType get_type() const
    {
        return NodeType::PROCEDURE_HEAD;
    }
};

struct Procedure : AstNode
{
    ProcedureHead procedure_head;
    std::optional<Declarations> declarations;
    Commands commands;

    Procedure(ProcedureHead &p, std::optional<Declarations> d, Commands &c)
    : procedure_head(p)
    , declarations(d)
    , commands(c)
    {

    }

    NodeType get_type() const
    {
        return NodeType::PROCEDURE;
    }
};

struct Program : AstNode
{
    std::vector<Procedure> procedure_list;
    Declarations declaration_list;
    Commands commands_list;

    NodeType get_type() const
    {
        return NodeType::PROGRAM;
    }
};