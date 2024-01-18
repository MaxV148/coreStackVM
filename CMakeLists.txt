cmake_minimum_required(VERSION 3.5)

# Definitions
set(PROJECT_NAME_STR coreStackVM)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

# Project title and define versioning
project(${PROJECT_NAME_STR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

#antlr4
set(ANTLR4_JAR src/thirdparty/antlr/antlr-4.13.1-complete.jar)
include_directories(${ANTLR4CPP_INCLUDE_DIRS})
link_directories(${ANTLR4CPP_LIBS})
message(STATUS "Found antlr4cpp libs: ${ANTLR4CPP_LIBS} and includes: ${ANTLR4CPP_INCLUDE_DIRS}")

# Gather all sources except the main entry point
file(GLOB_RECURSE INC_FILES src/*/*.hpp)
file(GLOB_RECURSE SRC_FILES src/*/*.cpp)

# Dependencies
find_package(Boost COMPONENTS filesystem system unit_test_framework REQUIRED)

# Unit test
add_subdirectory(test)

# Assign the include directories
include_directories(${Boost_INCLUDE_DIRS})

# Build
#set(SOURCE_FILES src/main.cpp $<TARGET_OBJECTS:demo_objects>)
set(SOURCE_FILES src/main.cpp ${INC_FILES} ${SRC_FILES}
        src/vm/MachineStack.cpp
        src/vm/MachineStack.hpp
        src/vm/Stackframe.cpp
        src/vm/Stackframe.hpp)
add_executable(cmake_boost_demo ${SOURCE_FILES})
target_link_libraries(cmake_boost_demo ${Boost_LIBRARIES})