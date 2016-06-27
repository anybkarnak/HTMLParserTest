cmake_minimum_required(VERSION 3.3)
project(view)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Widgets)


#Internal files
GENERATE_PROJECT_STRUCTURE()
add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_INCLUDES_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_HEADERS_DIR})

target_link_libraries(${PROJECT_NAME} common)
add_dependencies(${PROJECT_NAME} common)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
qt5_use_modules(${PROJECT_NAME} Widgets)