add_library(asio INTERFACE IMPORTED)
set_property(TARGET asio PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/3rdparty/asio/asio/include)