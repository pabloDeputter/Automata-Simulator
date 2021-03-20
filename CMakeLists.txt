cmake_minimum_required(VERSION 3.12)
project(Automata)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 14)

set(Automata_SOURCE_FILES
        src/DFA.h
        src/DFA.cpp
        src/json.hpp
        src/State.h
        src/State.cpp
        src/Transition.cpp src/Transition.h)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES main.cpp src/NFA.cpp src/NFA.h src/Utils.cpp src/Utils.h)

# Create RELEASE target
add_executable(Automata ${RELEASE_SOURCE_FILES} ${Automata_SOURCE_FILES})





