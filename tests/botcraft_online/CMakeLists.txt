project(botcraft_online_tests)

set(HDR_FILES
    include/MinecraftServer.hpp
    include/TestManager.hpp
    include/Utils.hpp
)

set(SRC_FILES 
    src/main.cpp

    src/MinecraftServer.cpp
    src/TestManager.cpp

    src/tests/entities.cpp
    src/tests/physics.cpp
    src/tests/self-tests.cpp
    src/tests/world.cpp

    src/tests/tasks/base_tasks.cpp
)

add_executable(${PROJECT_NAME} ${HDR_FILES} ${SRC_FILES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2)
target_link_libraries(${PROJECT_NAME} PRIVATE botcraft)
target_link_libraries(${PROJECT_NAME} PRIVATE subprocess)
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
get_filename_component(BOTCRAFT_ROOT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../.." ABSOLUTE)
target_compile_definitions(${PROJECT_NAME} PRIVATE BASE_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/src/tests")
if(BOTCRAFT_COMPRESSION)
    target_compile_definitions(${PROJECT_NAME} PRIVATE USE_COMPRESSION=1)
endif(BOTCRAFT_COMPRESSION)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER Tests)

# To have a nice files structure in Visual Studio
if(MSVC)
    foreach(source IN LISTS HDR_FILES)
        get_filename_component(source_path_header "${source}" PATH)
        string(REPLACE "include" "Header Files" source_path_header "${source_path_header}")
        string(REPLACE "/" "\\" source_path_msvc "${source_path_header}")
        source_group("${source_path_msvc}" FILES "${source}")
    endforeach()
    
    foreach(source IN LISTS SRC_FILES)
        get_filename_component(source_path "${source}" PATH)
        string(REPLACE "src" "Source Files" source_path "${source_path}")
        string(REPLACE "/" "\\" source_path_msvc "${source_path}")
        source_group("${source_path_msvc}" FILES "${source}")
    endforeach()
endif()


# Output the test executable next to the examples and library files
if(MSVC)
    # To avoid having folder for each configuration when building with Visual
    set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BOTCRAFT_OUTPUT_DIR}/lib")
    set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BOTCRAFT_OUTPUT_DIR}/lib")
    set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${BOTCRAFT_OUTPUT_DIR}/lib")
    set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${BOTCRAFT_OUTPUT_DIR}/lib")

    set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${BOTCRAFT_OUTPUT_DIR}/bin")
else()
    set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${BOTCRAFT_OUTPUT_DIR}/lib")
endif(MSVC)

# Manual add_test instead of catch_discover_tests because otherwise each test is launched by a separate process
# i.e. a separate server instance. And we want everything to happen on the same server.
add_test(
  NAME ${PROJECT_NAME}
  COMMAND $<TARGET_FILE:${PROJECT_NAME}>
  WORKING_DIRECTORY "${BOTCRAFT_OUTPUT_DIR}/bin"
)

# Copy runtime files to bin output folder
if(NOT IS_DIRECTORY "${BOTCRAFT_OUTPUT_DIR}/bin/test_server_files/runtime")
    message(STATUS "Copying runtime online test files to bin folder...")
endif()
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/runtime" DESTINATION "${BOTCRAFT_OUTPUT_DIR}/bin/test_server_files")
