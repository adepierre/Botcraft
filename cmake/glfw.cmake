#Add GLFW library

# We first try to find glfw in the system
find_package(glfw3 3.3 QUIET)

# If not found, build from sources
if(NOT TARGET glfw)
	
	message(STATUS "Can't find GLFW, cloning and building it from sources")
	
    file(GLOB RESULT "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glfw/include")
    list(LENGTH RESULT RES_LEN)
    message(STATUS ${RES_LEN})
    if(RES_LEN EQUAL 0)
        message(STATUS "Glfw not found, cloning it...")
        execute_process(COMMAND git submodule update --init -- 3rdparty/glfw WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
    endif()
    
	set(GLFW_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glfw")
	set(GLFW_BUILD_PATH "${CMAKE_CURRENT_BINARY_DIR}/3rdparty/glfw")
	
	file(MAKE_DIRECTORY "${GLFW_BUILD_PATH}")
	execute_process(
		COMMAND "cmake" "${GLFW_SRC_PATH}" "-G" "${CMAKE_GENERATOR}" "-A" "${CMAKE_GENERATOR_PLATFORM}" "-DGLFW_BUILD_EXAMPLES=OFF" "-DGLFW_BUILD_TESTS=OFF" "-DGLFW_BUILD_DOCS=OFF" "-DGLFW_INSTALL=ON" "-DCMAKE_INSTALL_PREFIX=install" 
		WORKING_DIRECTORY "${GLFW_BUILD_PATH}")

	execute_process(COMMAND "cmake" "--build" "." "--target" "install" "--config" "Release" WORKING_DIRECTORY "${GLFW_BUILD_PATH}")

	# Find the freshly built library
	find_package(glfw3 3.3 REQUIRED PATHS "${GLFW_BUILD_PATH}/install/lib/cmake/glfw3")
endif()