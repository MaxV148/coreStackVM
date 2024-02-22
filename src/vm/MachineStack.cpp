
#include "MachineStack.hpp"
#include <memory>
#include "CSTyp.hpp"
using std::unique_ptr;
using CSTypes::CSObject;

MachineStack::MachineStack() = default;

unique_ptr<CSObject>MachineStack::popStack() {
    auto val = std::move(stack.top());
    stack.pop();
    return val;
}

void MachineStack::pushStack(unique_ptr<CSObject> value) {
    stack.push(std::move(value));
}

