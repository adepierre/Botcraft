project(2_ChatCommandExample)

set(${PROJECT_NAME}_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/include/ChatCommandClient.hpp

    ${PROJECT_SOURCE_DIR}/src/ChatCommandClient.cpp
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)
set(${PROJECT_NAME}_INCLUDE_FOLDERS
    ${PROJECT_SOURCE_DIR}/include
)

add_example("${${PROJECT_NAME}_INCLUDE_FOLDERS}" "${${PROJECT_NAME}_SOURCE_FILES}")
