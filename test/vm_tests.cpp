#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE DemoTests
#endif

#include <boost/test/unit_test.hpp>

#include "../src/vm/Machine.hpp"
#include <vector>
#include <optional>


using std::vector; using std::optional;

BOOST_AUTO_TEST_SUITE(vm_tests)

    BOOST_AUTO_TEST_CASE(instruction_constructor)
    {
        auto inst = Instruction(Opcode::STOP);
        BOOST_CHECK_EQUAL(inst.opcode, Opcode::STOP);
    }

    BOOST_AUTO_TEST_CASE(vm_stop)
    {
        const vector<Instruction> prog = vector{Instruction(Opcode::STOP)};
        auto vm = Machine(prog);
        BOOST_CHECK_EQUAL(vm.valueIp(), 0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.valueIp(), 1);
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }

    BOOST_AUTO_TEST_CASE(vm_add)
    {
        const vector<Instruction> prog = vector{Instruction(Opcode::PUSH, optional(2L)), Instruction(Opcode::PUSH, optional(3L)),
                                                Instruction(Opcode::ADD), Instruction(Opcode::STOP)};
        auto vm = Machine(prog);
        BOOST_CHECK_EQUAL(vm.valueIp(), 0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.valueIp(), prog.size());
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
        BOOST_CHECK_EQUAL(vm.popStack(),5);
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }

BOOST_AUTO_TEST_SUITE_END()
