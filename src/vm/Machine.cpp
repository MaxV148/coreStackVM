//
// Created by Maximilian Vater on 15.01.24.
//

#include "Machine.hpp"
#include <iostream>

using std::cout;
using std::endl;

Machine::Machine(vector<Instructions::Instruction> const &instructions) : programVec(instructions), programStack() {}

void Machine::run() {
    while (!stopped) {
        auto nextInst = Machine::nextInst();
        executeInstr(nextInst);
    }
}

void Machine::executeInstr(Instruction const &instr) {
    auto opcode = instr.opcode;
    switch (opcode) {
        case Instructions::STOP:
            stopped = true;
            return;
        case Instructions::PUSH:
            if (!instr.immediate.has_value()) {
                std::cerr << "Immediate value missing" << std::endl;
                return;
            }
            programStack.pushStack(instr.immediate.value());
            break;
        case Instructions::ADD:
        case Instructions::SUB:
        case Instructions::MUL:
        case Instructions::DIV:
        case Instructions::MOD:
        case Instructions::GTE:
        case Instructions::GT:
        case Instructions::LT:
        case Instructions::EQ:
        case Instructions::NE:
        case Instructions::LTE:
            binary(opcode);
            break;
        case Instructions::DUP:
            programStack.dupStack();
            break;
        case Instructions::POP:
            programStack.popStack();
            break;
    }
}

unsigned long Machine::valueIp() const {
    return ip;
}

long Machine::popLast() {
    return programStack.popStack();
}

bool Machine::valueStop() const {
    return stopped;
}


void Machine::binary(Instructions::Opcode const &opcode) {
    long n2 = programStack.popStack();
    long n1 = programStack.popStack();
    switch (opcode) {
        case Instructions::ADD:
            programStack.pushStack(n1 + n2);
            break;
        case Instructions::SUB:
            programStack.pushStack(n1 - n2);
            break;
        case Instructions::MUL:
            programStack.pushStack(n1 * n2);
            break;
        case Instructions::DIV:
            programStack.pushStack(n1 / n2);
            break;
        case Instructions::MOD:
            programStack.pushStack(n1 % n2);
            break;
        case Instructions::GT:
            programStack.pushStack(n1 > n2);
            break;
        case Instructions::GTE:
            programStack.pushStack(n1 >= n2);
            break;
        case Instructions::LT:
            programStack.pushStack(n1 < n2);
            break;
        case Instructions::LTE:
            programStack.pushStack(n1 <= n2);
            break;
        case Instructions::EQ:
            programStack.pushStack(n1 == n2);
            break;
        case Instructions::NE:
            programStack.pushStack(n1 != n2);
            break;
    }
}

unsigned long Machine::advanceIP() {
    return ++ip;
}

Instruction Machine::nextInst() {
    auto next = programVec.at(ip);
    advanceIP();
    return next;
}


