
add_subdirectory(productions)
add_subdirectory(token_actions)
add_subdirectory(attributes)
add_subdirectory(code_generation)

set(
        SRC_LIST
        "${SRC_LIST}"
        PARENT_SCOPE
)

set(
        INCLUDE_LST
        "${INCLUDE_LST}"
        "${CMAKE_CURRENT_SOURCE_DIR}/productions"
        "${CMAKE_CURRENT_SOURCE_DIR}/token_actions"
        "${CMAKE_CURRENT_SOURCE_DIR}/attributes"
        "${CMAKE_CURRENT_SOURCE_DIR}/code_generation"
        PARENT_SCOPE
)