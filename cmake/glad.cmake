# Add glad library

# We first try to find glad in the system
if (NOT BOTCRAFT_FORCE_LOCAL_GLAD)
    find_package(glad QUIET)
endif()

# If not found, build from sources
if(NOT TARGET glad)
    set(GLAD_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glad/")
    set(GLAD_BUILD_PATH "${CMAKE_CURRENT_BINARY_DIR}/3rdparty/glad")

    file(GLOB RESULT "${GLAD_BUILD_PATH}/install")
    list(LENGTH RESULT RES_LEN)
    if(RES_LEN EQUAL 0)
        message(STATUS "Can't find glad, installing it locally...")

        file(MAKE_DIRECTORY "${GLAD_BUILD_PATH}")

        execute_process(
            COMMAND "${CMAKE_COMMAND}" "${GLAD_SRC_PATH}" "-G" "${CMAKE_GENERATOR}" "-A" "${CMAKE_GENERATOR_PLATFORM}" "-DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}" "-DCMAKE_BUILD_TYPE=Release" "-DCMAKE_INSTALL_PREFIX=install" "-DCMAKE_POSITION_INDEPENDENT_CODE=ON" 
            WORKING_DIRECTORY "${GLAD_BUILD_PATH}")

        execute_process(COMMAND "${CMAKE_COMMAND}" "--build" "." "--target" "install" "--parallel" "2" "--config" "Release" WORKING_DIRECTORY "${GLAD_BUILD_PATH}")
    endif()

    # Find the freshly built library
    find_package(glad QUIET PATHS "${GLAD_BUILD_PATH}/install")
endif()
