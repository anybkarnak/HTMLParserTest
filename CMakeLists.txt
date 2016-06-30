cmake_minimum_required(VERSION 3.3)
project(html-parser-test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
ENDIF()

set(CMAKE_PREFIX_PATH "/home/karnak/Qt/5.6/gcc_64/lib/cmake/Qt5Widgets")
MESSAGE( STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY:         " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
MESSAGE( STATUS "CMAKE_LIBRARY_OUTPUT_DIRECTORY:         " ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} )

#Include macros
include(macros.cmake)

add_subdirectory(common)
add_subdirectory(model)
add_subdirectory(presenter)
add_subdirectory(view)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets)

set(SOURCE_FILES main.cpp)
add_executable(html-parser-test ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} common model view presenter)
add_dependencies(${PROJECT_NAME} common model view presenter)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
