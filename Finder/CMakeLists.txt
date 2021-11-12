cmake_minimum_required(VERSION 3.17)
project(Finder)

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

PickSourceFiles(
    ${CMAKE_CURRENT_SOURCE_DIR}/
    CODEFILES
    #Exclude
    #...
)
add_executable(${PROJECT_NAME} ${CODEFILES} ${PROJECT_SOURCE_DIR}/main.cpp)