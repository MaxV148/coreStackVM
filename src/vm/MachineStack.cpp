
#include "MachineStack.hpp"

MachineStack::MachineStack() = default;

CSObject* MachineStack::popStack() {
    auto val = stack.top();
    stack.pop();
    return val;
}

void MachineStack::pushStack(CSObject* value) {
    stack.push(value);
}

void MachineStack::dupStack() {
    auto val = popStack();
    pushStack(val);
    pushStack(val);
}