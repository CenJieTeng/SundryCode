cmake_minimum_required(VERSION 3.17)
project(TestDllSharedMemory)

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/SharedDll/include")

if (LIB)
    PickSourceFiles(
        ${CMAKE_CURRENT_SOURCE_DIR}/SharedDll/src
        CODEFILES
        #Exclude
        #...
    )
    add_definitions(-D SHAREDDLL_EXPORTS)
    add_library(SharedDll SHARED ${CODEFILES})
    SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/SharedDll/lib)
    install_targets(TARGET SharedDll)
    set_target_properties(
        SharedDll PROPERTIES LINKER_LANGUAGE C
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        OUTPUT_NAME "SharedDll"
        PREFIX ""
    )
else()
    link_directories("${CMAKE_CURRENT_SOURCE_DIR}/SharedDll/lib")
    link_libraries(SharedDll.lib)
    add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/main.cpp)
endif()

