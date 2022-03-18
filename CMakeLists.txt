cmake_minimum_required(VERSION 2.4)
project(compiler)

macro(DEBUG)
endmacro()

find_package(Java REQUIRED)

include(UseJava)

add_subdirectory(constructor)

add_jar(Constructor
        ${JAVA_JAR_LIST}
        ENTRY_POINT Constructor
        OUTPUT_NAME Constructor
        OUTPUT_DIR "${PROJECT_BINARY_DIR}"
        )

add_executable(CFG_rules productions/Productions.cc productions/production_printer.cpp)

add_custom_command(
        OUTPUT token_data.cpp CFG_data.cpp
        COMMAND CFG_rules
        COMMAND java -jar ${PROJECT_BINARY_DIR}/Constructor.jar
        ${PROJECT_SOURCE_DIR}/constructor/token_list.txt
        ${PROJECT_BINARY_DIR}/cfg_rules.txt
        ${PROJECT_SOURCE_DIR}/constructor/scanner_part1.txt
        ${PROJECT_SOURCE_DIR}/constructor/scanner_part2.txt
        DEPEND CFG_rules
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

add_dependencies(Main Constructor)
