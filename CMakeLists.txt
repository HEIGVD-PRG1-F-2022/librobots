cmake_minimum_required(VERSION 3.23)
project(librobots VERSION 0.2.0 DESCRIPTION "Librairie pour les robots")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_library(librobots STATIC src/Bonus.cpp src/Direction.cpp src/Message.cpp src/Position.cpp src/RobotState.cpp)
set_target_properties(librobots PROPERTIES VERSION ${PROJECT_VERSION})
target_include_directories(librobots PUBLIC include)

add_executable(librobots_example example/main.cpp)
target_link_libraries(librobots_example librobots)
