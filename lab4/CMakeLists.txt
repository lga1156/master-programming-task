# --- Общие настройки проекта ---
cmake_minimum_required(VERSION 3.16)
project(ImageIteratorProject CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Зависимости (Boost и Catch2) ---

# Ищем Boost. Теперь он будет найден, т.к. мы его установили.
find_package(Boost 1.71 REQUIRED)

# Ищем Catch2. Если не найден, скачиваем автоматически.
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)
include(Catch)

# --- Наша библиотека "iterator" ---
# Так как у нас только заголовочный файл, библиотека-интерфейс - это то, что нужно.
add_library(iterator INTERFACE)

# Указываем, что заголовочные файлы находятся в той же папке, что и CMakeLists.txt
target_include_directories(iterator INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Связываем нашу "библиотеку" с Boost
target_link_libraries(iterator INTERFACE Boost::boost)

# --- Тесты ---
enable_testing()

# Создаем исполняемый файл для тестов из вашего .cpp файла
# Замените iterator.cpp на tests/iterator.cpp, если файл лежит в папке tests
add_executable(tests_iterator tests/iterator.cpp)

# Связываем тесты с нашей библиотекой "iterator" и с Catch2
target_link_libraries(tests_iterator PRIVATE iterator Catch2::Catch2WithMain)

# Автоматически находим тесты Catch2
catch_discover_tests(tests_iterator)