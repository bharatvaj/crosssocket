cmake_minimum_required(VERSION 3.0)
project(crosssocket VERSION 0.3.0 DESCRIPTION "Cross-platfrom socket library for C")
find_package(clog)
add_library(crosssocket src/crosssocket.c include/crosssocket.h)
if (WIN32)
    target_link_libraries(crosssocket wsock32 ws2_32)
endif ()

set_target_properties(crosssocket PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(crosssocket PUBLIC include)
target_include_directories(crosssocket PUBLIC ${CLOG_INCLUDE_DIR})
target_link_libraries(crosssocket ${CLOG_LIBS})

#TODO
#add_subdirectory(test)

install(FILES include/crosssocket.h DESTINATION include)
install(FILES crosssocket-config.cmake DESTINATION lib/cmake/crosssocket)
install(TARGETS crosssocket
        RUNTIME DESTINATION lib
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include)
enable_testing()