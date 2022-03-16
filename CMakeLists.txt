cmake_minimum_required(VERSION 2.4)
project(compiler)

find_package(Java REQUIRED)

include(UseJava)

add_jar(Constructor
        constructor/Constructor.java
        ENTRY_POINT Constructor
        OUTPUT_NAME Constructor
        OUTPUT_DIR "${PROJECT_BINARY_DIR}"
        )

add_executable(CFG_rules productions/Productions.cc productions/production_printer.cpp)
add_custom_command(
        OUTPUT token_data.cpp CFG_data.cpp
        COMMAND java -jar ${PROJECT_BINARY_DIR}/Constructor.jar constructor/tokenlist CFG_rules
        DEPEND Constructor CFG_rules constructor/tokenlist
        )

# final build
include_directories(
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/token "
        "${PROJECT_SOURCE_DIR}/productions"
        "${PROJECT_SOURCE_DIR}/parser"
)

LIST(APPEND SRC_LIST main.cpp token_data.cpp CFG_data.cpp)

add_subdirectory(productions)
add_subdirectory(token)
add_subdirectory(parser)

message(STATUS ${SRC_LIST})
add_executable(Main ${SRC_LIST})
