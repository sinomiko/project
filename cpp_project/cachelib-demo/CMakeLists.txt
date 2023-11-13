cmake_minimum_required (VERSION 3.12)
project (cachelib-demo VERSION 0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message(STATUS "Update CXXFLAGS: ${CMAKE_CXX_FLAGS}")

add_executable(simple-cache-example main.cpp)
target_link_libraries(simple-cache-example 
    cachelib_allocator cachelib_shm cachelib_common cachelib_navy cachelib_datatype
    
    thrift-core
    thriftcpp2
    # thriftfrozen2
    # thriftmetadata
    thriftprotocol
    # thrifttype

    folly 
    glog

    fmt 
    boost_fiber boost_context  
    double-conversion 
    
    pthread 
    rt
    )
