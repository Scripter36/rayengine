cmake_minimum_required(VERSION 3.28)
project(rayengine CXX CUDA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendors)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp ${SOURCE_DIR}/*.cu)
file(GLOB_RECURSE HEADERS ${INCLUDE_DIR}/*.h ${INCLUDE_DIR}/*.cuh)
file(GLOB_RECURSE TESTS ${TEST_DIR}/*.cpp ${TEST_DIR}/*.cu)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories(include)

add_library(rayengine ${SOURCES} ${HEADERS})
set_target_properties(rayengine PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

add_subdirectory(vendors/raylib)
add_subdirectory(vendors/glm)

link_directories(vendors/raylib/src)
link_directories(vendors/raygui/src)

target_link_libraries(rayengine raylib glm)
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    message(STATUS "OpenMP found")
    target_link_libraries(rayengine OpenMP::OpenMP_CXX)
endif()
target_include_directories(rayengine PRIVATE vendors/raylib/src)
target_include_directories(rayengine PRIVATE vendors/raygui/src)
target_include_directories(rayengine PRIVATE vendors/glm/glm)

add_executable(rayengine_test ${TESTS})
set_target_properties(rayengine_test PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

target_link_libraries(rayengine_test rayengine)