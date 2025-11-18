cmake_minimum_required(VERSION 3.16)
project(JsonParser CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.71 REQUIRED)

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)
include(Catch)

add_library(json_parser INTERFACE)
target_include_directories(json_parser INTERFACE include)
target_link_libraries(json_parser INTERFACE Boost::boost)

enable_testing()

file(GLOB TESTS tests/*.cpp)
add_executable(tests_json_parser ${TESTS})
target_link_libraries(tests_json_parser json_parser Catch2::Catch2WithMain)
catch_discover_tests(tests_json_parser)