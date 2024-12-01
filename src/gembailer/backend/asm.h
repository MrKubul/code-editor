#ifndef MY_HEADER_H__
#define MY_HEADER_H__

#include <string>
#include <variant>

//GEBALANG ASM instructions structs
//used to gather assembler code in abstract way

using u64 = uint64_t;

enum class Register
{
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H
};

std::string asm_register_to_char(Register r);

struct Read
{
    std::string to_str()
    {
        return "READ";
    }
};

struct Write
{
    std::string to_str()
    {
        return "WRITE";
    }
};

struct Load
{
    Register reg;

    std::string to_str()
    {
        return ("LOAD " + asm_register_to_char(reg));
    }

    Load(Register r)
    : reg(r)
    {
    
    }
};

struct Store
{
    Register reg;

    std::string to_str()
    {
        return ("STORE " + asm_register_to_char(reg));
    }

    Store(Register r)
    : reg(r)
    {
    
    }
};

struct Add
{
    Register reg;

    std::string to_str()
    {
        return ("ADD " + asm_register_to_char(reg));
    }

    Add(Register r)
    : reg(r)
    {
    
    }
};

struct Sub
{
    Register reg;

    std::string to_str()
    {
        return ("SUB " + asm_register_to_char(reg));
    }

    Sub(Register r)
    : reg(r)
    {
    
    }
};

struct Get
{
    Register reg;

    std::string to_str()
    {
        return ("GET " + asm_register_to_char(reg));
    }

    Get(Register r)
    : reg(r)
    {
    
    }
};

struct Put
{
    Register reg;

    std::string to_str()
    {
        return ("PUT " + asm_register_to_char(reg));
    }

    Put(Register r)
    : reg(r)
    {
    
    }
};

struct Rst
{
    Register reg;

    std::string to_str()
    {
        return ("RST " + asm_register_to_char(reg));
    }

    Rst(Register r)
    : reg(r)
    {
    
    }
};

struct Inc
{
    Register reg;

    std::string to_str()
    {
        return ("INC " + asm_register_to_char(reg));
    }

    Inc(Register r)
    : reg(r)
    {
    
    }
};

struct Dec
{
    Register reg;

    std::string to_str()
    {
        return ("DEC " + asm_register_to_char(reg));
    }

    Dec(Register r)
    : reg(r)
    {
    
    }
};

struct Shl
{
    Register reg;

    std::string to_str()
    {
        return ("SHL " + asm_register_to_char(reg));
    }

    Shl(Register r)
    : reg(r)
    {
    
    }
};

struct Shr
{
    Register reg;

    std::string to_str()
    {
        return ("SHR " + asm_register_to_char(reg));
    }

    Shr(Register r)
    : reg(r)
    {
    
    }
};

struct Jump
{
    size_t offset;

    std::string to_str()
    {
        return ("JUMP " + std::to_string(offset));
    }

    Jump(size_t o)
    :offset(o)
    {

    }
};

struct Jpos
{
    size_t offset;

    std::string to_str()
    {
        return ("JPOS " + std::to_string(offset));
    }

    Jpos(size_t o)
    :offset(o)
    {

    }
};

struct Jzero
{
    size_t offset;

    std::string to_str()
    {
        return ("JZERO " + std::to_string(offset));
    }

    Jzero(size_t o)
    :offset(o)
    {

    }
};

struct Strk
{
    Register reg;

    std::string to_str()
    {
        return ("STRK " + asm_register_to_char(reg));
    }

    Strk(Register r)
    : reg(r)
    {
    
    }
};

struct Jumpr
{
    Register reg;

    std::string to_str()
    {
         return ("JUMPR " + asm_register_to_char(reg));
    }

    Jumpr(Register r)
    :reg(r)
    {

    }
};

struct Halt
{
    std::string to_str()
    {
        return "HALT";
    }
};

using AsmInstruction = std::variant<Add, Read, Write, Sub, Get, Put, Rst, Inc, Dec, Shl, Shr, Load, Store,Jump, Jpos, Jzero, Strk, Jumpr, Halt>;

#endif