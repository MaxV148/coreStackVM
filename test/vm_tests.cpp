#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE DemoTests
#endif

#include <boost/test/unit_test.hpp>

#include "../src/vm/Machine.hpp"
#include <vector>
#include <optional>


using std::vector;
using std::optional;

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
        const vector<Instruction> prog = vector{Instruction(Opcode::PUSH, optional(2L)),
                                                Instruction(Opcode::PUSH, optional(3L)),
                                                Instruction(Opcode::ADD), Instruction(Opcode::STOP)};
        auto vm = Machine(prog);
        BOOST_CHECK_EQUAL(vm.valueIp(), 0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.valueIp(), prog.size());
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
        BOOST_CHECK_EQUAL(vm.popLast(), 5);
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }

    BOOST_AUTO_TEST_CASE(vm_sub_neg)
    {
        const vector<Instruction> prog = vector{Instruction(Opcode::PUSH, optional(2L)),
                                                Instruction(Opcode::PUSH, optional(3L)),
                                                Instruction(Opcode::SUB), Instruction(Opcode::STOP)};
        auto vm = Machine(prog);
        BOOST_CHECK_EQUAL(vm.valueIp(), 0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.valueIp(), prog.size());
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
        BOOST_CHECK_EQUAL(vm.popLast(), -1);
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }

    BOOST_AUTO_TEST_CASE(vm_sub_pos)
    {
        const vector<Instruction> prog = vector{Instruction(Opcode::PUSH, optional(20L)),
                                                Instruction(Opcode::PUSH, optional(5L)),
                                                Instruction(Opcode::SUB), Instruction(Opcode::STOP)};
        auto vm = Machine(prog);
        BOOST_CHECK_EQUAL(vm.valueIp(), 0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.valueIp(), prog.size());
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
        BOOST_CHECK_EQUAL(vm.popLast(), 15);
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }

    BOOST_AUTO_TEST_CASE(vm_mul)
    {
        const vector<Instruction> prog = vector{Instruction(Opcode::PUSH, optional(20L)),
                                                Instruction(Opcode::PUSH, optional(5L)),
                                                Instruction(Opcode::MUL), Instruction(Opcode::STOP)};
        auto vm = Machine(prog);
        BOOST_CHECK_EQUAL(vm.valueIp(), 0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.valueIp(), prog.size());
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
        BOOST_CHECK_EQUAL(vm.popLast(), 100);
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }

    BOOST_AUTO_TEST_CASE(vm_div)
    {
        const vector<Instruction> prog = vector{Instruction(Opcode::PUSH, optional(20L)),
                                                Instruction(Opcode::PUSH, optional(5L)),
                                                Instruction(Opcode::DIV), Instruction(Opcode::STOP)};
        auto vm = Machine(prog);
        BOOST_CHECK_EQUAL(vm.valueIp(), 0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.valueIp(), prog.size());
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
        BOOST_CHECK_EQUAL(vm.popLast(), 4);
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }

    BOOST_AUTO_TEST_CASE(vm_div_frac)
    {
        const vector<Instruction> prog = vector{Instruction(Opcode::PUSH, optional(28L)),
                                                Instruction(Opcode::PUSH, optional(5L)),
                                                Instruction(Opcode::DIV), Instruction(Opcode::STOP)};
        auto vm = Machine(prog);
        BOOST_CHECK_EQUAL(vm.valueIp(), 0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.valueIp(), prog.size());
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
        BOOST_CHECK_EQUAL(vm.popLast(), 5);
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }

    BOOST_AUTO_TEST_CASE(vm_mod)
    {
        const vector<Instruction> prog = vector{Instruction(Opcode::PUSH, optional(25L)),
                                                Instruction(Opcode::PUSH, optional(5L)),
                                                Instruction(Opcode::MOD), Instruction(Opcode::STOP)};
        auto vm = Machine(prog);
        BOOST_CHECK_EQUAL(vm.valueIp(), 0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.valueIp(), prog.size());
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
        BOOST_CHECK_EQUAL(vm.popLast(), 0);
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }

    BOOST_AUTO_TEST_CASE(vm_gt)
    {
        const vector<Instruction> prog = vector{Instruction(Opcode::PUSH, optional(25L)),
                                                Instruction(Opcode::PUSH, optional(5L)),
                                                Instruction(Opcode::GT), Instruction(Opcode::STOP)};
        auto vm = Machine(prog);
        BOOST_CHECK_EQUAL(vm.valueIp(), 0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.valueIp(), prog.size());
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
        BOOST_CHECK_EQUAL(vm.popLast(), 1);
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }

    BOOST_AUTO_TEST_CASE(vm_gte)
    {
        const vector<Instruction> prog = vector{Instruction(Opcode::PUSH, optional(25L)),
                                                Instruction(Opcode::PUSH, optional(25L)),
                                                Instruction(Opcode::GTE), Instruction(Opcode::STOP)};
        auto vm = Machine(prog);
        BOOST_CHECK_EQUAL(vm.valueIp(), 0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.valueIp(), prog.size());
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
        BOOST_CHECK_EQUAL(vm.popLast(), 1);
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }

    BOOST_AUTO_TEST_CASE(vm_lt)
    {
        const vector<Instruction> prog = vector{Instruction(Opcode::PUSH, optional(1234L)),
                                                Instruction(Opcode::PUSH, optional(5655L)),
                                                Instruction(Opcode::LT), Instruction(Opcode::STOP)};
        auto vm = Machine(prog);
        BOOST_CHECK_EQUAL(vm.valueIp(), 0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.valueIp(), prog.size());
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
        BOOST_CHECK_EQUAL(vm.popLast(), 1);
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }

    BOOST_AUTO_TEST_CASE(vm_lte)
    {
        const vector<Instruction> prog = vector{Instruction(Opcode::PUSH, optional(1234L)),
                                                Instruction(Opcode::PUSH, optional(1234L)),
                                                Instruction(Opcode::LTE), Instruction(Opcode::STOP)};
        auto vm = Machine(prog);
        BOOST_CHECK_EQUAL(vm.valueIp(), 0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.valueIp(), prog.size());
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
        BOOST_CHECK_EQUAL(vm.popLast(), 1);
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }

    BOOST_AUTO_TEST_CASE(vm_eq)
    {
        const vector<Instruction> prog = vector{Instruction(Opcode::PUSH, optional(1234L)),
                                                Instruction(Opcode::PUSH, optional(12334L)),
                                                Instruction(Opcode::EQ), Instruction(Opcode::STOP)};
        auto vm = Machine(prog);
        BOOST_CHECK_EQUAL(vm.valueIp(), 0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.valueIp(), prog.size());
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
        BOOST_CHECK_EQUAL(vm.popLast(), 0);
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }

    BOOST_AUTO_TEST_CASE(vm_ne)
    {
        const vector<Instruction> prog = vector{Instruction(Opcode::PUSH, optional(1234L)),
                                                Instruction(Opcode::PUSH, optional(1234L)),
                                                Instruction(Opcode::NE), Instruction(Opcode::STOP)};
        auto vm = Machine(prog);
        BOOST_CHECK_EQUAL(vm.valueIp(), 0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.valueIp(), prog.size());
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
        BOOST_CHECK_EQUAL(vm.popLast(), 0);
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }

    BOOST_AUTO_TEST_CASE(dup)
    {
        const vector<Instruction> prog = vector{Instruction(Opcode::PUSH, optional(1234L)), Instruction(Opcode::DUP),
                                                Instruction(Opcode::STOP)};
        auto vm = Machine{prog};
        BOOST_CHECK_EQUAL(vm.valueIp(),0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.valueIp(), prog.size());
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
        BOOST_CHECK_EQUAL(vm.popLast(), 1234L);
        BOOST_CHECK_EQUAL(vm.popLast(), 1234L);

    }
    BOOST_AUTO_TEST_CASE(pop)
    {
        const vector<Instruction> prog = vector{Instruction(Opcode::PUSH, optional(1234L)), Instruction(Opcode::POP),
                                                Instruction(Opcode::STOP)};
        auto vm = Machine{prog};
        BOOST_CHECK_EQUAL(vm.valueIp(),0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.valueIp(), prog.size());
        BOOST_CHECK_EQUAL(vm.valueStop(), true);


    }

    BOOST_AUTO_TEST_CASE(jmp)
    {
        const vector<Instruction> prog = vector{Instruction(Opcode::JMP, optional(2L)), Instruction(Opcode::STOP),
                                                Instruction(Opcode::JMP,optional(1L))};
        auto vm = Machine{prog};
        BOOST_CHECK_EQUAL(vm.valueIp(),0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.valueIp(), 2);
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }
    BOOST_AUTO_TEST_CASE(jif)
    {
        const vector<Instruction> prog = vector{
            Instruction(Opcode::PUSH, optional(1L)),
            Instruction(Opcode::JIF,optional(3L)),
            Instruction(Opcode::POP),
            Instruction(Opcode::PUSH, optional(0L)),
            Instruction(Opcode::JIF,optional(2)),
            Instruction(Opcode::STOP)
        };
        auto vm = Machine{prog};
        BOOST_CHECK_EQUAL(vm.valueIp(),0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.valueIp(), 6);
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }

BOOST_AUTO_TEST_SUITE_END()
