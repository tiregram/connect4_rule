cmake_minimum_required (VERSION 2.8.11)
project (Connect4_rule)
set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE C4_FILE_LIB src/*.cpp)

add_library(c4rule_S SHARED ${C4_FILE_LIB})
add_library(c4rule STATIC ${C4_FILE_LIB})

add_definitions("-D_GLIBCXX_USE_CXX11_ABI=0")
