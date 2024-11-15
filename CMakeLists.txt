cmake_minimum_required(VERSION 3.5)

project(Library_Management)

set(CMAKE_CXX_STANDARD 20)
set(COMPONENTS_DIR ${CMAKE_SOURCE_DIR}/components)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE COMPONENTS_SOURCES ${COMPONENTS_DIR}/**/*.cpp)
file(GLOB_RECURSE SRC_SOURCES ${SRC_DIR}/**/*.cpp)
list(FILTER COMPONENTS_SOURCES EXCLUDE REGEX "${COMPONENTS_DIR}/UI_Console/.*")

add_executable(library_Management)

add_subdirectory(raylib/)

target_sources(
    library_Management
    PRIVATE
    ${COMPONENTS_SOURCES}
    ${SRC_SOURCES}
    ${COMPONENTS_DIR}/main.cpp
)

target_include_directories(
    library_Management 
    PRIVATE
    components/
    raylib/src
    utils/
)

target_link_libraries(
    library_Management 
    PRIVATE
    raylib
)