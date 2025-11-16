cmake_minimum_required(VERSION 3.16)
project(Variant CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)
include(Catch)

add_library(variant INTERFACE)

target_include_directories(variant INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing()

# Создаем исполняемый файл для тестов из вашего .cpp файла
# Замените iterator.cpp на tests/iterator.cpp, если файл лежит в папке tests
add_executable(tests_variant tests/variant.cpp)

# Связываем тесты с нашей библиотекой "variant" и с Catch2
target_link_libraries(tests_variant PRIVATE variant Catch2::Catch2WithMain)

# Автоматически находим тесты Catch2
catch_discover_tests(tests_variant)