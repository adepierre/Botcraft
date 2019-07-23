add_library(stb_image INTERFACE IMPORTED)
set_property(TARGET stb_image PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/3rdparty/stb_image/include)