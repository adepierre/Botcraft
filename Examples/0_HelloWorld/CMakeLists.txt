project(0_HelloWorld)

set(SRC_FILES
${PROJECT_SOURCE_DIR}/src/main.cpp
)
set(HDR_FILES 
)

add_executable(0_HelloWorld ${HDR_FILES} ${SRC_FILES})
target_include_directories(0_HelloWorld PUBLIC include)
target_link_libraries(0_HelloWorld botcraft)
set_property(TARGET 0_HelloWorld PROPERTY CXX_STANDARD 11)
set_target_properties(0_HelloWorld PROPERTIES FOLDER Examples)
set_target_properties(0_HelloWorld PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(0_HelloWorld PROPERTIES RELWITHDEBINFO_POSTFIX "_rd")
if(MSVC)
    # To avoid having folder for each configuration when building with Visual
    set_target_properties(0_HelloWorld PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(0_HelloWorld PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(0_HelloWorld PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(0_HelloWorld PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/bin")
    
    set_property(TARGET 0_HelloWorld PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
else()
    set_target_properties(0_HelloWorld PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
endif(MSVC)

install(TARGETS 0_HelloWorld RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})