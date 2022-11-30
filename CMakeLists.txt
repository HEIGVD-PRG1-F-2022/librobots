cmake_minimum_required(VERSION 3.23)
project(librobots VERSION 0.1 DESCRIPTION "Librairie pour les robots")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_library(librobots STATIC src/robots.cpp)
set_target_properties(librobots PROPERTIES VERSION ${PROJECT_VERSION})
target_include_directories(librobots PUBLIC include)

add_executable(example example/main.cpp)
target_link_libraries(example librobots)