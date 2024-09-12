cmake_minimum_required(VERSION 3.29)
project(modular_vectors C)

set(CMAKE_C_STANDARD 11)

add_library(modular_vectors STATIC library.c)
