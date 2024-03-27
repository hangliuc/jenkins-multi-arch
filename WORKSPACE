# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.

workspace(name = "shareidAds")
# load
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load('@bazel_tools//tools/build_defs/repo:git.bzl', 'git_repository')

# bazel_skylib
skylib_version = "0.8.0"
http_archive(
    name = "bazel_skylib",
    type = "tar.gz",
    url = "https://github.com/bazelbuild/bazel-skylib/releases/download/{}/bazel-skylib.{}.tar.gz".format (skylib_version, skylib_version),
    sha256 = "2ef429f5d7ce7111263289644d233707dba35e39696377ebab8b0bc701f7818e",
)

# glog
git_repository(
    name = "com_github_google_glog",
    remote = "git@git.ushareit.me:ads/algorithm/adsservice/glog.git",
    tag = "v1.0.0",
)

# gflag
http_archive(
    name = "com_github_gflags_gflags",
    strip_prefix = "gflags-46f73f88b18aee341538c0dfc22b1710a6abedef",
    url = "https://github.com/gflags/gflags/archive/46f73f88b18aee341538c0dfc22b1710a6abedef.tar.gz",
)
bind(
    name = "gflags",
    actual = "@com_github_gflags_gflags//:gflags",
)

# brpc
git_repository(
    name = "brpc",
    # remote = "git@git.ushareit.me:sprs-ads/ecom-dsp/brpc.git",
    # branch = "master",
    remote = "git@git.ushareit.me:sprs-ads/ecom-dsp/brpc.git",
    tag = "v1.0.1",
)

# protobuf
git_repository(
    name = "com_google_protobuf",
    remote = "git@git.ushareit.me:ads/algorithm/adsservice/protobuf.git",
    tag = "v3.6.1.3",
)

# rapidjson
git_repository(
    name = "rapidjson",
    remote = "git@git.ushareit.me:ads/algorithm/adsservice/base/rapidjson.git",
    #tag = "v3.6.1.3",
    branch = "master",
)


# leveldb
git_repository(
    name = "com_github_google_leveldb",
    remote = "git@git.ushareit.me:ads/algorithm/adsservice/base/leveldb.git",
    tag = "v1.0.0",
)

# shareit MA proto
git_repository(
    name = "shareit_ma_proto",
    remote = "git@git.ushareit.me:sprs-ads/ecom-dsp/proto.git",
    tag = "v1.3.33",
    # branch = "lyn_lbs_service",
)

# ads_util
git_repository(
    name = "ads_util",
    remote = "git@git.ushareit.me:sprs-ads/ecom-dsp/ads_util.git",
    tag = "v0.1.44.1",
    # branch = "lyn_modify_crypto",
)

# shareit lbs sdk
git_repository(
    name = "shareit_lbs_sdk",
    remote = "git@git.ushareit.me:csp/core/baseservice/lbs/shareit-lbs-cpp.git",
    tag = "v0.3.0_20240327"
    # branch = "lyn_debug"
)
