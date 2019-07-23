add_library(picoJson INTERFACE IMPORTED)
set_property(TARGET picoJson PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/3rdparty/picoJson/include)