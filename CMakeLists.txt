cmake_minimum_required(VERSION 3.21) 
project(code_editor VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Custom command to build the compiler using its Makefile
add_custom_command(
    OUTPUT compiler_built
    COMMAND ${CMAKE_MAKE_PROGRAM} -C ${CMAKE_SOURCE_DIR}/src/compiler
    COMMENT "Building compiler in compiler/ directory..."
    VERBATIM
)

# Add the virtual_machine build step
add_custom_target(virtual_machine_build ALL
    COMMAND ${CMAKE_COMMAND} -E echo "Building virtual_machine..."
    COMMAND ${CMAKE_MAKE_PROGRAM}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src/maszyna_wirtualna
)

# Custom target to trigger the build of the compiler
add_custom_target(compile_compiler DEPENDS compiler_built)

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
add_dependencies(code_editor compile_compiler virtual_machine_build)
target_link_libraries(code_editor ${CURSES_LIBRARIES})
