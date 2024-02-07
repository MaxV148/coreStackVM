//
// Created by Maximilian Vater on 15.01.24.
//

#ifndef STACK_VM_MACHINE_HPP
#define STACK_VM_MACHINE_HPP
#include <vector>
#include <unordered_map>
#include <stack>
#include "../util/Instructions.hpp"
#include "./Stackframe.hpp"
#include "MachineStack.hpp"
#include "VMList.hpp"

using std::vector; using std::stack; using Instructions::Instruction; using Instructions::Opcode; using std::unordered_map;

class Machine {
    const vector<Instruction> programVec{};
    MachineStack programStack;
    stack<Stackframe> frames;
    unordered_map<long,VMList> lists;
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
    void newList(long idxList);
    void pushList(long idxList);
    void popList(long idxList);
    void getLenList(long idxList);
    void setElemList(long idxList);
    void getElemAt(long idxList);
    void writeOut();
    void readIn();


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
