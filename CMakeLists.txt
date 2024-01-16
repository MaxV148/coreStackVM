CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
project("StackVM")

SET(CMAKE_CXX_STANDARD 17)

set(ANTLR4_JAR src/thirdparty/antlr/antlr-4.13.1-complete.jar)
include_directories(${ANTLR4CPP_INCLUDE_DIRS})
link_directories(${ANTLR4CPP_LIBS})
message(STATUS "Found antlr4cpp libs: ${ANTLR4CPP_LIBS} and includes: ${ANTLR4CPP_INCLUDE_DIRS}")

#Boost.Lib testing

add_subdirectory(tests)



add_executable(test_antlr
        src/main/main.cpp
        main.hpp
        src/util/Instructions.hpp
        src/vm/Machine.cpp
        src/vm/Machine.hpp
        tests/vm_tests.cpp
)