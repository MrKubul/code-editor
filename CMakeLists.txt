cmake_minimum_required(VERSION 3.21) 
project(code_editor VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

# Komenda do skompilowania projektu kompilatora Gebalang
add_custom_target(compiler_build ALL
    COMMAND ${CMAKE_COMMAND} -E echo "Building compiler..."
    COMMAND ${CMAKE_MAKE_PROGRAM}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src/compiler
)

# Komenda do skompilowania projektu maszyny wirtualnej Gebalang
add_custom_target(virtual_machine_build ALL
    COMMAND ${CMAKE_COMMAND} -E echo "Building virtual_machine..."
    COMMAND ${CMAKE_MAKE_PROGRAM}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src/maszyna_wirtualna
)

# Kompiluje Lexer do podświetlania składni 
set(SYNTAX_HIGHLIGHTER_DIR ${CMAKE_SOURCE_DIR}/src/syntax_highlighter)

FLEX_TARGET(SyntaxHighlighterLexer
    ${SYNTAX_HIGHLIGHTER_DIR}/syntax_highlighter.l
    ${CMAKE_BINARY_DIR}/syntax_highlighter.cpp
    COMPILE_FLAGS "-P SH_"
)
include_directories(${CMAKE_SOURCE_DIR}/src/syntax_highlighter)

# Kompiluje Parser i Lexer języka Gebalang dla Analizatora Składniowego
set(CODE_PARSER_DIR ${CMAKE_SOURCE_DIR}/src/code_parser)

BISON_TARGET(Parser 
    ${CODE_PARSER_DIR}/parser.y
    ${CODE_PARSER_DIR}/parser.tab.cpp
    DEFINES_FILE ${CODE_PARSER_DIR}/parser.tab.hpp
)
include_directories(${CMAKE_SOURCE_DIR}/src/code_parser)

FLEX_TARGET(Lexer 
    ${CODE_PARSER_DIR}/lexer.l 
    ${CODE_PARSER_DIR}/lexer.cpp
)

# Ensure lexer depends on parser
add_flex_bison_dependency(Lexer Parser)

### NCURSES
find_package(Curses REQUIRED)  
include_directories(${CURSES_INCLUDE_DIR})

# Source files
set(SOURCES 
    ${FLEX_SyntaxHighlighterLexer_OUTPUTS}
    ${BISON_Parser_OUTPUT_SOURCE}
    ${FLEX_Lexer_OUTPUTS}    
    src/main.cpp     
)

add_executable(code_editor ${SOURCES})

target_include_directories(code_editor PRIVATE
    ${CMAKE_BINARY_DIR}         
    ${SYNTAX_HIGHLIGHTER_DIR}   
    ${CODE_PARSER_DIR}           
)

add_dependencies(code_editor compiler_build virtual_machine_build)

target_link_libraries(code_editor ${FLEX_LIBRARIES} ${BISON_LIBRARIES} ${CURSES_LIBRARIES})
