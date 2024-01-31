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
        BOOST_CHECK_EQUAL(vm.valueIp(), 0);
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
        BOOST_CHECK_EQUAL(vm.valueIp(), 0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.valueIp(), prog.size());
        BOOST_CHECK_EQUAL(vm.valueStop(), true);


    }

    BOOST_AUTO_TEST_CASE(jmp)
    {
        const vector<Instruction> prog = vector{Instruction(Opcode::JMP, optional(2L)), Instruction(Opcode::STOP),
                                                Instruction(Opcode::JMP, optional(1L))};
        auto vm = Machine{prog};
        BOOST_CHECK_EQUAL(vm.valueIp(), 0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.valueIp(), 2);
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }

    BOOST_AUTO_TEST_CASE(jif)
    {
        const vector<Instruction> prog = vector{
                Instruction(Opcode::PUSH, optional(1L)),
                Instruction(Opcode::JIF, optional(3L)),
                Instruction(Opcode::POP),
                Instruction(Opcode::PUSH, optional(0L)),
                Instruction(Opcode::JIF, optional(2)),
                Instruction(Opcode::STOP)
        };
        auto vm = Machine{prog};
        BOOST_CHECK_EQUAL(vm.valueIp(), 0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.valueIp(), 6);
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }

/*    BOOST_AUTO_TEST_CASE(load_var_not_initialized, *utf::disabled())
    {
        const vector<Instruction> prog = vector{
                Instruction(Opcode::LOAD, optional(0L)),
                Instruction(Opcode::STOP)
        };
        auto vm = Machine{prog};
        BOOST_CHECK_EQUAL(vm.valueIp(),0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.valueIp(), prog.size());
        BOOST_CHECK_EQUAL(vm.popLast(), 0);
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }*/

    BOOST_AUTO_TEST_CASE(load_var_initialized)
    {
        const vector<Instruction> prog = vector{
                Instruction(Opcode::PUSH, optional(5L)),
                Instruction(Opcode::STORE, optional(0L)),
                Instruction(Opcode::PUSH, optional(780L)),
                Instruction(Opcode::STORE, optional(1L)),
                Instruction(Opcode::LOAD, optional(0L)),
                Instruction(Opcode::LOAD, optional(1L)),
                Instruction(Opcode::STOP)
        };
        auto vm = Machine{prog};
        BOOST_CHECK_EQUAL(vm.valueIp(), 0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.valueIp(), prog.size());
        BOOST_CHECK_EQUAL(vm.popLast(), 780);
        BOOST_CHECK_EQUAL(vm.popLast(), 5);
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }

    BOOST_AUTO_TEST_CASE(max_a_b)
    {
        /*
         * int max(int a, int b) {
         *     if (a > b) {
         *         return a;
         *     } else {
         *         return b;
         *     }
         * }
         */
        const vector<Instruction> prog = vector{
                Instruction(Opcode::PUSH, optional(6L)),//1. arg
                Instruction(Opcode::PUSH, optional(4L)), // 2. arg
                Instruction(Opcode::CALL, optional(4L)), // call max(6,4);
                Instruction(Opcode::STOP),
                //max()
                Instruction(Opcode::STORE, optional(1L)),
                Instruction(Opcode::STORE, optional(0L)),
                Instruction(Opcode::LOAD, optional(0L)),
                Instruction(Opcode::LOAD, optional(1L)),
                Instruction(Opcode::GT),
                Instruction(Opcode::JIF, optional(12L)),
                Instruction(Opcode::LOAD, optional(1L)),
                Instruction(Opcode::RET),
                Instruction(Opcode::LOAD, optional(0L)),
                Instruction(Opcode::RET),
        };
        auto vm = Machine{prog};
        BOOST_CHECK_EQUAL(vm.valueIp(), 0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.popLast(), 6);

        //BOOST_CHECK_EQUAL(vm.valueIp(), prog.size());
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }

    BOOST_AUTO_TEST_CASE(recusion)
    {
        /*
         * int rec(int a) {
         *     if (a == 50) {
         *         return a;
         *     } else {
         *         return rec(a+1);
         *     }
         * }
         * rec(0);
         */
        const vector<Instruction> prog = vector{
                //main
                Instruction(Opcode::PUSH, optional(0L)),//1. arg
                Instruction(Opcode::CALL, optional(3L)), // call rec(0);
                Instruction(Opcode::STOP),
                //rec()
                Instruction(Opcode::STORE, optional(0L)),
                Instruction(Opcode::LOAD, optional(0L)),
                Instruction(Opcode::PUSH, optional(50L)),
                Instruction(Opcode::EQ),
                Instruction(Opcode::JIF, optional(13L)),
                //else path
                Instruction(Opcode::LOAD, optional(0L)),
                Instruction(Opcode::PUSH, optional(1L)),
                Instruction(Opcode::ADD),
                Instruction(Opcode::CALL, optional(3L)), // call rec(arg+1);
                Instruction(Opcode::JMP, optional(14L)),
                //if true path
                Instruction(Opcode::LOAD, optional(0L)),
                Instruction(Opcode::RET),
        };
        auto vm = Machine{prog};
        BOOST_CHECK_EQUAL(vm.valueIp(), 0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.popLast(), 50);

        //BOOST_CHECK_EQUAL(vm.valueIp(), prog.size());
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }

    BOOST_AUTO_TEST_CASE(while_simple)
    {
        /*
         * int total = 0;
         * int a = 6;
         * int b = 4;
         * while (b >= 1) {
         *  total += a;
         *  --b;
         * }
         *
         */
        const vector<Instruction> prog = vector{
                //a = 6
                Instruction(Opcode::PUSH, optional(6L)),
                Instruction(Opcode::STORE, optional(0L)),
                //b = 4
                Instruction(Opcode::PUSH, optional(4L)),
                Instruction(Opcode::STORE, optional(1L)),
                //total = 0;
                Instruction(Opcode::PUSH, optional(0L)),
                Instruction(Opcode::STORE, optional(2L)),
                //while
                Instruction(Opcode::LOAD, optional(1L)),
                Instruction(Opcode::PUSH, optional(1L)),
                Instruction(Opcode::GTE),
                Instruction(Opcode::NOT),
                Instruction(Opcode::JIF, optional(20L)),
                //inner loop
                Instruction(Instructions::LOAD, optional(0L)),
                Instruction(Instructions::LOAD, optional(2L)),
                Instruction(Instructions::ADD),
                Instruction(Instructions::STORE, optional(2L)),

                Instruction(Instructions::LOAD, optional(1L)),
                Instruction(Instructions::PUSH, optional(1L)),
                Instruction(Instructions::SUB),
                Instruction(Instructions::STORE, optional(1L)),
                Instruction(Instructions::JMP, optional(6L)),

                Instruction(Instructions::LOAD, optional(2L)),
                Instruction(Instructions::STOP)


        };
        auto vm = Machine{prog};
        BOOST_CHECK_EQUAL(vm.valueIp(), 0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.popLast(), 24);

        //BOOST_CHECK_EQUAL(vm.valueIp(), prog.size());
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }

    BOOST_AUTO_TEST_CASE(array_test) {
        /*
         * var arr = new Array(1,2,3);
         * var sum = arr[0] + arr[1] + arr[2]
         *
         */
        const vector<Instruction> prog = {

                Instruction(Opcode::PUSH, optional(3L)),
                Instruction(Opcode::PUSH, optional(2L)),
                Instruction(Opcode::PUSH, optional(1L)),

                Instruction(Opcode::PUSH, optional(3L)),
                Instruction(Opcode::NEW_LIST, optional(0L)),

                Instruction(Opcode::PUSH, optional(0L)),//idx
                Instruction(Opcode::GET_ELM_LIST, optional(0L)),//list index

                Instruction(Opcode::PUSH, optional(1L)),//idx
                Instruction(Opcode::GET_ELM_LIST, optional(0L)),//list index

                Instruction(Opcode::ADD),

                Instruction(Opcode::PUSH, optional(2L)),//idx
                Instruction(Opcode::GET_ELM_LIST, optional(0L)),//list index

                Instruction(Opcode::ADD),

                Instruction(Opcode::STOP)
        };
        auto vm = Machine{prog};
        BOOST_CHECK_EQUAL(vm.valueIp(), 0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.popLast(), 6);
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }

    BOOST_AUTO_TEST_CASE(list_append) {
        /*
         * var arr = new List();
         * arr.append(1);
         *
         */
        const vector<Instruction> prog = {
                Instruction(Opcode::PUSH, optional(0L)),//init size
                Instruction(Opcode::NEW_LIST, optional(0L)),

                Instruction(Opcode::PUSH, optional(1L)),//idx
                Instruction(Opcode::PUSH_LIST, optional(0L)),//list index

                Instruction(Opcode::PUSH, optional(0L)),//idx
                Instruction(Opcode::GET_ELM_LIST, optional(0L)),//list index

                Instruction(Opcode::STOP)
        };
        auto vm = Machine{prog};
        BOOST_CHECK_EQUAL(vm.valueIp(), 0);
        vm.run();
        BOOST_CHECK_EQUAL(vm.popLast(), 1);
        BOOST_CHECK_EQUAL(vm.valueStop(), true);
    }


    /*
     * class Test{
     *  var i = 0;
     *  var list = new List();
     * }
     * var t = new Test();
     * t.list.append(1);
     */

