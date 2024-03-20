git pull
#!/bin/bash
cp -fr shell/.bazelrc_cloud .bazelrc

if [ "${PlatForm}" == "gcs" ];then
    echo "build --define with_gcs=true --cxxopt=-DUSE_GCS" >> .bazelrc
    echo "build --define with_s3=false --cxxopt=-DNOT_USE_S3" >> .bazelrc
fi

# 业务
bazel build ...
sh shell/copy_proto_src.sh
