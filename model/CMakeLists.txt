cmake_minimum_required(VERSION 3.3)
project(model)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#Internal files
GENERATE_PROJECT_STRUCTURE()

FIND_PACKAGE(CURL)
IF(CURL_FOUND)
    INCLUDE_DIRECTORIES(${CURL_INCLUDE_DIR})
    SET(requiredlibs ${requiredlibs} ${CURL_LIBRARIES} )
ELSE(CURL_FOUND)
    MESSAGE(FATAL_ERROR "Could not find the CURL library and development files.")
ENDIF(CURL_FOUND)

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_INCLUDES_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_HEADERS_DIR})

target_link_libraries(${PROJECT_NAME} common)
target_link_libraries(${PROJECT_NAME} curl)
add_dependencies(${PROJECT_NAME} common)
