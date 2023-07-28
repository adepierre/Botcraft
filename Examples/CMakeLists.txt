# Define a macro that can be reused to quickly setup an Example project
# without all the boilerplate code
macro(add_example include_folders source_files)
    add_executable(${PROJECT_NAME} ${source_files})
    target_include_directories(${PROJECT_NAME} PUBLIC ${include_folders})
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
endmacro()

add_subdirectory(0_HelloWorld)
add_subdirectory(1_UserControlledExample)
add_subdirectory(2_ChatCommandExample)
add_subdirectory(3_SimpleAFKExample)
add_subdirectory(4_MapCreatorExample)
add_subdirectory(5_MobHitterExample)
if (PROTOCOL_VERSION STRGREATER "470") # 1.14+
    add_subdirectory(6_DispenserFarmExample)
endif()
add_subdirectory(7_WorldEaterExample)
