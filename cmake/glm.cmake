# Check if glm folder is empty and clone submodule if needed
file(GLOB RESULT ${CMAKE_SOURCE_DIR}/3rdparty/glm/glm)
list(LENGTH RESULT RES_LEN)
if(RES_LEN EQUAL 0)
    message(STATUS "glm not found, cloning it...")
    execute_process(COMMAND git submodule update --init -- 3rdparty/glm WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif()

add_library(glm INTERFACE IMPORTED)
set_property(TARGET glm PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/3rdparty/glm)