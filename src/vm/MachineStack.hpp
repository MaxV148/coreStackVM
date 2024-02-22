//
// Created by Maximilian Vater on 17.01.24.
//

#ifndef CMAKE_BOOST_DEMO_MACHINESTACK_HPP
#define CMAKE_BOOST_DEMO_MACHINESTACK_HPP
#include <stack>
#include <memory>
#include "../util/Instructions.hpp"

using std::stack; using Instructions::Instruction; using std::unique_ptr;


class MachineStack {
    stack<unique_ptr<CSObject>> stack{};
public:
    explicit MachineStack();
    unique_ptr<CSObject> popStack();
    void pushStack(unique_ptr<CSObject> value);
};

#endif //CMAKE_BOOST_DEMO_MACHINESTACK_HPP
