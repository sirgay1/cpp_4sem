cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES
    main.cpp
    input_n_output.cpp
    find_roots.cpp
)

set(HEADERS
    structs.hpp
    input_n_output.hpp
    find_roots.hpp

)

add_executable(MyExecutable ${SOURCES} ${HEADERS})