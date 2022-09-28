target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp
        ${CMAKE_CURRENT_LIST_DIR}/MBoundingBox.cpp
        ${CMAKE_CURRENT_LIST_DIR}/MDagModifier.cpp
        ${CMAKE_CURRENT_LIST_DIR}/MDagPath.cpp
        ${CMAKE_CURRENT_LIST_DIR}/MDGModifier.cpp
        ${CMAKE_CURRENT_LIST_DIR}/MObject.cpp
        ${CMAKE_CURRENT_LIST_DIR}/MPlug.cpp
        ${CMAKE_CURRENT_LIST_DIR}/MSelectionList.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Types.cpp
)

add_subdirectory(fn)
add_subdirectory(math)
