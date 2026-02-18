add_subdirectory(ast)
add_subdirectory(lexer)
add_subdirectory(state)
add_subdirectory(parser)
add_subdirectory(errors)
add_subdirectory(interpreter)
add_subdirectory(repl)
add_subdirectory(runner)

add_executable(tape main.cpp)

target_link_libraries(tape PRIVATE repl)