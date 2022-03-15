cmake_minimum_required(VERSION 2.4)
project(compiler)
include_directories(${PROJECT_SOURCE_DIR})

LIST(APPEND SRC_LIST main.cpp CFG_data.cpp MyParser.hpp)
add_subdirectory(productions)
message(STATUS ${SRC_LIST})
add_executable(Main ${SRC_LIST})

#target_link_libraries(lib_productions)