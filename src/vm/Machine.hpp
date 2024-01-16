//
// Created by Maximilian Vater on 15.01.24.
//

#ifndef STACK_VM_MACHINE_HPP
#define STACK_VM_MACHINE_HPP
#include <vector>
#include <stack>
#include "../util/Instructions.hpp"

using std::vector; using std::stack; using Instructions::Instruction; using Instructions::Opcode;


class Machine {
    const vector<Instruction> programVec{};
    stack<long> programStack{};
    unsigned long sp{0};
    unsigned long ip{0};
    bool stopped{false};

public:
    explicit Machine(vector<Instruction>const& instructions);
    void run();
    void executeInstr(Instruction const& instr);
    void binary(Opcode const& opcode,long n1, long n2);
    unsigned long advanceIP();
    unsigned long advanceSP();
    Instruction nextInst();

};


#endif //STACK_VM_MACHINE_HPP
