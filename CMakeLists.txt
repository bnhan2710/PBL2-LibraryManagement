cmake_minimum_required(VERSION 3.16)

project(PBL2-LibraryManagement VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Danh sách tệp nguồn
set(PROJECT_SOURCES
        Login.cpp
        Login.h
        main.cpp
        Resource.qrc
        src/Author/Author.cpp src/Author/Author.h src/Book/Book.cpp src/Book/Book.h src/BorrowReturn/BorrowReturn.cpp src/BorrowReturn/BorrowReturn.h src/Category/Category.cpp src/Category/Category.h src/Publisher/Publisher.cpp src/Publisher/Publisher.h src/Role/Role.cpp src/Role/Role.h src/User/User.cpp src/User/User.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PBL2-LibraryManagement
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Login.cpp
        Login.h
        main.cpp
        Resource.qrc
        src/Author/Author.cpp src/Author/Author.h src/Book/Book.cpp src/Book/Book.h src/BorrowReturn/BorrowReturn.cpp src/BorrowReturn/BorrowReturn.h src/Category/Category.cpp src/Category/Category.h src/Publisher/Publisher.cpp src/Publisher/Publisher.h src/Role/Role.cpp src/Role/Role.h src/User/User.cpp src/User/User.h
    )
else()
    add_executable(PBL2-LibraryManagement
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(PBL2-LibraryManagement PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(PBL2-LibraryManagement PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS PBL2-LibraryManagement
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PBL2-LibraryManagement)
endif()
