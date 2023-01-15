project(5_MobHitterExample)

set(HDR_FILES 
${PROJECT_SOURCE_DIR}/include/MobHitterTasks.hpp
)

set(SRC_FILES
${PROJECT_SOURCE_DIR}/src/MobHitterTasks.cpp
${PROJECT_SOURCE_DIR}/src/main.cpp
)


add_executable(${PROJECT_NAME} ${HDR_FILES} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} botcraft)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER Examples)
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(${PROJECT_NAME} PROPERTIES RELWITHDEBINFO_POSTFIX "_rd")
if(MSVC)
    # To avoid having folder for each configuration when building with Visual
    set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${BOTCRAFT_OUTPUT_DIR}/bin")
    set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${BOTCRAFT_OUTPUT_DIR}/bin")
    
    set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${BOTCRAFT_OUTPUT_DIR}/bin")
else()
    set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${BOTCRAFT_OUTPUT_DIR}/bin")
endif(MSVC)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})