add_executable(index_load_bin
test_index_load.cc
    )

set_target_properties(index_load_bin PROPERTIES
    OUTPUT_NAME index_load
    )

target_link_libraries(index_load_bin
    pthread
    gflags
    )