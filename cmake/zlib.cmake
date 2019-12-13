#Add zlib library

# We first try to find zlib in the system
find_package(zlib QUIET)

# If not found, build from sources
if(NOT TARGET ZLIB::ZLIB)
	
	message(STATUS "Can't find zlib, building it from sources")
	
	set(ZLIB_SRC_PATH ${CMAKE_SOURCE_DIR}/3rdparty/zlib)
	set(ZLIB_BUILD_PATH ${CMAKE_BINARY_DIR}/3rdparty/zlib)
	
	file(MAKE_DIRECTORY ${ZLIB_BUILD_PATH})

	execute_process(
		COMMAND "cmake" "${ZLIB_SRC_PATH}" "-G" "${CMAKE_GENERATOR}" "-A" "${CMAKE_GENERATOR_PLATFORM}" "-DCMAKE_INSTALL_PREFIX=install" 
		WORKING_DIRECTORY ${ZLIB_BUILD_PATH})

	execute_process(COMMAND "cmake" "--build" "." "--target" "install" "--config" "Release" WORKING_DIRECTORY ${ZLIB_BUILD_PATH})

	# Find the freshly built library
	set(ZLIB_ROOT ${ZLIB_BUILD_PATH}/install)
	find_package(zlib QUIET)
endif()