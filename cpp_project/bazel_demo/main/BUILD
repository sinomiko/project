cc_library(
    name = "actv",
    srcs = ["activations.c"],
    hdrs = ["activations.h"],
)


cc_binary(
    name = "actv-testbed",
    srcs = ["testbed.c"],
    deps = [
        ":actv",
        "//lib:random",
        "//lib:timer"
    ],
)
