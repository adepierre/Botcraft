project(3_SimpleAFKExample)

set(SRC_FILES
${PROJECT_SOURCE_DIR}/src/main.cpp
)
set(HDR_FILES 
)


add_executable(3_SimpleAFKExample ${HDR_FILES} ${SRC_FILES})
target_link_libraries(3_SimpleAFKExample botcraft)

set_property(TARGET 3_SimpleAFKExample PROPERTY CXX_STANDARD 11)
set_target_properties(3_SimpleAFKExample PROPERTIES FOLDER Examples)
set_target_properties(3_SimpleAFKExample PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(3_SimpleAFKExample PROPERTIES RELWITHDEBINFO_POSTFIX "_rd")
if(MSVC)
    # To avoid having folder for each configuration when building with Visual
    set_target_properties(3_SimpleAFKExample PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(3_SimpleAFKExample PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(3_SimpleAFKExample PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(3_SimpleAFKExample PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/bin")
    
    set_property(TARGET 3_SimpleAFKExample PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
else()
    set_target_properties(3_SimpleAFKExample PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
endif(MSVC)

install(TARGETS 3_SimpleAFKExample RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})