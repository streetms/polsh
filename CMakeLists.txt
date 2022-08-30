cmake_minimum_required(VERSION 3.21)
project(polsh)

set(CMAKE_CXX_STANDARD 17)

add_executable(polsh main.cpp Lexeme.cpp Lexeme.h utility.h utility.cpp polsh.h polsh.cpp)
