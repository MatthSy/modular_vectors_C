cmake_minimum_required(VERSION 3.29)
project(modular_vectors_test C)

set(CMAKE_C_STANDARD 11)

add_executable(modular_vectors_test main.c
        tests.c tests.h
        ../library.c ../library.h
)