# 1. Базовая настройка проекта
cmake_minimum_required(VERSION 3.16)
project(proxy_task LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 2. Включаем систему тестирования
enable_testing()

# 3. Находим необходимые пакеты
find_package(Threads REQUIRED)
find_package(Catch2 3 REQUIRED)

# 4. ПОДКЛЮЧАЕМ МОДУЛЬ С КОМАНДАМИ CATCH2
#    Вот эта строка исправляет ошибку!
include(Catch)

# 5. Объявляем нашу библиотеку proxy
add_library(proxy INTERFACE)
target_include_directories(proxy INTERFACE include)
target_link_libraries(proxy INTERFACE Threads::Threads)

# 6. Собираем тесты
file(GLOB TESTS tests/*.cpp)
add_executable(tests_proxy ${TESTS})

# 7. Линкуем тесты
target_link_libraries(tests_proxy PRIVATE proxy Catch2::Catch2WithMain)

# 8. Обнаруживаем тесты
# Теперь эта команда будет известна CMake
catch_discover_tests(tests_proxy)