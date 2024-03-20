package(default_visibility = ["//visibility:public"])

load("@brpc//:bazel/brpc.bzl", "brpc_proto_library")


cc_library(
    name = 'lbs_lib',
    hdrs = glob([
        "lbs_brpc_impl.h",
    ]),
    srcs = glob([
        "lbs_brpc_impl.cpp",
    ],
    exclude = [
    ]),
    copts = [
    ],
    linkopts = [
    ],
    deps = [
        "@brpc//:brpc",
        "//src/local_utils:local_utils",
        "@shareit_lbs_sdk//:shareit_lbs_sdk",
        "@ads_util//timer:timer_util",
        "@shareit_ma_proto//lbs:lbs_proto",
    ],
    alwayslink = 1,
)



cc_binary(
    name = "lbs_brpc",
    srcs = glob([
        "main.cpp",
    ]),
    copts = [

    ],
    linkopts = [

    ],
    deps = [
        ":lbs_lib",
        "@com_github_gflags_gflags//:gflags",
        "@brpc//:brpc",
        "@ads_util//string:string_util",
        "@ads_util//cpu_profiler:cpu_profiler",
        "@ads_util//runtime_info:runtime_util",
        "//src/local_utils:local_utils",
        "@shareit_lbs_sdk//:shareit_lbs_sdk",
    ],
)
