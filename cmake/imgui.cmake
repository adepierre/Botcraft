# Check if imgui folder is empty and clone submodule if needed
file(GLOB RESULT "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/imgui/misc")
list(LENGTH RESULT RES_LEN)
if(RES_LEN EQUAL 0)
    message(STATUS "Imgui not found, cloning it...")
    execute_process(COMMAND git submodule update --init -- 3rdparty/imgui WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

# Check if imgui-node-editor folder is empty and clone submodule if needed
file(GLOB RESULT "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/imgui-node-editor/misc")
list(LENGTH RESULT RES_LEN)
if(RES_LEN EQUAL 0)
    message(STATUS "Imgui node editor not found, cloning it...")
    execute_process(COMMAND git submodule update --init -- 3rdparty/imgui-node-editor WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

if(NOT TARGET imgui)
    set(IMGUI_SOURCES
        3rdparty/imgui/imgui.cpp
        3rdparty/imgui/imgui_draw.cpp
        3rdparty/imgui/imgui_tables.cpp
        3rdparty/imgui/imgui_widgets.cpp
        3rdparty/imgui/backends/imgui_impl_glfw.cpp
        3rdparty/imgui/backends/imgui_impl_opengl3.cpp

        #Add Node-Editor extension
        3rdparty/imgui-node-editor/crude_json.cpp
        3rdparty/imgui-node-editor/crude_json.cpp
        3rdparty/imgui-node-editor/imgui_canvas.cpp
        3rdparty/imgui-node-editor/imgui_node_editor.cpp
        3rdparty/imgui-node-editor/imgui_node_editor_api.cpp
    )

    set(IMGUI_HEADERS
        3rdparty/imgui/imconfig.h
        3rdparty/imgui/imgui.h
        3rdparty/imgui/imgui_internal.h
        3rdparty/imgui/imstb_rectpack.h
        3rdparty/imgui/imstb_textedit.h
        3rdparty/imgui/imstb_truetype.h
        3rdparty/imgui/backends/imgui_impl_glfw.h
        3rdparty/imgui/backends/imgui_impl_opengl3.h

        #Add Node-Editor extension
        3rdparty/imgui-node-editor/crude_json.h
        3rdparty/imgui-node-editor/imgui_bezier_math.h
        3rdparty/imgui-node-editor/imgui_bezier_math.inl
        3rdparty/imgui-node-editor/imgui_canvas.h
        3rdparty/imgui-node-editor/imgui_extra_math.h
        3rdparty/imgui-node-editor/imgui_extra_math.inl
        3rdparty/imgui-node-editor/imgui_node_editor.h
        3rdparty/imgui-node-editor/imgui_node_editor_internal.h
        3rdparty/imgui-node-editor/imgui_node_editor_internal.inl
    )

    add_library(imgui STATIC ${IMGUI_HEADERS} ${IMGUI_SOURCES})
    set_property(TARGET imgui PROPERTY POSITION_INDEPENDENT_CODE ON)
    set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/imgui")
    target_include_directories(imgui PUBLIC "${IMGUI_DIR}")
    target_include_directories(imgui PUBLIC "${IMGUI_DIR}/backends")
    set(IMGUI_NODE_EDITOR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/imgui-node-editor")
    target_include_directories(imgui PUBLIC "${IMGUI_NODE_EDITOR_DIR}")

    target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)
    target_link_libraries(imgui PRIVATE OpenGL::GL glfw glad)
    set_target_properties(imgui PROPERTIES FOLDER 3rdparty)
    if(MSVC)
        set_target_properties(imgui PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded")
    endif()
endif()
