cmake_minimum_required(VERSION 3.3)
project(html-parser-test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")

MESSAGE( STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY:         " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
MESSAGE( STATUS "CMAKE_LIBRARY_OUTPUT_DIRECTORY:         " ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} )

#Include macros
include(macros.cmake)

add_subdirectory(common)
add_subdirectory(model)
add_subdirectory(presenter)
add_subdirectory(view)


set(SOURCE_FILES main.cpp)
add_executable(html-parser-test ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} common model view presenter)
add_dependencies(${PROJECT_NAME} common model view presenter)


