
add_subdirectory(symbols)
add_subdirectory(attribute_rules)

set(
        SRC_LIST
        "${SRC_LIST}"
        "${CMAKE_CURRENT_SOURCE_DIR}/C_rule_attr.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/CSymbolTable.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/C_type.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/CNameSpace.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/C_constant.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/AttrContext.cpp"
        PARENT_SCOPE
)

set(
        INCLUDE_LST
        "${INCLUDE_LST}"
        "${CMAKE_CURRENT_SOURCE_DIR}/symbols"
        "${CMAKE_CURRENT_SOURCE_DIR}/attribute_rules"
        PARENT_SCOPE
)