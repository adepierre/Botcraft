project(4_MapCreatorExample)

set(${PROJECT_NAME}_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/include/MapCreationTasks.hpp
    ${PROJECT_SOURCE_DIR}/include/CustomBehaviourTree.hpp

    ${PROJECT_SOURCE_DIR}/src/MapCreationTasks.cpp
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)
set(${PROJECT_NAME}_INCLUDE_FOLDERS
    ${PROJECT_SOURCE_DIR}/include
)

add_example("${${PROJECT_NAME}_INCLUDE_FOLDERS}" "${${PROJECT_NAME}_SOURCE_FILES}")
