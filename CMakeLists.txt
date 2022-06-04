cmake_minimum_required(VERSION 3.1)
project(compiler)

set(CMAKE_CXX_STANDARD 17)

#message("start configure")
#set(GRAMMAR_SYNC ON)

if(GRAMMAR_SYNC)
    message("GRAMMAR_SYNC has opened")
endif()

if(NOT DEFINED ENV{LLVM_DIR})
#     message("llvm dir not found")
#    set(ENV{LLVM_DIR} /lib/llvm-14/cmake)
endif()

find_package(Java REQUIRED)

include(UseJava)

find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

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

if(EXISTS ${PROJECT_BINARY_DIR}/CFG_data.cpp AND EXISTS ${PROJECT_BINARY_DIR}/CTokenTable.cpp)
    set(HAS_BUILT ON)
    message("CFG and Token data found")
    LIST(APPEND SRC_LIST ${PROJECT_BINARY_DIR}/CFG_data.cpp ${PROJECT_BINARY_DIR}/CTokenTable.cpp)
else()
    set(HAS_BUILT OFF)
    message("CFG and Token data not found")
endif()


if(GRAMMAR_SYNC OR NOT HAS_BUILT)
    message("Need to build the CFG")
    add_executable(TokenTableWrapper token/TokenTableWrapper.cpp)
    add_executable(
            CFG_Generator
            usr-defined/productions/CProductions.cc
            usr-defined/productions/C_production_printer.cpp
            semantic/ProductionInfo.cpp
    )
    add_executable(
            TokenListGenerator
            usr-defined/token_actions/CTokenActions.cpp
            usr-defined/token_actions/CTokenWriter.cpp
            usr-defined/productions/default_production.cpp
            semantic/ProductionInfo.cpp
    )

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

    LIST(APPEND SRC_LIST CTokenTable.cpp CFG_data.cpp)

endif()

LIST(APPEND SRC_LIST main.cpp)
add_executable(Main ${SRC_LIST})
target_compile_definitions(Main PUBLIC DEBUG)

add_executable(TEST test.cpp)
target_compile_definitions(TEST PUBLIC DEBUG)

llvm_map_components_to_libnames(llvm_libs core orcjit native)
target_link_libraries(TEST ${llvm_libs})
target_link_libraries(Main ${llvm_libs})

add_executable(CONSTRUCTOR usr-defined/C_rule_attr_initializer.cpp)