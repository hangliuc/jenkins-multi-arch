#!/bin/bash
cp -fr shell/.bazelrc_cloud .bazelrc

ARCH=$(uname -m)
if [ "$ARCH" = "aarch64" ] || [ "$ARCH" = "arm64" ]; then
    echo "build --define arm_cpu=true --cxxopt=-DARM_CPU_ARCH" >> .bazelrc
fi

# 业务
bazel build ... --experimental_ui_max_stdouterr_bytes=1073741819
sh shell/copy_proto_src.sh
