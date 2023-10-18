# Устанавливаем каталог для библиотек (.a или .lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/temp")

# Устанавливаем каталог для разделяемых библиотек (.so или .dll)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/temp")

# Устанавливаем каталог для исполняемых файлов (вашего проекта)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/temp")

# Создание каталога "temp"
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/temp")

# Создание подкаталогов "Task_1", "Task_2" и "Task_3" внутри "temp"
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/temp/Task_1")
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/temp/Task_2")
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/temp/Task_3")

function(add_library_with_dependencies TARGET SOURCE)
    add_library(${TARGET} SHARED ${SOURCE})
    target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endfunction()

add_library_with_dependencies(task_1 task_1.cpp)
add_library_with_dependencies(task_2 task_2.cpp)
add_library_with_dependencies(task_3 task_3.cpp)
add_library_with_dependencies(compareVAndR compareVAndR.cpp)

add_executable(main main.cpp)

target_link_libraries(main task_1 task_2 task_3 compareVAndR)
