cmake_minimum_required(VERSION 3.1)

project(glad C)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(GLAD_SOURCES 
${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c)

set(GLAD_HEADERS 
${CMAKE_CURRENT_SOURCE_DIR}/include/glad/glad.h
${CMAKE_CURRENT_SOURCE_DIR}/include/KHR/khrplatform.h)
                 
add_library(glad STATIC ${GLAD_HEADERS} ${GLAD_SOURCES})
target_include_directories(glad PUBLIC
						   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
						   $<INSTALL_INTERFACE:include>)

install(DIRECTORY include DESTINATION ".")
install(TARGETS glad
		EXPORT glad-targets
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib)
		
install(EXPORT glad-targets
		DESTINATION lib/cmake/glad)
include(CMakePackageConfigHelpers)
configure_package_config_file(
	"cmake/gladConfig.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/gladConfig.cmake"
	INSTALL_DESTINATION "lib/cmake/glad"
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/gladConfig.cmake" DESTINATION "lib/cmake/glad")