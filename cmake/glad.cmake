#Add glad library

# We first try to find glad in the system
find_package(glad QUIET)

# If not found, build from sources
if(NOT TARGET glad)
    message(STATUS "Can't find glad, building it from sources")

    set(GLAD_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glad")
    set(GLAD_BUILD_PATH "${CMAKE_CURRENT_BINARY_DIR}/3rdparty/glad")

    file(MAKE_DIRECTORY "${GLAD_BUILD_PATH}")

    execute_process(
        COMMAND "${CMAKE_COMMAND}" "${GLAD_SRC_PATH}" "-G" "${CMAKE_GENERATOR}" "-A" "${CMAKE_GENERATOR_PLATFORM}" "-DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}" "-DCMAKE_BUILD_TYPE=Release" "-DCMAKE_INSTALL_PREFIX=install" "-DCMAKE_POSITION_INDEPENDENT_CODE=ON" 
        WORKING_DIRECTORY "${GLAD_BUILD_PATH}")

    execute_process(COMMAND "${CMAKE_COMMAND}" "--build" "." "--target" "install" "--config" "Release" WORKING_DIRECTORY "${GLAD_BUILD_PATH}")

    # Find the freshly built library
    find_package(glad QUIET PATHS "${GLAD_BUILD_PATH}/install")
endif()
