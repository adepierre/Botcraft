# Check if imgui folder is empty and clone submodule if needed
file(GLOB RESULT "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/imgui/misc")
list(LENGTH RESULT RES_LEN)
if(RES_LEN EQUAL 0)
    message(STATUS "Imgui not found, cloning it...")
    execute_process(COMMAND git submodule update --init -- 3rdparty/imgui WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

if(NOT TARGET imgui)

    set(IMGUI_SOURCES 
        3rdparty/imgui/imgui.cpp
        3rdparty/imgui/imgui_draw.cpp
        3rdparty/imgui/imgui_tables.cpp
        3rdparty/imgui/imgui_widgets.cpp
        3rdparty/imgui/backends/imgui_impl_glfw.cpp
        3rdparty/imgui/backends/imgui_impl_opengl3.cpp)

    set(IMGUI_HEADERS 
        3rdparty/imgui/imconfig.h
        3rdparty/imgui/imgui.h
        3rdparty/imgui/imgui_internal.h
        3rdparty/imgui/imstb_rectpack.h
        3rdparty/imgui/imstb_textedit.h
        3rdparty/imgui/imstb_truetype.h
        3rdparty/imgui/backends/imgui_impl_glfw.h
        3rdparty/imgui/backends/imgui_impl_opengl3.h)

    add_library(imgui STATIC ${IMGUI_HEADERS} ${IMGUI_SOURCES})
    set_property(TARGET imgui PROPERTY POSITION_INDEPENDENT_CODE ON)
    set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/imgui")
    target_include_directories(imgui PUBLIC "${IMGUI_DIR}")
    target_include_directories(imgui PUBLIC "${IMGUI_DIR}/backends")

    target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)
    target_link_libraries(imgui PRIVATE OpenGL::GL glfw glad)
    set_target_properties(imgui PROPERTIES FOLDER 3rdparty)
endif()
