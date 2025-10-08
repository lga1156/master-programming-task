cmake_minimum_required(VERSION 3.16)
project(iomanip_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(iomanip INTERFACE)
target_include_directories(iomanip INTERFACE include)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/gprotect.cpp "#include <iomanip.hpp>\n")

file(GLOB TESTS tests/*.cpp)

find_package(Catch2 3 REQUIRED)
include(Catch)

add_executable(tests_iomanip ${TESTS} ${CMAKE_CURRENT_BINARY_DIR}/gprotect.cpp)
target_link_libraries(tests_iomanip PRIVATE iomanip Catch2::Catch2WithMain)

catch_discover_tests(tests_iomanip)