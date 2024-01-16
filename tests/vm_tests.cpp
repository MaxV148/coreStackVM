//
// Created by Maximilian Vater on 15.01.24.
//



#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN  // in only one cpp file

#include "../src/vm/Machine.hpp"
#include "../src/util/Instructions.hpp"
#include <vector>

using std::vector;

BOOST_AUTO_TEST_SUITE(vm)

    BOOST_AUTO_TEST_CASE(instruction)
    {
        auto inst = Instruction(Opcode::STOP);
        BOOST_ASSERT(inst.opcode == Opcode::STOP)




    }
BOOST_AUTO_TEST_SUITE_END()
