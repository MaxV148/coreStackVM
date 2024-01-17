//
// Created by Maximilian Vater on 17.01.24.
//

#ifndef CMAKE_BOOST_DEMO_MACHINESTACK_HPP
#define CMAKE_BOOST_DEMO_MACHINESTACK_HPP
#include <array>
#include "../util/Instructions.hpp"

using std::array; using Instructions::Instruction;

constexpr unsigned STACK_SIZE = 1024;

class MachineStack {
    const array<Instruction,STACK_SIZE> stack;
    int stackPt{0};
public:
    Instruction popStack();
    void pushStack();
    int valueStackPt()const;


};


#endif //CMAKE_BOOST_DEMO_MACHINESTACK_HPP
