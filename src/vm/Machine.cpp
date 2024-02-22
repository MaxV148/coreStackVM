//
// Created by Maximilian Vater on 15.01.24.
//

#include "Machine.hpp"
#include "CSTyp.hpp"
#include <iostream>

using std::cout;
using std::endl;
using Typing::CSObject;
using Typing::CSTypes;



Machine::Machine(vector<Instructions::Instruction*> const &instructions) : programVec(instructions), programStack() {
    frames.push(Stackframe{0});//initial Stackframe
}

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
            if (!instr.value.has_value()) {
                std::cerr << "Immediate value missing" << std::endl;
                return;
            }
            programStack.pushStack(instr.value.value());
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
            //TODO: implement DUP
            break;
        case Instructions::POP:
            programStack.popStack();
            break;
        case Instructions::JMP:
            jump(instr.idx.value());
            break;
        case Instructions::JIF:
            jumpOnTrue(instr.idx.value());
            break;
        case Instructions::LOAD:
            loadVar(instr.idx.value());
            break;
        case Instructions::STORE:
            storeVar(instr.idx.value());
            break;
        case Instructions::CALL:
            callFunction(instr.idx.value());
            break;
        case Instructions::RET:
            returnFromFunction();
            break;
        case Instructions::NOT:
            notInstr();
            break;
        case Instructions::NEW_LIST:
            newList(instr.idx.value());
            break;
        case Instructions::PUSH_LIST:
            pushList(instr.idx.value());
            break;
        case Instructions::LEN_LIST:
            getLenList(instr.idx.value());
            break;
        case Instructions::SET_ELM_LIST:
            setElemList(instr.idx.value());
            break;
        case Instructions::GET_ELM_LIST:
            getElemAt(instr.idx.value());
            break;
    }
}

void Machine::writeOut() {
    auto val = programStack.popStack();
    std::cout << val << std::endl;
}


void Machine::readIn() {

}

void Machine::callFunction(long imm) {
    auto newFrame = Stackframe(ip);
    frames.push(newFrame);
    ip = imm;
}

void Machine::returnFromFunction() {
    auto retAddress = getCurrentframe().getReturnAddress();
    frames.pop();
    ip = retAddress;
}

Stackframe &Machine::getCurrentframe() {
    return frames.top();
}

unsigned long Machine::valueIp() const {
    return ip;
}

unique_ptr<CSObject> Machine::popLast() {
    return std::move(programStack.popStack());
}

void Machine::jumpOnTrue(long imm) {
    auto val = programStack.popStack();
    if(val->getType() == CSTypes::Double){
        if (val == 1) {
            ip = imm;
        }
    }

}

void Machine::loadVar(long imm) {
    // TODO: fix Narrowing conversion
    auto &currFrame = getCurrentframe();
    programStack.pushStack(currFrame.getVariable(imm));
}

void Machine::storeVar(long imm) {
    // TODO: fix Narrowing conversion
    auto &currFrame = getCurrentframe();
    currFrame.setVariable(imm, programStack.popStack());
}

void Machine::jump(long val) {
    setIp(val);
}

void Machine::setIp(long val) {
    ip = val;
}

bool Machine::valueStop() const {
    return stopped;
}

void Machine::notInstr() {
    auto val = programStack.popStack();
    if (val == 0) {
        programStack.pushStack(1);
    } else {
        programStack.pushStack(0);
    }
}


void Machine::binary(Instructions::Opcode const &opcode) {
    auto n2 = programStack.popStack();
    auto n1 = programStack.popStack();
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

void Machine::newList(long idxList) {
    auto newList = VMList();
    auto initAmount = programStack.popStack();
    for (int i = 0; i < initAmount; ++i) {
        newList.add(programStack.popStack());
    }
    lists[idxList] = newList;
}

void Machine::pushList(long idxList) {
    auto val = programStack.popStack();
    lists[idxList].add(val);

}


void Machine::getLenList(long idxList) {
    auto len = lists[idxList].size();
    programStack.pushStack(len);
}

void Machine::setElemList(long idxList) {
    auto idxInList = programStack.popStack();
    auto val = programStack.popStack();
    lists[idxList].set(idxInList, val);

}

void Machine::getElemAt(long idxList) {
    auto idxInList = programStack.popStack();
    auto val = lists[idxList].get(idxInList);
    programStack.pushStack(val);
}


