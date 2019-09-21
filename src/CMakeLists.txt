cmake_minimum_required(VERSION 3.0)
project(Exomit)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")

set(src
    main.cpp
    definitions.h
    instruction.h
    instruction.cpp
    instructions.h
    instructions.cpp
    timerh/timer.h
    timerh/timer.cpp)

add_executable(exomit ${src})