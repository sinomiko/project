# find_library(PkgConfig)

add_executable(problem_set_bin
    # TestCase.cpp
    Frame.cpp
)

set_target_properties(problem_set_bin PROPERTIES
    OUTPUT_NAME problem_set
)
# target_link_libraries(problem_set_bin
#     PRIVATE
#     leetcode
# )