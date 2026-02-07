add_library(parser Parser.cpp)

target_include_directories(parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(parser PUBLIC lexer ast)