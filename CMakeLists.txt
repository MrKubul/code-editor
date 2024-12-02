cmake_minimum_required(VERSION 3.21) 
project(code_editor VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

### NCURSES
find_package(Curses REQUIRED)  
include_directories(${CURSES_INCLUDE_DIR})

### FLEX
set(FLEX_FILE src/syntax_highlighter/syntax_highlighter.l)
find_package(FLEX REQUIRED)
FLEX_TARGET(SyntaxHighlighter ${FLEX_FILE} syntax_highlighter.cpp)
include_directories(src/syntax_highlighter/)

### COMPILING
# Source files
set(SOURCES
    ${FLEX_SyntaxHighlighter_OUTPUTS} 
    src/main.cpp                          # Your main program
)

add_executable(code_editor ${SOURCES})
target_link_libraries(code_editor ${CURSES_LIBRARIES})