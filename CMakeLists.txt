cmake_minimum_required(VERSION 3.0)
project(crosssocket DESCRIPTION "Cross-platfrom socket library for C")
add_library(crosssocket INTERFACE)

#set_target_properties(crosssocket PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(crosssocket INTERFACE include)

if (WIN32)
    target_link_libraries(crosssocket wsock32 ws2_32)
endif ()

add_subdirectory(test)

install(FILES include/crosssocket.h DESTINATION include)
install(FILES crosssocket-config.cmake DESTINATION lib/cmake/crosssocket)
install(TARGETS crosssocket
        RUNTIME DESTINATION lib
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include)
enable_testing()
