cmake_minimum_required(VERSION 3.8)
project(crosssocket VERSION 0.3.0 LANGUAGES C DESCRIPTION "Cross-platfrom socket library for C")
add_library(crosssocket INTERFACE)

target_include_directories(crosssocket INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

if (WIN32)
    target_link_libraries(crosssocket wsock32 ws2_32)
endif ()

add_subdirectory(test)

#install(FILES crosssocket-config.cmake DESTINATION lib/cmake/crosssocket)
install(FILES include/crosssocket.h DESTINATION include)
enable_testing()
