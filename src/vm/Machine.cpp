//
// Created by Maximilian Vater on 15.01.24.
//

#include "Machine.hpp"
#include <iostream>

using std::cout; using std::endl;

Machine::Machine(vector<Instructions::Instruction> const &instructions) : programVec(instructions) {}

void Machine::run() {
    while (!stopped) {
        auto nextInst = Machine::nextInst();
        executeInstr(nextInst);
    }

}

void Machine::executeInstr(Instruction const &instr) {

    auto opcode = instr.opcode;
    long val{};
    switch (opcode) {
        case Instructions::STOP:
            stopped = true;
            return;
        case Instructions::PUSH:
            if (!instr.immediate.has_value()) {
                std::cerr << "Immediate value missing" << std::endl;
                return;
            }
            val = instr.immediate.value();
            std::cout << "PUSHED: " << val << endl;
            programStack.push(instr.immediate.value());
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
            long n2 = popStack();
            long n1 = popStack();
            binary(opcode, n1, n2);
            break;
    }
}

unsigned long Machine::valueIp() const {
    return ip;
}

bool Machine::valueStop() const {
    return stopped;
}


long Machine::popStack() {
    auto val = programStack.top();
    programStack.pop();
    return val;
}

void Machine::binary(Instructions::Opcode const &opcode, long n1, long n2) {
    switch (opcode) {
        case Instructions::ADD:
            programStack.push(n1 + n2);
            break;
        case Instructions::SUB:
            programStack.push(n1 - n1);
            break;
        case Instructions::MUL:
            programStack.push(n1 * n2);
            break;
        case Instructions::DIV:
            programStack.push(n1 / n2);
            break;
        case Instructions::MOD:
            programStack.push(n1 % n2);
            break;
        case Instructions::GT:
            programStack.push(n1 > n2);
            break;
        case Instructions::GTE:
            programStack.push(n1 >= n2);
            break;
        case Instructions::LT:
            programStack.push(n1 < n2);
            break;
        case Instructions::LTE:
            programStack.push(n1 <= n2);
            break;
        case Instructions::EQ:
            programStack.push(n1 == n2);
            break;
        case Instructions::NE:
            programStack.push(n1 != n2);
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


