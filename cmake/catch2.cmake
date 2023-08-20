# Add Catch2 library

# We first try to find Catch2 in the system
if(NOT BOTCRAFT_FORCE_LOCAL_CATCH)
    find_package(Catch2 3 QUIET)
endif()

# If not found, build from sources
if(NOT TARGET Catch2::Catch2WithMain)
    set(CATCH_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/catch2/")
    set(CATCH_BUILD_PATH "${CMAKE_CURRENT_BINARY_DIR}/3rdparty/catch2")

    file(GLOB RESULT "${CATCH_BUILD_PATH}/install")
    list(LENGTH RESULT RES_LEN)
    if(RES_LEN EQUAL 0)
        message(STATUS "Can't find Catch2, installing it locally...")

        file(GLOB RESULT "${CATCH_SRC_PATH}")
        list(LENGTH RESULT RES_LEN)
        if(RES_LEN EQUAL 0)
            execute_process(COMMAND git submodule update --init -- 3rdparty/catch2 WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
        endif()

        file(MAKE_DIRECTORY "${CATCH_BUILD_PATH}")

        execute_process(
            COMMAND "${CMAKE_COMMAND}" "${CATCH_SRC_PATH}" "-G" "${CMAKE_GENERATOR}" "-A" "${CMAKE_GENERATOR_PLATFORM}" "-DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}" "-DCMAKE_BUILD_TYPE=Release" "-DCATCH_INSTALL_DOCS=OFF" "-DCMAKE_INSTALL_PREFIX=install" 
            WORKING_DIRECTORY "${CATCH_BUILD_PATH}")

        execute_process(COMMAND "${CMAKE_COMMAND}" "--build" "." "--target" "install" "--parallel" "2" "--config" "Release" WORKING_DIRECTORY "${CATCH_BUILD_PATH}")
    endif()

    # Find the freshly built library
    find_package(Catch2 3 REQUIRED PATHS "${CATCH_BUILD_PATH}/install/${CMAKE_INSTALL_LIBDIR}/cmake/Catch2")
    include("${CATCH_BUILD_PATH}/install/${CMAKE_INSTALL_LIBDIR}/cmake/Catch2/Catch.cmake")
else()
    include("${Catch2_DIR}/Catch.cmake")
endif()
