cmake_minimum_required(VERSION 3.20)
project(problem_set LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

# add_executable(problem_set Frame.cpp QuickSort.cpp TPC.cpp Solution.h TestCase.h MallocTest.h)

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
# pkg_check_modules(grpc REQUIRED IMPORTED_TARGET grpc)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_BINARY_DIR}/src)
add_subdirectory(src)
# include(CTest)
# add_subdirectory(tests)
include(GNUInstallDirs)
install(TARGETS
    problem_set_bin
)
install(DIRECTORY
    scripts
    DESTINATION "/home/work/tools/"
    USE_SOURCE_PERMISSIONS
    DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE
    FILE_PERMISSIONS  OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE )

#set(CPACK_SET_DESTDIR ON)
if(NOT CPACK_PACKAGE_NAME)
    set(CPACK_PACKAGE_NAME "problem_set")
endif()
if(NOT CPACK_PACKAGE_MAINTAINER)
    set(CPACK_PACKAGE_MAINTAINER "miko.song")
endif()
if(NOT CPACK_PACKAGE_VERSION)
    set(CPACK_PACKAGE_VERSION "0.0.1")
endif()
if(NOT CPACK_RPM_PACKAGE_RELEASE)
    set(CPACK_RPM_PACKAGE_RELEASE 1)
endif()
set(CPACK_SET_DESTDIR OFF)
set(CPACK_RPM_PACKAGE_RELOCATABLE ON)
set(CPACK_PACKAGING_INSTALL_PREFIX "/usr")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "algo and test C++")
set(CPACK_PACKAGE_VENDOR "Miko's Project")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "1")
# set(CPACK_RPM_PACKAGE_GROUP "unknown")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://sinomiko.github.io")
set(CPACK_RPM_PACKAGE_URL "https://sinomiko.github.io")
set(CPACK_RPM_PACKAGE_DESCRIPTION "algo and test C++")
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_EPOCH 1)
set(CPACK_RPM_PACKAGE_AUTOREQ 0)
set(CPACK_RPM_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_RPM_PACKAGE_RELEASE}.el8.${CMAKE_SYSTEM_PROCESSOR}.rpm")
# set(CPACK_RPM_PACKAGE_REQUIRES "libsfs >= 0.0.1-35, libtensorflow >= 1.15.5-11.el8, libtensorflow < 1.16.0")
# set(CPACK_RPM_PACKAGE_REQUIRES_PRE "abseil")

set(CPACK_RPM_PACKAGE_DEBUG 1)
set(CPACK_RPM_DEBUGINFO_PACKAGE ON)
set(CPACK_RPM_DEBUGINFO_FILE_NAME "${CPACK_PACKAGE_NAME}-debuginfo-${CPACK_PACKAGE_VERSION}-${CPACK_RPM_PACKAGE_RELEASE}.el8.${CMAKE_SYSTEM_PROCESSOR}.rpm")
include(CPack)

