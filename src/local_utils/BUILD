package(default_visibility = ["//visibility:public"])

load("@brpc//:bazel/brpc.bzl", "brpc_proto_library")

cc_library(
    name = 'local_utils',
    hdrs = glob([
        "*.h",
    ]),
    srcs = glob([
        "*.cpp",
    ],
    exclude = [
    ]),
    copts = [
    ],
    deps = [
        "@rapidjson//:rapidjson",
        "@ads_util//monitor:monitor",
        "@ads_util//runtime_info:runtime_util",
        "@ads_util//libcrypto:aes",
        "@ads_util//url_codec:url_codec",
        "@ads_util//string:string_util",
        "@ads_util//adder_window:adder_util",
    ],

)

