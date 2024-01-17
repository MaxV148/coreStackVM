//
// Created by Maximilian Vater on 17.01.24.
//

#ifndef CMAKE_BOOST_DEMO_MACHINESTACK_HPP
#define CMAKE_BOOST_DEMO_MACHINESTACK_HPP
#include <stack>
#include "../util/Instructions.hpp"

using std::stack; using Instructions::Instruction;


class MachineStack {
    stack<long> stack{};
public:
    explicit MachineStack();
    long popStack();
    void pushStack(long value);
    void dupStack();
};

#endif //CMAKE_BOOST_DEMO_MACHINESTACK_HPP
