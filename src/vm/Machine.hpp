//
// Created by Maximilian Vater on 15.01.24.
//

#ifndef STACK_VM_MACHINE_HPP
#define STACK_VM_MACHINE_HPP
#include <vector>
#include <stack>
#include "../util/Instructions.hpp"
#include "./Stackframe.hpp"
#include "MachineStack.hpp"

using std::vector; using std::stack; using Instructions::Instruction; using Instructions::Opcode;

class Machine {
    const vector<Instruction> programVec{};
    MachineStack programStack;
    stack<Stackframe> frames;
    long ip{0};
    bool stopped{false};
    void binary(Opcode const& opcode);
    void notInstr();
    void loadVar(long imm);
    void storeVar(long imm);
    void setIp(long val);
    void jump(long val);
    void jumpOnTrue(long imm);
    Stackframe& getCurrentframe();
    void callFunction(long imm);
    void returnFromFunction();
public:
    explicit Machine(vector<Instruction>const& instructions);
    void run();
    void executeInstr(Instruction const& instr);
    unsigned long valueIp()const;
    bool valueStop()const;
    unsigned long advanceIP();
    Instruction nextInst();

    //only for testing
    long popLast();
};


#endif //STACK_VM_MACHINE_HPP
