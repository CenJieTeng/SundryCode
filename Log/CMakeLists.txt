cmake_minimum_required(VERSION 3.17)
project(Log)

PickSourceFiles(
    ${CMAKE_CURRENT_SOURCE_DIR}/
    CODEFILES
    #Exclude
    #...
)

PickIncludeDirectories(
    ${CMAKE_SOURCE_DIR}/vendor/spdlog/include
    INCLUDEDIRS
    #Exclude
    #...
)

add_executable(${PROJECT_NAME} ${CODEFILES} ${PROJECT_SOURCE_DIR}/main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDEDIRS})