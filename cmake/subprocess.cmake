add_library(subprocess INTERFACE IMPORTED)
set_property(TARGET subprocess PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/subprocess/include")
