#!/bin/bash

rm -fr proto_src
mkdir proto_src
cp -fr bazel-bin/external/shareit_ma_proto proto_src
# cp -fr bazel-bin/src/datamanager/ proto_src/
