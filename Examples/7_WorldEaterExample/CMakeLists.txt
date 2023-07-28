project(7_WorldEaterExample)

set(${PROJECT_NAME}_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/include/WorldEaterSubTrees.hpp
    ${PROJECT_SOURCE_DIR}/include/WorldEaterTasks.hpp

    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/WorldEaterSubTrees.cpp
    ${PROJECT_SOURCE_DIR}/src/WorldEaterTasks.cpp
)
set(${PROJECT_NAME}_INCLUDE_FOLDERS
    ${PROJECT_SOURCE_DIR}/include
)

add_example("${${PROJECT_NAME}_INCLUDE_FOLDERS}" "${${PROJECT_NAME}_SOURCE_FILES}")
