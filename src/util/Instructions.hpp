//
// Created by Maximilian Vater on 15.01.24.
//

#ifndef STACK_VM_INSTRUCTIONS_HPP
#define STACK_VM_INSTRUCTIONS_HPP

#include <optional>


using std::optional;

namespace Instructions{
    enum Opcode{
        STOP = 0,
        PUSH = 1,
        ADD = 2,
        SUB = 3,
        MUL = 4,
        DIV = 5,
        MOD = 6,
        GT = 7,
        GTE = 8,
        LT = 9,
        LTE = 10,
        EQ = 11,
        NE = 12,
        POP = 13,
        DUP = 14


    };
    struct Instruction{
        Opcode opcode;
        optional<long> immediate;
        explicit Instruction(Opcode op, optional<long> imm = std::nullopt) : opcode(op), immediate(imm) {}
    };
}



#endif //STACK_VM_INSTRUCTIONS_HPP







