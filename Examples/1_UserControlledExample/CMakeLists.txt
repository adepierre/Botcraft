project(1_UserControlledExample)

set(SRC_FILES
${PROJECT_SOURCE_DIR}/src/UserControlledClient.cpp
${PROJECT_SOURCE_DIR}/src/main.cpp
)
set(HDR_FILES 
${PROJECT_SOURCE_DIR}/include/UserControlledClient.hpp
)


add_executable(1_UserControlledExample ${HDR_FILES} ${SRC_FILES})
target_include_directories(1_UserControlledExample PUBLIC include)
target_link_libraries(1_UserControlledExample botcraft)
set_property(TARGET 1_UserControlledExample PROPERTY CXX_STANDARD 11)
set_target_properties(1_UserControlledExample PROPERTIES FOLDER Examples)
set_target_properties(1_UserControlledExample PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(1_UserControlledExample PROPERTIES RELWITHDEBINFO_POSTFIX "_rd")
if(MSVC)
    # To avoid having folder for each configuration when building with Visual
    set_target_properties(1_UserControlledExample PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(1_UserControlledExample PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(1_UserControlledExample PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(1_UserControlledExample PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/bin")
    
    set_property(TARGET 1_UserControlledExample PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
else()
    set_target_properties(1_UserControlledExample PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
endif(MSVC)

install(TARGETS 1_UserControlledExample RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})