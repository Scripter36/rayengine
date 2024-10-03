cmake_minimum_required(VERSION 3.28)
project(rayengine CXX CUDA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp ${SOURCE_DIR}/*.cu)
file(GLOB_RECURSE HEADERS ${INCLUDE_DIR}/*.h ${INCLUDE_DIR}/*.cuh)
file(GLOB_RECURSE TESTS ${TEST_DIR}/*.cpp ${TEST_DIR}/*.cu)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories(include)

add_library(rayengine ${SOURCES} ${HEADERS})
set_target_properties(rayengine PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

include(cmake/CPM.cmake)
CPMAddPackage("gh:raysan5/raylib#96d91a38923094951e481d9fbc26291026e48fea")
CPMAddPackage("gh:g-truc/glm#1.0.1")

target_link_libraries(rayengine raylib glm)
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    message(STATUS "OpenMP found")
    target_link_libraries(rayengine OpenMP::OpenMP_CXX)
endif()

add_executable(rayengine_test ${TESTS})
set_target_properties(rayengine_test PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

target_link_libraries(rayengine_test rayengine)