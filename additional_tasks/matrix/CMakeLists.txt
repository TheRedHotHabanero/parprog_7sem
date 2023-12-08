cmake_minimum_required(VERSION 3.16)
project(additional_matrix)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP REQUIRED)

# Создаем директорию для сборки
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

# Создаем директорию сборки, если она не существует
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR})

# Добавьте флаги OpenMP для компиляции и линковки
if(OpenMP_CXX_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

add_executable(additional_matrix
    ${CMAKE_SOURCE_DIR}/matrix.cpp
    ${CMAKE_SOURCE_DIR}/trivial.cpp
    ${CMAKE_SOURCE_DIR}/boosted.cpp
    ${CMAKE_SOURCE_DIR}/main.cpp)