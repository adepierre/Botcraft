# Will get client.jar and server.jar urls for a given game version and save them in ${VERSION_CLIENT/SERVER_URL}
function(get_mc_version_urls game_version)
    if(NOT EXISTS "${CMAKE_BINARY_DIR}/mc_version_json_files/${game_version}.json")
        message(STATUS "${game_version}.json does not exist, retrieving it...")

        # Download global manifest file
        message(STATUS "Downloading Mojang's version_manifest_v2.json...")
        file(DOWNLOAD
            "https://piston-meta.mojang.com/mc/game/version_manifest_v2.json"    # URL
            "${CMAKE_BINARY_DIR}/mc_version_json_files/version_manifest_v2.json" # Path
            STATUS DOWNLOAD_STATUS                                               # Status code
        )

        # Separate the returned status code, and error message
        list(GET DOWNLOAD_STATUS 0 STATUS_CODE)
        list(GET DOWNLOAD_STATUS 1 ERROR_MESSAGE)

        if(${STATUS_CODE} EQUAL 0)
            message(STATUS "version_manifest_v2.json downloaded successfully. Extracting ${game_version} json urls...")
        else()
            # Exit CMake if the download failed, printing the error message.
            message(FATAL_ERROR "Error occurred during version_manifest_v2.json download: ${ERROR_MESSAGE}")
        endif()

        file(READ "${CMAKE_BINARY_DIR}/mc_version_json_files/version_manifest_v2.json" VERSION_MANIFEST_V2_CONTENT)

        # Get versions length
        string(JSON versions_array_length LENGTH ${VERSION_MANIFEST_V2_CONTENT} "versions")

        foreach(IDX RANGE ${versions_array_length})
            # Get the version of the current element
            string(JSON current_version GET ${VERSION_MANIFEST_V2_CONTENT} "versions" ${IDX} "id")

            # If it matches desired game_version, get version specific json URL
            if(current_version STREQUAL game_version)
                string(JSON version_json_url GET ${VERSION_MANIFEST_V2_CONTENT} "versions" ${IDX} "url")
                break()
            endif()
        endforeach()

        # Download version specific json file
        message(STATUS "Downloading Mojang's ${game_version}.json...")
        file(DOWNLOAD
            "${version_json_url}"                                            # URL
            "${CMAKE_BINARY_DIR}/mc_version_json_files/${game_version}.json" # Path
            STATUS DOWNLOAD_STATUS                                           # Status code
        )

        # Separate the returned status code, and error message
        list(GET DOWNLOAD_STATUS 0 STATUS_CODE)
        list(GET DOWNLOAD_STATUS 1 ERROR_MESSAGE)

        if(${STATUS_CODE} EQUAL 0)
            message(STATUS "${game_version}.json downloaded successfully. Extracting client and server urls...")
        else()
            # Exit CMake if the download failed, printing the error message.
            message(FATAL_ERROR "Error occurred during ${game_version}.json download: ${ERROR_MESSAGE}")
        endif()
    endif()

    # If we are here, ${game_version}.json exists, so get the URLs from it
    file(READ "${CMAKE_BINARY_DIR}/mc_version_json_files/${game_version}.json" GAME_VERSION_JSON_CONTENT)

    # Read client URL
    string(JSON VERSION_CLIENT_URL GET ${GAME_VERSION_JSON_CONTENT} "downloads" "client" "url")
    # Read server URL
    string(JSON VERSION_SERVER_URL GET ${GAME_VERSION_JSON_CONTENT} "downloads" "server" "url")

    set(VERSION_CLIENT_URL ${VERSION_CLIENT_URL} PARENT_SCOPE)
    set(VERSION_SERVER_URL ${VERSION_SERVER_URL} PARENT_SCOPE)
endfunction()

function(download_mc_server url path)
    if(NOT EXISTS ${path})
        message(STATUS "Downloading server.jar...")
        file(DOWNLOAD
            ${url}                   # URL
            ${path}                  # Path
            STATUS DOWNLOAD_STATUS   # Status code
            SHOW_PROGRESS
        )

        # Separate the returned status code, and error message
        list(GET DOWNLOAD_STATUS 0 STATUS_CODE)
        list(GET DOWNLOAD_STATUS 1 ERROR_MESSAGE)

        if(NOT ${STATUS_CODE} EQUAL 0)
            # Exit CMake if the download failed, printing the error message.
            message(FATAL_ERROR "Error occurred during server.jar download: ${ERROR_MESSAGE}")
        endif()
    endif()
endfunction()
