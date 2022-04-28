
add_subdirectory(productions)
add_subdirectory(token_actions)

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
        PARENT_SCOPE
)