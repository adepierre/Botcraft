project(6_DispenserFarmExample)

set(${PROJECT_NAME}_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/include/DispenserFarmTasks.hpp

    ${PROJECT_SOURCE_DIR}/src/DispenserFarmTasks.cpp
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)
set(${PROJECT_NAME}_INCLUDE_FOLDERS
    ${PROJECT_SOURCE_DIR}/include
)

add_example("${${PROJECT_NAME}_INCLUDE_FOLDERS}" "${${PROJECT_NAME}_SOURCE_FILES}")
