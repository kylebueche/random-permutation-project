cmake_minimum_required(VERSION 4.0)
project(random-permutation-project)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(permutations
                src/main.cpp
                src/polynomial.cpp)
