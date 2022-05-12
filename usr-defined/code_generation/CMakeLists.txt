add_subdirectory(code_rules)

set(
        SRC_LIST
        "${SRC_LIST}"
        ${CMAKE_CURRENT_SOURCE_DIR}/codeGenerator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/C_rule_code.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/code_gen_productionInfo.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/code_gen_Context.cpp
        PARENT_SCOPE
)

set(
        INCLUDE_LST
        "${INCLUDE_LST}"
        "${CMAKE_CURRENT_SOURCE_DIR}/code_rules"
        PARENT_SCOPE
)