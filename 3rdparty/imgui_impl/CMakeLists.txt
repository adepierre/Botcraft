set(IMGUI_IMPL_SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/imgui_impl_glfw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/imgui_impl_opengl3.cpp
)

add_library(imgui_impl STATIC 
    ${IMGUI_IMPL_SRC}
)

target_compile_definitions(imgui_impl
    PUBLIC
        IMGUI_IMPL_OPENGL_LOADER_GLAD
)

target_include_directories(imgui_impl
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        CONAN_PKG::imgui
)

target_link_libraries(imgui_impl
    PRIVATE
        CONAN_PKG::imgui
        CONAN_PKG::glfw
        CONAN_PKG::glad
)