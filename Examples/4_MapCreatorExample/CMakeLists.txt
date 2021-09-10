project(4_MapCreatorExample)

set(SRC_FILES
${PROJECT_SOURCE_DIR}/src/MapCreatorBot.cpp
${PROJECT_SOURCE_DIR}/src/main.cpp
)
set(HDR_FILES 
${PROJECT_SOURCE_DIR}/include/MapCreatorBot.hpp
)


add_executable(4_MapCreatorExample ${HDR_FILES} ${SRC_FILES})
target_include_directories(4_MapCreatorExample PUBLIC include)
target_link_libraries(4_MapCreatorExample botcraft)

set_property(TARGET 4_MapCreatorExample PROPERTY CXX_STANDARD 17)
set_target_properties(4_MapCreatorExample PROPERTIES FOLDER Examples)
set_target_properties(4_MapCreatorExample PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(4_MapCreatorExample PROPERTIES RELWITHDEBINFO_POSTFIX "_rd")
if(MSVC)
    # To avoid having folder for each configuration when building with Visual
    set_target_properties(4_MapCreatorExample PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(4_MapCreatorExample PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(4_MapCreatorExample PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(4_MapCreatorExample PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/bin")
    
    set_property(TARGET 4_MapCreatorExample PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
else()
    set_target_properties(4_MapCreatorExample PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
endif(MSVC)

install(TARGETS 4_MapCreatorExample RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})