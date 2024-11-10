cmake_minimum_required(VERSION 3.5)

project(Library_Management)

add_executable(library_Management components/main.cpp)

add_subdirectory(raylib/)

target_include_directories(
    library_Management 
    PRIVATE
    raylib/src
)

target_link_libraries(
    library_Management 
    PRIVATE
    raylib
)