//    BOOST_AUTO_TEST_CASE(iteration)
//    {
//        /*
//         * fn factorial(Integer n){
//         *  var r = 1;
//         *  while (n > 0) {
//         *      r = r * n;
//         *      n = n - 1;
//         *  }
//         *  return r;
//         * }
//         * rec(0);
//         */
//        const vector<Instruction> prog = vector{
//                Instruction(Opcode::PUSH, optional(5L)),//1. arg
//                Instruction(Opcode::CALL, optional(3L)), // call factorial(5);
//                Instruction(Opcode::STOP),
//                //rec()
//                Instruction(Opcode::STORE, optional(0L)),
//                Instruction(Opcode::LOAD, optional(0L)),
//                Instruction(Opcode::PUSH, optional(2L)),
//                Instruction(Opcode::EQ),
//                Instruction(Opcode::JIF,optional(12L)),
//                Instruction(Opcode::LOAD, optional(0L)),
//                Instruction(Opcode::PUSH, optional(1L)),
//                Instruction(Opcode::ADD),
//                Instruction(Opcode::CALL, optional(3L)), // call rec(5);
//                //else path
//                Instruction(Opcode::LOAD, optional(0L)),
//                Instruction(Opcode::RET),
//        };
//        auto vm = Machine{prog};
//        BOOST_CHECK_EQUAL(vm.valueIp(),0);
//        vm.run();
//        BOOST_CHECK_EQUAL(vm.popLast(), 5);
//
//        //BOOST_CHECK_EQUAL(vm.valueIp(), prog.size());
//        BOOST_CHECK_EQUAL(vm.valueStop(), true);
//    }

BOOST_AUTO_TEST_SUITE_END()
