cmake_minimum_required(VERSION 3.12)

project(rayengine)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendors)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS ${INCLUDE_DIR}/*.h)
file(GLOB_RECURSE TESTS ${TEST_DIR}/*.cpp)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories(include)

add_library(rayengine ${SOURCES} ${HEADERS})

add_subdirectory(vendors/raylib)
add_subdirectory(vendors/glm)

link_directories(vendors/raylib/src)
link_directories(vendors/raygui/src)

target_link_libraries(rayengine raylib glm)
target_include_directories(rayengine PRIVATE vendors/raylib/src)
target_include_directories(rayengine PRIVATE vendors/raygui/src)
target_include_directories(rayengine PRIVATE vendors/glm/glm)

add_executable(rayengine_test ${TESTS})

target_link_libraries(rayengine_test rayengine)