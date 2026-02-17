add_library(repl REPL.cpp)

target_include_directories(repl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(repl PUBLIC ast errors state parser lexer interpreter)