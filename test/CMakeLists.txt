cmake_minimum_required(VERSION 3.11)

include(FetchContent)
FetchContent_Declare(
    gtest
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG master
)
FetchContent_GetProperties(gtest)
FetchContent_Populate(gtest)
add_subdirectory(${gtest_SOURCE_DIR} ${gtest_BINARY_DIR} EXCLUDE_FROM_ALL)

add_executable(unit_tests UnitTests.cpp)
target_include_directories(unit_tests PRIVATE ../include)
target_link_libraries(unit_tests PRIVATE gtest)
target_compile_options(unit_tests PRIVATE
    -Werror
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
    -Wsign-conversion
    -Wold-style-cast
)
add_test(NAME unit_tests COMMAND unit_tests)

add_executable(example Example.cpp)
target_link_libraries(example PRIVATE argon)

add_test(NAME flag--help COMMAND example --help)
set_property(TEST flag--help PROPERTY PASS_REGULAR_EXPRESSION
    "Usage
  example <filename> <args...> \\[options\\]

Argon CLI parser example program

Positions
  filename                Input file
  args...                 Various arguments

Options
  -h, --help              Show this help text
  --version               Print program version
  -d, --debug             Debug output
  -c, --count <value>     Number of instances
  --speed <value>         Initial speed
  -o, --output <value>    Output filename")

add_test(NAME flag--version COMMAND example --version)
set_property(TEST flag--version PROPERTY PASS_REGULAR_EXPRESSION "v0.0.0")
