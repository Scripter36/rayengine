cmake_minimum_required(VERSION 3.10)

project(rayengine)

set(CMAKE_CXX_STANDARD 17)

# source files: in src/
file(GLOB_RECURSE SOURCES src/*.cpp)
# header files: in include/
file(GLOB_RECURSE HEADERS include/*.h)
include_directories(include)

add_executable(rayengine ${SOURCES} ${HEADERS})

add_subdirectory(vendors/raylib)
add_subdirectory(vendors/glm)

link_directories(vendors/raylib/src)
link_directories(vendors/raygui/src)

target_link_libraries(rayengine raylib glm)
target_include_directories(rayengine PRIVATE vendors/raylib/src)
target_include_directories(rayengine PRIVATE vendors/raygui/src)
target_include_directories(rayengine PRIVATE vendors/glm/glm)