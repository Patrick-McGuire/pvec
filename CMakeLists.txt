cmake_minimum_required(VERSION 3.17)
project(pvec C)

set(CMAKE_C_STANDARD 99)

add_executable(pvec main.c pvec.c pvec.h)