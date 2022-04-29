cmake_minimum_required(VERSION 3.1)
project(compiler)

set(CMAKE_CXX_STANDARD 20)
macro(DEBUG)
endmacro()

find_package(Java REQUIRED)

include(UseJava)

LIST(APPEND SRC_LIST main.cpp CTokenTable.cpp CFG_data.cpp)
LIST(APPEND INCLUDE_LST include token parser semantic usr-defined)

add_subdirectory(constructor)
add_subdirectory(token)
add_subdirectory(parser)
add_subdirectory(usr-defined)
add_subdirectory(semantic)

add_jar(Constructor
        ${JAVA_JAR_LIST}
        ENTRY_POINT Constructor
        OUTPUT_NAME Constructor
        OUTPUT_DIR "${PROJECT_BINARY_DIR}"
        )

# final build
include_directories(
        ${INCLUDE_LST}
)

add_executable(TokenTableWrapper token/TokenTableWrapper.cpp)
add_executable(CFG_Generator usr-defined/productions/CProductions.cc usr-defined/productions/C_production_printer.cpp)
add_executable(TokenListGenerator usr-defined/token_actions/CTokenActions.cpp usr-defined/token_actions/CTokenWriter.cpp)

add_custom_command(
        OUTPUT cfg_rules.txt
        COMMAND CFG_Generator
        DEPENDS CFG_Generator
)

add_custom_command(
        OUTPUT TokenList
        COMMAND TokenListGenerator > TokenList
        DEPENDS TokenListGenerator
)

add_custom_command(
        OUTPUT CFG_data.cpp token_data
        COMMAND java -jar Constructor.jar TokenList cfg_rules.txt
        DEPENDS cfg_rules.txt TokenList Constructor.jar
)

add_custom_command(
        OUTPUT CTokenTable.cpp
        COMMAND TokenTableWrapper CTokenTable <token_data >CTokenTable.cpp
        DEPENDS TokenTableWrapper token_data
)

message(STATUS ${SRC_LIST})
add_executable(Main ${SRC_LIST})
target_compile_definitions(Main PUBLIC DEBUG)

add_executable(TEST test.cpp)

target_compile_definitions(TEST PUBLIC DEBUG)