#include "asm.h"

std::string asm_register_to_char(Register r)
{
    switch(r) 
    {
        case Register::A:
            return "a";
        case Register::B:
            return "b";
        case Register::C:
            return "c";
        case Register::D:
            return "d";
        case Register::E:
            return "e";
        case Register::F:
            return "f";
        case Register::G:
            return "g";
        case Register::H:
            return "h";
    }
    //TODO MAKE IT AN ERRIR
    return "UNKNOWN REGISTER";
};