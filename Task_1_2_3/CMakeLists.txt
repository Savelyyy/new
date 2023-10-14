cmake_minimum_required(VERSION 3.0)

project(compareVandR)

# Создание разделяемой библиотеки
add_library(compareVandR SHARED
    compareVandR.cpp
)

# Указание директории, где хранятся заголовочные файлы
target_include_directories(compareVandR PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(task_1_2_3 task_1_2_3.cpp)

# Укажите зависимость от вашей библиотеки
target_link_libraries(task_1_2_3 compareVandR)
