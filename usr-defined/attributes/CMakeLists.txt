
add_subdirectory(symbols)

set(
        SRC_LIST
        "${SRC_LIST}"
        "${CMAKE_CURRENT_SOURCE_DIR}/C_rule_attr.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/CSymbolTable.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/C_type.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/CNameSpace.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/C_constant.cpp"
        PARENT_SCOPE
)

set(
        INCLUDE_LST
        "${INCLUDE_LST}"
        "${CMAKE_CURRENT_SOURCE_DIR}/symbols"
        PARENT_SCOPE
)