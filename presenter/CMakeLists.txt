cmake_minimum_required(VERSION 3.3)
project(presenter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


#Internal files
GENERATE_PROJECT_STRUCTURE()
add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_INCLUDES_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_HEADERS_DIR})

target_link_libraries(${PROJECT_NAME} common)
add_dependencies(${PROJECT_NAME} common)
