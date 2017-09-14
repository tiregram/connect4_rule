cmake_minimum_required (VERSION 2.8.11)
project (Connect4_rule)

# lib build
file(GLOB_RECURSE C4_FILE_LIB src/*.cpp)
add_library(c4rule SHARED ${C4_FILE_LIB})

find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

# UT
file(GLOB_RECURSE C4_FILE_UT test/*.cpp)
add_executable(c4rule_ut ${C4_FILE_UT})


target_link_libraries(c4rule_ut
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      )




