cmake_minimum_required(VERSION 3.5)

project(Library Management)

add_executable(library_management src/main.cpp)

target_include_directories(
    library_management 
    PRIVATE
    raylib/src
)

target_link_libraries(
    library_management 
    PRIVATE
    raylib
)