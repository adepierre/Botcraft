# Check if the minecraft assets folder already exists for the current version
# If not, download the client and extract the assets
if(BOTCRAFT_DONWLOAD_MC_ASSETS AND NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft")
    message(STATUS "Downloading assets for version " ${GAME_VERSION} " from " ${VERSION_CLIENTURL} "...")
    file(DOWNLOAD "${VERSION_CLIENTURL}" "${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/client.jar")
    message(STATUS "Extracting assets...")
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/temp/")
    execute_process(COMMAND "cmake" "-E" "tar" "xfz" "${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/client.jar" WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/temp/")
    file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/temp/assets/minecraft/" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/")
    message(STATUS "Removing temp folder")
    file(REMOVE_RECURSE "${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/temp")
endif()

# If assets folder doesn't exist, create it and copy all relevant files (custom and minecraft) to it
if(NOT EXISTS "${BOTCRAFT_OUTPUT_DIR}/bin/Assets/${GAME_VERSION}")
    message(STATUS "Asset folder not found, creating it...")
    # Create base assets folder for given version
    file(MAKE_DIRECTORY "${BOTCRAFT_OUTPUT_DIR}/bin/Assets/${GAME_VERSION}")
endif()


# Copying custom assets
if(NOT EXISTS "${BOTCRAFT_OUTPUT_DIR}/bin/Assets/${GAME_VERSION}/custom/")
    message(STATUS "Copying custom assets...")
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/custom/")
        file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/custom/" DESTINATION "${BOTCRAFT_OUTPUT_DIR}/bin/Assets/${GAME_VERSION}/custom/")
    endif()

    file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/previous_custom_files.txt" previous_custom_files)
    foreach(previous_file IN LISTS previous_custom_files)
        string(REGEX MATCH "^[^\\]+" file_version "${previous_file}")
        file(RELATIVE_PATH relative_file_path "${CMAKE_CURRENT_SOURCE_DIR}/Assets/${file_version}" "${CMAKE_CURRENT_SOURCE_DIR}/Assets/${previous_file}")
        get_filename_component(relative_file_path "${relative_file_path}" DIRECTORY)
        file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Assets/${previous_file}" DESTINATION "${BOTCRAFT_OUTPUT_DIR}/bin/Assets/${GAME_VERSION}/${relative_file_path}")
    endforeach()
endif()

# Copying Minecraft assets
if (BOTCRAFT_DONWLOAD_MC_ASSETS)
    # Blockstates
    if(NOT EXISTS "${BOTCRAFT_OUTPUT_DIR}/bin/Assets/${GAME_VERSION}/minecraft/blockstates")
        message(STATUS "Copying minecraft blockstates...")
        file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/blockstates" DESTINATION "${BOTCRAFT_OUTPUT_DIR}/bin/Assets/${GAME_VERSION}/minecraft/")
    endif()

    # Block models
    if(NOT EXISTS "${BOTCRAFT_OUTPUT_DIR}/bin/Assets/${GAME_VERSION}/minecraft/models/block")
        message(STATUS "Copying minecraft block models...")
        file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/models/block" DESTINATION "${BOTCRAFT_OUTPUT_DIR}/bin/Assets/${GAME_VERSION}/minecraft/models")
    endif()

    # Textures
    if(BOTCRAFT_USE_OPENGL_GUI)
        # Blocks
        if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/textures/blocks" AND NOT EXISTS "${BOTCRAFT_OUTPUT_DIR}/bin/Assets/${GAME_VERSION}/minecraft/textures/blocks")
            message(STATUS "Copying minecraft block textures...")
            file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/textures/blocks" DESTINATION "${BOTCRAFT_OUTPUT_DIR}/bin/Assets/${GAME_VERSION}/minecraft/textures")
        elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/textures/block" AND NOT EXISTS "${BOTCRAFT_OUTPUT_DIR}/bin/Assets/${GAME_VERSION}/minecraft/textures/block")
            message(STATUS "Copying minecraft block textures...")
            file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/textures/block" DESTINATION "${BOTCRAFT_OUTPUT_DIR}/bin/Assets/${GAME_VERSION}/minecraft/textures")
        endif()

        # Entities
        if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/textures/entity" AND NOT EXISTS "${BOTCRAFT_OUTPUT_DIR}/bin/Assets/${GAME_VERSION}/minecraft/textures/entity")
            message(STATUS "Copying minecraft entity textures...")
            file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Assets/${GAME_VERSION}/minecraft/textures/entity" DESTINATION "${BOTCRAFT_OUTPUT_DIR}/bin/Assets/${GAME_VERSION}/minecraft/textures")
        endif()

    endif()
endif(BOTCRAFT_DONWLOAD_MC_ASSETS)
    
    
    
    

set(ASSET_DIR ./Assets/${GAME_VERSION})
