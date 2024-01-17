
#include "MachineStack.hpp"

MachineStack::MachineStack() = default;

long MachineStack::popStack() {
    auto val = stack.top();
    stack.pop();
    return val;
}

void MachineStack::pushStack(long value) {
    stack.push(value);
}

void MachineStack::dupStack() {
    auto val = popStack();
    pushStack(val);
    pushStack(val);
}