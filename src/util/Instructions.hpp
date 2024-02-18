//
// Created by Maximilian Vater on 15.01.24.
//

#ifndef STACK_VM_INSTRUCTIONS_HPP
#define STACK_VM_INSTRUCTIONS_HPP

#include <optional>
#include "../vm/CSObject.hpp"


using std::optional;

namespace Instructions {
    enum Opcode {
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
        DUP = 14,
        JMP = 15,
        JIF = 16,
        LOAD = 17,
        STORE = 18,
        CALL = 19,
        RET = 20,
        NOT = 21,
        NEW_LIST = 22,
        PUSH_LIST = 23,
        POP_LIST = 24,
        LEN_LIST = 25,
        SET_ELM_LIST = 27,
        GET_ELM_LIST = 28,
        WRITE_OUT = 29,
        READ_IN = 30
    };

    struct Instruction {
        Opcode opcode;
        optional<long> idx;
        optional<CSObject> value;

        explicit Instruction(Opcode op, optional<long> idx = std::nullopt, optional<CSObject> value = std::nullopt)
                : opcode(op), idx(idx), value(value) {}
    };
}

#endif //STACK_VM_INSTRUCTIONS_HPP







