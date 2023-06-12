project(1_UserControlledExample)

set(${PROJECT_NAME}_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/include/UserControlledClient.hpp

    ${PROJECT_SOURCE_DIR}/src/UserControlledClient.cpp
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)
set(${PROJECT_NAME}_INCLUDE_FOLDERS
    ${PROJECT_SOURCE_DIR}/include
)

add_example("${${PROJECT_NAME}_INCLUDE_FOLDERS}" "${${PROJECT_NAME}_SOURCE_FILES}")
