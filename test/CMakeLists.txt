add_executable(xs_test xs_test.c)

target_link_libraries(xs_test crosssocket)
target_link_libraries(xs_test ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(xs_test PRIVATE crosssocket)

add_test(NAME xs_server_test COMMAND xs_test server)
enable_testing()
