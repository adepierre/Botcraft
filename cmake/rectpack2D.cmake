# Check if rectpack2d folder is empty and clone submodule if needed
file(GLOB RESULT "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/rectpack2d/src")
list(LENGTH RESULT RES_LEN)
if(RES_LEN EQUAL 0)
    message(STATUS "rectpack2D not found, cloning it...")
    execute_process(COMMAND git submodule update --init -- 3rdparty/rectpack2D WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

add_library(rectpack2D INTERFACE IMPORTED)
set_property(TARGET rectpack2D PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/rectpack2D/src")