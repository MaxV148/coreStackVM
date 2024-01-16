//
// Created by Maximilian Vater on 15.01.24.
//

#include "Machine.hpp"
#include <iostream>


Machine::Machine(vector<Instructions::Instruction> const&instructions):programVec(instructions) {}

void Machine::run() {
    while(!stopped){
        auto nextInst = Machine::nextInst();
        executeInstr(nextInst);
    }

}

void Machine::executeInstr(Instruction const& instr) {

    auto opcode = instr.opcode;
    switch (opcode) {
        case Instructions::STOP:
            stopped = true;
            return;
        case Instructions::PUSH:
            if(!instr.immediate.has_value()){
                std::cerr << "Immediate value missing" << std::endl;
                return;
            }
            programStack.push(instr.immediate.value());
            break;
        case Instructions::ADD: case Instructions::SUB: case Instructions::MUL: case Instructions::DIV: case Instructions::MOD:
            auto n2 = nextInst().immediate.value();
            auto n1 = nextInst().immediate.value();
            binary(opcode,n1,n2);
            break;
    }
}


void Machine::binary(Instructions::Opcode const& opcode, long n1, long n2) {
    switch (opcode) {
        case Instructions::ADD:
            programStack.push(n1+n2);
            break;
        case Instructions::SUB:
            programStack.push(n1-n1);
            break;
        case Instructions::MUL:
            programStack.push(n1*n2);
            break;
        case Instructions::DIV:
            programStack.push(n1/n2);
            break;
        case Instructions::MOD:
            programStack.push(n1%n2);
            break;
        case Instructions::GT:
            programStack.push(n1>n2);
            break;
        case Instructions::GTE:
            programStack.push(n1>=n2);
            break;
        case Instructions::LT:
            programStack.push(n1<n2);
            break;
        case Instructions::LTE:
            programStack.push(n1<=n2);
            break;
        case Instructions::EQ:
            programStack.push(n1==n2);
            break;
    }
}

unsigned long Machine::advanceIP() {
    return ip++;
}

unsigned long Machine::advanceSP() {
    return sp++;
}

Instruction Machine::nextInst() {
    return programVec.at(advanceIP());
}
