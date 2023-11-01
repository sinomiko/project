add_executable(seek_dispatch_bin
test_seek_task.cc
    )

set_target_properties(seek_dispatch_bin PROPERTIES
    OUTPUT_NAME seek_dispatch
    )

target_link_libraries(seek_dispatch_bin
    pthread
    )