cmake_minimum_required(VERSION 3.20)

project(basic_search LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

SET(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -Wall -Werror=format -Werror=format-truncation -Werror=return-type")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -Wall -Werror=format -Werror=format-truncation -Werror=return-type")

option(ENABLE_ASAN "enable build with asan" NO)
if(ENABLE_ASAN)
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
endif()

option(ENABLE_COV "enable build with cov" NO)
if(ENABLE_COV)
    add_compile_options(-fprofile-arcs -ftest-coverage)
    add_link_options(-fprofile-arcs -ftest-coverage)
endif()

# find_package(PkgConfig)
# pkg_check_modules(brpc REQUIRED IMPORTED_TARGET brpc)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_BINARY_DIR}/src)


add_subdirectory(src)





