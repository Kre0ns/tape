add_subdirectory(ast)
add_subdirectory(lexer)
add_subdirectory(state)

add_executable(tape main.cpp)

target_link_libraries(tape PRIVATE lexer ast state)