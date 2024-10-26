cmake_minimum_required(VERSION 3.21) 
project(code_editor VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Curses REQUIRED)  

include_directories(${CURSES_INCLUDE_DIR})
add_executable(code_editor src/main.cpp)

target_link_libraries(code_editor ${CURSES_LIBRARIES})