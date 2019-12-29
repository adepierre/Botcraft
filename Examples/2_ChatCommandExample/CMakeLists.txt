project(2_ChatCommandExample)

set(SRC_FILES
${PROJECT_SOURCE_DIR}/src/ChatCommandClient.cpp
${PROJECT_SOURCE_DIR}/src/main.cpp
)
set(HDR_FILES 
${PROJECT_SOURCE_DIR}/include/ChatCommandClient.hpp
)


add_executable(2_ChatCommandExample ${HDR_FILES} ${SRC_FILES})
target_include_directories(2_ChatCommandExample PUBLIC include)
target_link_libraries(2_ChatCommandExample botcraft)

set_property(TARGET 2_ChatCommandExample PROPERTY CXX_STANDARD 11)
set_target_properties(2_ChatCommandExample PROPERTIES FOLDER Examples)
set_target_properties(2_ChatCommandExample PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(2_ChatCommandExample PROPERTIES RELWITHDEBINFO_POSTFIX "_rd")
if(MSVC)
    # To avoid having folder for each configuration when building with Visual
    set_target_properties(2_ChatCommandExample PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(2_ChatCommandExample PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(2_ChatCommandExample PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(2_ChatCommandExample PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/bin")
    
    set_property(TARGET 2_ChatCommandExample PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
else()
    set_target_properties(2_ChatCommandExample PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
endif(MSVC)

install(TARGETS 2_ChatCommandExample RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})