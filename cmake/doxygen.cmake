find_package(Doxygen QUIET)
if (DOXYGEN_FOUND)
    set(DOXYGEN_PREDEFINED "PROTOCOL_VERSION=${PROTOCOL_VERSION}")

    if (BOTCRAFT_COMPRESSION)
        set(DOXYGEN_PREDEFINED "${DOXYGEN_PREDEFINED} USE_COMPRESSION=1")
    endif(BOTCRAFT_COMPRESSION)

    if (BOTCRAFT_ENCRYPTION)
        set(DOXYGEN_PREDEFINED "${DOXYGEN_PREDEFINED} USE_ENCRYPTION=1")
    endif(BOTCRAFT_ENCRYPTION)

    if (WIN32 AND BOTCRAFT_WINDOWS_BETTER_SLEEP)
        set(DOXYGEN_PREDEFINED "${DOXYGEN_PREDEFINED} BETTER_SLEEP=1")
    endif()

    if (BOTCRAFT_USE_OPENGL_GUI)
        set(DOXYGEN_PREDEFINED "${DOXYGEN_PREDEFINED} USE_GUI=1")
        if(BOTCRAFT_USE_IMGUI)
            set(DOXYGEN_PREDEFINED "${DOXYGEN_PREDEFINED} USE_IMGUI=1")
        endif(BOTCRAFT_USE_IMGUI)
    endif(BOTCRAFT_USE_OPENGL_GUI)

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doxygen/main.md.in ${CMAKE_CURRENT_BINARY_DIR}/doxygen/main.md)

    set(DOXYGEN_MAIN_PAGE ${CMAKE_CURRENT_BINARY_DIR}/doxygen/main.md)
    set(DOXYGEN_WIKI_FOLDER ${CMAKE_CURRENT_BINARY_DIR}/doxygen/wiki)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doxygen/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/doxygen/Doxyfile)

    add_custom_target(doc_doxygen
        COMMAND ${CMAKE_COMMAND} -E echo "Removing previous wiki files..."
        COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_CURRENT_BINARY_DIR}/doxygen/wiki
        COMMAND ${CMAKE_COMMAND} -E echo "Downloading latest version of repo wiki pages..."
        COMMAND git clone --depth 1 https://github.com/adepierre/Botcraft.wiki.git ${DOXYGEN_WIKI_FOLDER}
        COMMAND ${CMAKE_COMMAND} -E echo "Running doxygen..."
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxygen/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating documentation with Doxygen"
        VERBATIM
    )
else()
    message(WARNING "BOTCRAFT_BUILD_DOC set to ON, but Doxygen not found")
endif(DOXYGEN_FOUND)
