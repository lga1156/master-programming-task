cmake_minimum_required(VERSION 3.16)
project(TypeMap CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Немного заколхозил с библиотекой, лень разбираться((
include(FetchContent)
FetchContent_Declare(
    Catch2
    SOURCE_DIR /workspaces/master-programming-task/lab4/build/_deps/catch2-src
)
FetchContent_MakeAvailable(Catch2)
include(Catch)

add_library(TypeMap INTERFACE)

target_include_directories(TypeMap INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing()

# Создаем исполняемый файл для тестов из вашего .cpp файла
# Замените iterator.cpp на tests/iterator.cpp, если файл лежит в папке tests
add_executable(tests_type_map tests/type_map.cpp)

# Связываем тесты с нашей библиотекой "variant" и с Catch2
target_link_libraries(tests_type_map PRIVATE TypeMap Catch2::Catch2WithMain)

# Автоматически находим тесты Catch2
catch_discover_tests(tests_type_map)