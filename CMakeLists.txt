cmake_minimum_required(VERSION 3.0)
project(crosssocket VERSION 0.1.0 DESCRIPTION "Cross-platfrom socket library for C")
add_library(crosssocket include/crosssocket.h src/crosssocket.c)
if (WIN32)
    target_link_libraries(crosssocket wsock32 ws2_32)
endif ()

set_target_properties(crosssocket PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(crosssocket PRIVATE include)

add_subdirectory(test)

install(FILES include/crosssocket.h DESTINATION include)
install(FILES crosssocket-config.cmake DESTINATION lib/cmake/crosssocket)
install(TARGETS crosssocket
        RUNTIME DESTINATION lib
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include)
enable_testing()
