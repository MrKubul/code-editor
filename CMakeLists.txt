cmake_minimum_required(VERSION 3.21) 
project(code_editor VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(FLEX_FILE ${CMAKE_SOURCE_DIR}/syntax_highlight.l)

find_package(FLEX REQUIRED)
FLEX_TARGET(MyScanner ${FLEX_FILE} ${CMAKE_BINARY_DIR}/lex.yy.c)

find_package(Curses REQUIRED)  

include_directories(${CURSES_INCLUDE_DIR})
add_executable(code_editor src/main.cpp src/${FLEX_MyScanner_OUTPUTS})

target_link_libraries(code_editor ${CURSES_LIBRARIES})