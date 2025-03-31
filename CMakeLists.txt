cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES
    main.cpp
    funcs.cpp
    teacher.cpp
)

set(HEADERS
    structs.hpp
    funcs.hpp
    teacher.hpp
)

configure_file(tasks.txt tasks.txt COPYONLY)
configure_file(students.txt students.txt COPYONLY)

add_executable(MyExecutable ${SOURCES} ${HEADERS})
